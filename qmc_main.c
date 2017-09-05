/*
クワイン・マクラスキー法とペトリック法による論理圧縮
参照
http://qiita.com/jun6231jp/items/41b492ce31a109e4cec6
*/
// #define NODEBUG
#include <assert.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "qmc.h"
#include "qmc_misc.h"
#include "readfile.h"
#include "mask12.h"


int remake = 0;					//  最小入力ビットを計算する
int sort_table = 0;				//  入力テーブルをソートする

int read_opt(int argc, char *argv[])
{
	int i;
	int in_file = -1;

	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
			case 'r':
				remake = 1;
				break;
			case 's':
				sort_table = 1;
				break;
			}
		}
		else if (in_file == -1 && argv[i][0] != 0) {
			in_file = i;
		}
	}
	return in_file;
}

void print_usage(void)
{
	printf("Usage : qmc FILE [-r -s]\n");
	printf("\t-r remake table.\n");
	printf("\t-s sort input table.\n");
}


int cmp_int(const void *left, const void *right)
{
	return *(int *) left - *(int *) right;
}

//  出力指示bitが立っている場合があるのでLOGIC_MASKでマスク後比較する。
int cmp_short(const void *left, const void *right)
{
	return (LOGIC_MASK & (*(uint32_t *) left)) - (LOGIC_MASK & (*(uint32_t *) right));
}


static int CMPSize;

int cmp_mem(const void *left, const void *right)
{
	int i;
	uint32_t *l = *(uint32_t **) left;
	uint32_t *r = *(uint32_t **) right;

	for (i = 0; i < CMPSize; i++, l++, r++) {
		if (*l < *r) return -1;
		else if (*l > *r) return 1;
	}
	return 0;
}

//  sort and uniq logic_compress_*から呼ばれる
int uniq(int index)
{
	int i;
	int len = lt_lines(index);

	if (len == 0)
		return len;

	CMPSize = lt_pieces(index);
	uint32_t **ubuff = lt_logic(index);

	//  入力の各行をソート
	for (i = 0; i < len; i++) {
		qsort(ubuff[i], CMPSize, sizeof(uint32_t), cmp_int);
	}

	qsort(ubuff, len, sizeof(uint32_t *), cmp_mem);	//  ソート

	int item_count = 0;
	for (i = 1; i < len; i++) {
		if (memcmp(ubuff[item_count], ubuff[i], CMPSize * sizeof(int)) != 0) {
			ubuff[++item_count] = ubuff[i];
		}
	}
	lt_setlines(index, item_count);
	item_count++;

	return item_count;
}


//  tempからpatternと一致するデータを削除
int reject(uint32_t * temp, uint32_t pattern, int count)
{
	int dist = 0;
	for (int i = 0; i < count; i++) {
		if (temp[i] != pattern) {
			temp[dist++] = temp[i];
		}
	}
	return dist;
}


//  入力から１，２へ出力
int logic_compress_2(int index)
{
	int pattern, pattern_n;

	int tbl1 = LT_INDEX_TEMP_BASE + 1;
	int tbl2 = LT_INDEX_TEMP_BASE + 2;

	lt_make(tbl1);
	lt_make(tbl2);

	int clen = lt_bits(index);
	lt_setbits(tbl1, clen);
	lt_setbits(tbl2, clen);

	int in_count = lt_pieces(index);
	uint32_t *logic = lt_logic(index)[0];
	uint32_t *logic_out = lt_logic(index)[1];

	uint32_t *logic_temp = malloc(in_count * sizeof(uint32_t));
	memcpy(logic_temp, logic, in_count * sizeof(uint32_t));

	int temp_count = in_count;

	for (int i = 0; i < in_count; i++) {
		int j, k, m;
		pattern = logic_temp[0];

		for (j = 0; j < in_count; j++) {
			if (logic[j] == pattern) break;
		}
		if (j == in_count || logic_out[j]) {
			int tbl_out = 1;

			// ビット反転と比較
			for (m = 0; m < clen; m++) {
				int mask = 1UL << (clen - m - 1);
				pattern_n = pattern ^ mask;

				for (k = 0; k < in_count; k++) {
					if (logic[k] == pattern_n) break;
				}
				if (k == in_count || logic_out[k]) {	//  出力が1かDon't care
					tbl_out = 2;

					lt_add_piece(tbl2, pattern);
					lt_add_piece(tbl2, pattern_n);
					lt_newline(tbl2);

					temp_count = reject(logic_temp, pattern, temp_count);
					temp_count = reject(logic_temp, pattern_n, temp_count);
				}
			}

			if (tbl_out == 1) {
				lt_add_piece(tbl1, pattern);
				lt_newline(tbl1);

				temp_count = reject(logic_temp, pattern, temp_count);
			}
		}
		else {					//  一致して出力が０
			temp_count = reject(logic_temp, pattern, temp_count);
		}
		if (temp_count == 0) break;
	}

	free(logic_temp);

	return uniq(tbl2);
}


//  halfからhalf*2へ
int logic_compress_n(int half)
{
	int tbl1 = LT_INDEX_TEMP_BASE + half;
	int tbl2 = LT_INDEX_TEMP_BASE + half * 2;

	uint32_t *pattern_n = malloc(half * sizeof(int));

	lt_make(tbl2);
	lt_setbits(tbl2, lt_bits(LT_INDEX_IN));

	int nline = lt_lines(tbl1);
	int bits = lt_bits(tbl1);

	int master_datas = lt_pieces(LT_INDEX_IN);
	uint32_t **master_logic = lt_logic(LT_INDEX_IN);

	for (int i = 0; i < nline; i++) {
		uint32_t *pattern = lt_logic(tbl1)[i];

		for (int bit_pos = 0; bit_pos < bits; bit_pos++) {	//  各ビット位置について
			int n, m;
			int mask = 1UL << (bits - bit_pos - 1);

			for (n = 1; n < half; n++) {	//  bit_pos の同じものだけの行か？
				if ((pattern[0] & mask) != (pattern[n] & mask)) break;
			}
			if (n != half) continue;

			for (n = 0; n < half; n++) {
				pattern_n[n] = pattern[n] ^ mask;

				for (m = 0; m < master_datas; m++) {
					if (master_logic[0][m] == pattern_n[n]) break;
				}
				if (m < master_datas && master_logic[1][m] == 0) break;		// 出力0
			}
			if (n == half) {	// bit_posを反転した物が出力1だった
				lt_add_pieces(tbl2, pattern, half);	//  後でソートするので
				lt_add_pieces(tbl2, pattern_n, half);	//  データセット順は関係ない
				lt_newline(tbl2);
			}
		}
	}
	free(pattern_n);
	return uniq(tbl2);
}


int resize(int half)
{
	int tbl1 = LT_INDEX_TEMP_BASE + half;
	int tbl2 = LT_INDEX_TEMP_BASE + half * 2;
	int tbl_t = LT_INDEX_UT_BASE;

	lt_make(tbl_t);
	lt_setbits(tbl_t, lt_bits(tbl1));

	uint32_t **logic_in = lt_logic(tbl1);
	int tbl1_line = lt_lines(tbl1);
	int tbl1_count = lt_pieces(tbl1);

	uint32_t **i_buff = lt_logic(tbl2);
	int tbl2_line = lt_lines(tbl2);
	int tbl2_count = lt_pieces(tbl2);

	for (int line = 0; line < tbl1_line; line++) {
		int i, j, n;
		uint32_t *i_part = logic_in[line];

		for (i = 0; i < tbl2_line; i++) {
			for (j = 0; j < tbl1_count; j++) {
				for (n = 0; n < tbl2_count; n++) {
					if (i_part[j] == i_buff[i][n]) break;
				}
				if (n == tbl2_count) break;
			}
			if (j == tbl1_count) break;
		}
		if (i == tbl2_line) {
			lt_add_pieces(tbl_t, i_part, tbl1_count);
			lt_newline(tbl_t);
		}
	}

	lt_delete(tbl1);
	lt_rename(tbl_t, tbl1);

	return lt_lines(tbl1);
}


inline int mem_cmp(uint32_t * haystack, uint32_t needle, int len)
{
	for (int i = 0; i < len; i++) {
		if (haystack[i] == needle)
			return 1;
	}
	return 0;
}

void count_pattern(uint32_t ** logic, int lines, uint32_t * part, int count,
				   int pieces, int *br)
{
	for (int m = 0; m < lines; m++) {
		for (int n = 0; n < count; n++) {
			if (mem_cmp(logic[m], part[n], pieces)) {
				br[n]++;
			}
		}
	}
	return;
}

void remove_dup(int dim)
{
	int tbl_out = LT_INDEX_UT_BASE;	//  出力
	int slist = LT_INDEX_UT_BASE + 1;
	int tbl_master = LT_INDEX_IN;

	int tbl1 = LT_INDEX_TEMP_BASE + dim;
	int tbl2 = LT_INDEX_TEMP_BASE + dim * 2;

	lt_make(slist);
	lt_make(tbl_out);
	lt_setbits(tbl_out, lt_bits(tbl1));

	int count = lt_pieces(tbl1);

	int *br = malloc(sizeof(int) * count * 3);
	int *abr = br + count;
	int *sbr = br + count * 2;

	for (int i = 0; i < lt_lines(tbl1); i++) {
		int n;
		memset(br, 0, sizeof(int) * count * 3);
		uint32_t *part = lt_logic(tbl1)[i];	//tbl_in->logic[i] ;

		for (n = 0; n < count; n++) {	//真理値表からパターン検索
			if (mem_cmp
				(lt_logic(tbl_master)[0], part[n],
				 lt_pieces(tbl_master)) == 0) {
				br[n] = 2;
			}
		}

		count_pattern(lt_logic(tbl1), lt_lines(tbl1), part, count, lt_pieces(tbl1), abr);	//同位ファイル
		count_pattern(lt_logic(tbl2), lt_lines(tbl2), part, count, lt_pieces(tbl2), abr);	//上位ファイル
		count_pattern(lt_logic(slist), lt_lines(slist), part, count, lt_pieces(slist), sbr);	//  サーチ済み

		for (n = 0; n < count; n++) {
			if ((br[n] != 2) && ((abr[n] - sbr[n]) < 2)) break;
		}
		if (n < count) {
			lt_add_pieces(tbl_out, part, count);
			lt_newline(tbl_out);
		}
		else {
			lt_add_pieces(slist, part, count);
			lt_newline(slist);
		}
	}

	lt_delete(tbl1);
	lt_rename(tbl_out, tbl1);
	lt_delete(slist);
	free(br);
}


//  結果出力
int logic_function(int field, int mask, int bits, int *conv)
{
	int tbl_in = LT_INDEX_TEMP_BASE + field;

	int count = lt_lines(tbl_in);
	if (count == 0) return 0;

	int tbl_bitlen = lt_bits(tbl_in);
	uint32_t **line = lt_logic(tbl_in);

	for (int i = 0; i < count; i++) {
		int sum = 0;
		if (i != 0) printf(" + ");

		for (int n = 0; n < tbl_bitlen; n++) {
			sum = 0;
			for (int m = 0; m < field; m++) {
				sum += (line[i][m] >> (tbl_bitlen - n - 1)) & 1;	//  bit[n] ;
			}

			if (sum == 0)
				printf("%c", 'a' + conv[n]);
			else if (sum == field)
				printf("%c", 'A' + conv[n]);
		}
	}
	printf("\n");

	return 1;
}


//  logic をソートし、重複する行を削除する
int sort_and_uniq(uint32_t * logic, int logic_line)
{
	qsort(logic, logic_line, sizeof(uint32_t), cmp_short);

	int count = 0;
	for (int i = 1; i < logic_line; i++) {
		if (logic[count] != logic[i]) {
			logic[++count] = logic[i];
		}
	}
	return count + 1;
}


//  maskした時削除できる行か？
int compare_table(uint32_t * table, char *out, int len, uint32_t mask)
{
	if (len <= 1) return 0;

	for (int i = 0; i < len - 1; i++) {
		for (int m = i + 1; m < len; m++) {
			if ((table[i] & mask) == (table[m] & mask)) {
				if (out[i] != out[m]) return 0;
			}
		}
	}
	return 1;
}


//  不要なビットを削除するマスクを返す
int least_mask(InTable * in_table)
{
	for (int i = 0; i < MASK_TABLE_SIZE; i++) {
		if (compare_table(in_table->logic_arg, in_table->out_arg, in_table->nline,mask_table[i])) {
			return mask_table[i];
		}
	}
	return -1;	//  矛盾がある
}


//  マスク、ソート済みデータを作る
int make_table(InTable * in_table)
{
	int i;
	int mask = least_mask(in_table);

	if (mask < 0) {	//  入力に矛盾がある
		printf("error table_remake.\n");
		return -1;
	}

	if (remake == 0) {
		mask = LOGIC_MASK;
	}
	else {
		printf(" mask[%03x]", mask);
	}
	in_table->rebuild_mask = mask;

	int lines = in_table->nline;
	int sum = 0;
	for (i = 0; i < lines; i++) {
		sum += in_table->out_arg[i] - '0';
		in_table->logic[i] = (in_table->logic_arg[i] & mask) | (in_table->out_arg[i] - '0') << OUT_MASK_SHIFT;
	}

	if (sum == lines) {	//  出力指示が全て '1'
		printf("\n1\n");
		return 0;
	}
	if (sum == 0) {	//  全て '0'
		printf("\n0\n");
		return 0;
	}

	//  未使用のビットを削除して詰める   出力指示ビットはクリアされる
	in_table->bits = 0;
	for (i = 0; i < lines; i++) {
		int logic = in_table->logic[i];
		in_table->logic[i] = 0;

		for (int m = 0, bit = 0; m < in_table->logic_bits; m++) {
			//  maskのビットが立ってる位置だけ取り出して詰める
			if (mask & (1UL << m)) {
				in_table->logic[i] |= (logic & (1UL << m)) >> (m - bit);
				bit++;
			}
		}

		int msb = msb16(in_table->logic[i]) + 1;	//  上位の0のビットを除いた長さ
		if (in_table->bits < msb)
			in_table->bits = msb;

		in_table->logic[i] |= (logic & OUT_MASK);	//  出力指示ビット書き戻し
	}

	if (remake == 0) {
		mask &= (LOGIC_MASK >> (LOGIC_MAX_BITS - in_table->bits));
	}

	//  重複行削除 出力バッファはソートされない
	if (sort_table) {
		lines = sort_and_uniq(in_table->logic, lines);
	}

	//  入力データテーブル（remake,sort済み）をセット
	in_table->nline_rebuild = lines;

	lt_make(LT_INDEX_IN);
	lt_setbits(LT_INDEX_IN, in_table->bits);

	for (i = 0; i < lines; i++) {
		lt_add_piece(LT_INDEX_IN, in_table->logic[i] & LOGIC_MASK);	//  1行目は出力指示ビットを削除
	}

	lt_newline(LT_INDEX_IN);

	for (i = 0; i < lines; i++) {
		lt_add_piece(LT_INDEX_IN, in_table->logic[i] >> OUT_MASK_SHIFT);	//  2行目は出力ビットのみ
	}

	int pos = 0;
	for (i = 0; i < in_table->logic_bits; i++) {
		if (mask & (1UL << (in_table->logic_bits - i - 1))) {
			in_table->conv[pos] = i;	//  入力ファイル中のビット位置
			pos++;
		}
	}

	printf("\n");
	return 1;
}


//  圧縮
int compress(InTable * in_table)
{
	int field = 2;

	int ret = logic_compress_2(LT_INDEX_IN);
	while (ret >= 2) {
		ret = logic_compress_n(field);

		if (ret == 0)
			remove_dup(field);
		else if (resize(field) > 0)
			remove_dup(field);

		field <<= 1;
	}

	//  結果表示
	while (field) {
		logic_function(field, in_table->rebuild_mask, in_table->logic_bits,
					   in_table->conv);
		field >>= 1;
	}

	return 0;
}


InFile in_file[1];
InTable in_table[1];


int main(int argc, char *argv[])
{
	int file = read_opt(argc, argv);

	if (argc < 2 || file < 0) {
		print_usage();
		return 1;
	}

	if (read_in_file(in_file, argv[file]) < 0) {
		printf("file [%s] not exists.\n", argv[file]);
		return 2;
	}

	lt_setup();

	for (int clmn = 0; clmn < in_file->out_bits; clmn++) {
		printf("\n# Clumn %d ", clmn + 1);

		setup_in_table(in_file, in_table, clmn);

		if (make_table(in_table) > 0)
			compress(in_table);

		lt_freeall();
		free_in_table(in_table);
	}

	return 0;
}


