/*
クワイン・マクラスキー法とペトリック法による論理圧縮
参照
http://qiita.com/jun6231jp/items/41b492ce31a109e4cec6
*/
// #define NODEBUG
#include <assert.h>

#include <stdint.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "qmc.h"
#include "qmc_misc.h"
#include "readfile.h"
#include "mask12.h"

int msg_out=0 ;		//	各処理でのメッセージ出力
int org_format=0 ;	//	出力フォーマットをオリジナルに合わせる
int remake=1 ;		//	最小入力ビットを計算する
int sort_table=0;	//	入力テーブルをソートする

int read_opt(int argc, char* argv[]){
	int i ;
	int in_file=-1 ;

	for(i=1 ; i<argc ; i++){
		if(argv[i][0]=='-'){
			switch(argv[i][1]){
			case 'm': msg_out=1 ; break ;
			case 'f': org_format=1 ; break ;
			case 'r': remake=0 ; break ;
			case 's': sort_table=1 ; break ;
			}
		}
		else if(argv[i][0]!=0){
			in_file=i ;
		}
	}

	return in_file ;
}


int cmp_int(const void *left, const void *right)
{
	return *(int *) left - *(int *) right;
}

//	出力指示bitが立っている場合があるのでLOGIC_MASKでマスク後比較する。
int cmp_short(const void *left, const void *right)
{
	return (LOGIC_MASK & (*(uint32_t *) left)) - (LOGIC_MASK & (*(uint32_t *) right)) ;
}

static int cmpsize;
int cmp_mem(const void *left, const void *right)
{
	int i ;
	uint32_t *l=*(uint32_t**)left ;
	uint32_t *r=*(uint32_t**)right ;

	for(i=0 ; i<cmpsize ; i++, l++, r++){
		if(*l < *r){
			return -1 ;
		}
		else if(*l > *r){
			return 1 ;
		}
	}
	return 0 ;
}


//  logic をソートし、重複する行を削除する
int sort_and_uniq(uint32_t *logic, int logic_line)
{
	qsort(logic, logic_line, sizeof(uint32_t), cmp_short);

	int count = 0;
	for (int i = 1 ; i < logic_line; i++) {
		if (logic[count] != logic[i]) {
			logic[++count] = logic[i];
		}
	}
	return count+1 ;
}


//	sort and uniq logic_compress_*から呼ばれる
int uniq(int index)
{
	uint32_t **ubuff = NULL;

	int i;

	LogicTable* tbl_in=lt_search(index) ;
	if(tbl_in->lines < 2){
		if(msg_out){printf(" (%d) \n", tbl_in->lines); fflush(stdout) ;}
		return tbl_in->lines ;
	}

	cmpsize=tbl_in->pieces ;
	ubuff=tbl_in->logic ;

	//	入力の各行をソート
	for (i = 0; i < tbl_in->lines; i++) {
		qsort(ubuff[i], cmpsize, sizeof(uint32_t), cmp_int);
	}

	qsort(ubuff, tbl_in->lines, sizeof(uint32_t *), cmp_mem);

	int item_count = 0;
	for (i = 1; i < tbl_in->lines; i++) {
		if (memcmp(ubuff[item_count], ubuff[i], cmpsize * sizeof(int)) != 0) {
			ubuff[++item_count] = ubuff[i];
		}
	}
	tbl_in->t_line=item_count ;
	item_count++;
	tbl_in->lines=item_count ;

	if(msg_out){printf(" uniq(%d) \n", item_count); fflush(stdout) ;}

	return item_count;
}


//	tempからpatternと一致するデータを削除
int reject(uint32_t *temp, uint32_t pattern, int count){
	int dist=0 ;
	for (int i = 0; i < count; i++) {
		if (temp[i]!= pattern) {
			temp[dist++] = temp[i];
		}
	}
	return dist ;
}


//	入力から１，２へ出力
int logic_compress_2(int index)
{
	LogicTable* tbl_in ;

	int count1 = 0, count2 = 0;
	int pattern, pattern_n ;

	int tbl1=LT_INDEX_TEMP_BASE+1 ;
	int tbl2=LT_INDEX_TEMP_BASE+2 ;

	lt_make(tbl1);
	lt_make(tbl2);

	tbl_in=lt_search(index) ;

	int clen=tbl_in->bits ;
	lt_setbits(tbl1, clen) ;
	lt_setbits(tbl2, clen) ;

	int in_count = tbl_in->pieces ;
	uint32_t* logic=tbl_in->logic[0] ;
	uint32_t* logic_out = tbl_in->logic[1] ;

	uint32_t* logic_temp = malloc(in_count*sizeof(uint32_t)) ;
	memcpy(logic_temp, logic, in_count*sizeof(uint32_t)) ;

	int temp_count = in_count ;

	for (int i = 0; i < in_count; i++) {
		int j, k, m;
		pattern=logic_temp[0] ;

		for (j = 0; j < in_count; j++) {
			if(logic[j]==pattern) break;
		}
		if(j==in_count || logic_out[j]){
			int groupchk = 0;

			// ビット反転と比較
			for (m = 0; m < clen; m++) {
				int mask = 1UL << (clen-m-1) ;
				pattern_n = pattern ^ mask ;

				for (k = 0; k < in_count; k++) {
					if (logic[k]==pattern_n) break;
				}
				if(k==in_count || logic_out[k]){	//  出力が1かDon't care
					groupchk = 1;
					count2++;

					lt_add_piece(tbl2, pattern) ;
					lt_add_piece(tbl2, pattern_n) ;
					lt_newline(tbl2) ;

					temp_count=reject(logic_temp, pattern, temp_count) ;
					temp_count=reject(logic_temp, pattern_n, temp_count) ;
				}
			}

			if (groupchk == 0) {
				count1++;
				lt_add_piece(tbl1, pattern) ;
				lt_newline(tbl1) ;

				temp_count=reject(logic_temp, pattern, temp_count) ;
			}
		}
		else {					//  一致して出力が０
			temp_count=reject(logic_temp, pattern, temp_count) ;
		}
		if(temp_count==0) break ;
	}

	free(logic_temp) ;

	if (count1 > 0) {
		if(msg_out){printf("comp 1 ... end  %d lines\n", count1);}
	}

	if (count2 > 0) {
		int res = uniq(tbl2);
		if(msg_out){printf("comp 2 ... end %d lines \n", res);}
		return res ;
	}

	return 0;
}


//	halfからhalf*2へ
int logic_compress_n(int half)
{
	LogicTable* tbl_in ;

	int tbl1=LT_INDEX_TEMP_BASE+half ;
	int tbl2=LT_INDEX_TEMP_BASE+half*2 ;

	if(msg_out){printf("comp N(%d) ", half); fflush(stdout);}

	lt_make(tbl2) ;
	tbl_in=lt_search(tbl1) ;

	int nline=tbl_in->lines ;
	int part_len=tbl_in->bits ;

	uint32_t *pattern_n=malloc(half*sizeof(int)) ;

	LogicTable *tbl_master=lt_search(LT_INDEX_IN) ;
	lt_setbits(tbl2, tbl_master->bits) ;

	int master_ndata = tbl_master->pieces ;
	uint32_t* logic=tbl_master->logic[0] ;
	uint32_t* logic_out = tbl_master->logic[1] ;

	for(int i=0 ; i<nline ; i++){
		uint32_t *pattern=tbl_in->logic[i] ;

		for (int bit_pos = 0; bit_pos < part_len; bit_pos++) {	//  各ビット位置について
			int n, m;

			int mask=1UL << (part_len-bit_pos-1) ;

			//  bit_pos の同じものだけの行か？
			for (n = 1; n < half; n++) {
				if((pattern[0] & mask) != (pattern[n] & mask)) break;
			}
			if (n != half) continue ;

			for (n = 0; n < half; n++) {
				pattern_n[n] = pattern[n] ^ mask ;

				for (m = 0; m < master_ndata; m++) {
					if(logic[m]==pattern_n[n]){
						break ;
					}
				}
				if(m < master_ndata && logic_out[m]==0) break ; // 出力0
			}

			if(n == half){ // bit_posを反転した物が出力1だった
				lt_add_pieces(tbl2, pattern, half) ;
				lt_add_pieces(tbl2, pattern_n, half) ;
				lt_newline(tbl2) ;
			}
		}
	}

	free(pattern_n);

	if(msg_out){printf(" ... end "); fflush(stdout);}

	return uniq(tbl2);
}


int resize(int half)
{
	int tbl1=LT_INDEX_TEMP_BASE+half ;
	int tbl2=LT_INDEX_TEMP_BASE+half*2 ;
	int tbl_t=LT_INDEX_UT_BASE ;

	clock_t start, end;
	start = clock();
	if(msg_out){printf(" start resize(%d) ", half); fflush(stdout);}

	lt_make(tbl_t) ;

	LogicTable *tbl_in1 = lt_search(tbl1) ;
	LogicTable *tbl_in2 = lt_search(tbl2) ;

	lt_setbits(tbl_t, tbl_in1->bits) ;
	int tbl1_line = tbl_in1->lines ;
	int tbl1_count = tbl_in1->pieces ;

	uint32_t **i_buff = tbl_in2->logic ;
	int tbl2_line = tbl_in2->lines ;
	int tbl2_count = tbl_in2->pieces ;

	for(int line=0 ; line < tbl1_line ; line++){
		int i, j, n ;
		uint32_t * i_part=tbl_in1->logic[line] ;

		for (i = 0; i < tbl2_line; i++) {
			for (j = 0; j < tbl1_count; j++) {
				for (n = 0; n < tbl2_count; n++) {
					if (i_part[j] == i_buff[i][n]) {
						break;
					}
				}
				if (n == tbl2_count) break;
			}
			if (j == tbl1_count) break ;
		}
		if (i == tbl2_line){
			lt_add_pieces(tbl_t, i_part, tbl1_count) ;
			lt_newline(tbl_t) ;
		}
	}

	lt_delete(tbl1) ;
	lt_rename(tbl_t, tbl1) ;

	int out_count=lt_search(tbl1)->lines ;

	end = clock();

	if(msg_out){
		printf(" t(%.2f) ", (end - start) / 1000.0);
		printf(" ..end %d lines \n", out_count); fflush(stdout);
	}

	return out_count ;
}


int mem_cmp(uint32_t *haystack, uint32_t needle, int len){
	for(int i=0 ; i<len ; i++){
		if(haystack[i]==needle) return 1 ;
	}
	return 0 ;
}


void remove_dup(int dim)
{
	clock_t start, end;
	start = clock();

	if(msg_out){printf("remove dup(%d) ...", dim); fflush(stdout);}

	int tbl_temp=LT_INDEX_UT_BASE ;		//	compact_temp
	lt_make(tbl_temp) ;

	int tbl_slist=LT_INDEX_UT_BASE+1 ;	//	search_list
	lt_make(tbl_slist) ;

	int tbl1=LT_INDEX_TEMP_BASE+dim ;
	int tbl2=LT_INDEX_TEMP_BASE+dim*2 ;
	int tbl_master=LT_INDEX_IN ;

	LogicTable *tbl_in=lt_search(tbl1) ;

	int line_count=tbl_in->lines ;
	int count = tbl_in->pieces ;
	lt_setbits(tbl_temp, tbl_in->bits) ;

	int *br = malloc(count*sizeof(int));

	for(int i=0 ; i<line_count ; i++){
		LogicTable *ptr ;
		int m, n ;

		memset(br, 0, sizeof(int) * count);

		tbl_in=lt_search(tbl1) ;
		uint32_t *part=tbl_in->logic[i] ;

		ptr=lt_search(tbl1) ;	//同位ファイルからパターン検索
		for(m=0 ; m<ptr->lines ; m++){
			for (n = 0; n < count; n++) {
				if(mem_cmp(ptr->logic[m], part[n], ptr->pieces)){
					br[n]++;
				}
			}
		}

		ptr=lt_search(tbl2) ;	//上位ファイルからパターン検索
		for(m=0 ; m<ptr->lines ; m++){
			for (n = 0; n < count; n++) {
				if(mem_cmp(ptr->logic[m], part[n], ptr->pieces)){
					br[n]++;
				}
			}
		}

		ptr=lt_search(tbl_slist) ;
		for(m=0 ; m<ptr->lines ; m++){
			for (n = 0; n < count; n++) {
				if(mem_cmp(ptr->logic[m], part[n], ptr->pieces)){
					br[n]--;
				}
			}
		}

		ptr=lt_search(tbl_master) ;	//真理値表からパターン検索
		for (n = 0; n < count; n++) {
			if(mem_cmp(ptr->logic[0], part[n], ptr->pieces)==0){
				br[n] = 2;
			}
		}

		for (m = 0; m < count; m++) {
			if (br[m] < 2)
				break;
		}
		if (m < count) {
			lt_add_pieces(tbl_temp, part, count) ;
			lt_newline(tbl_temp) ;
		}
		else {
			lt_add_pieces(tbl_slist, part, count) ;
			lt_newline(tbl_slist) ;
		}
	}

	lt_delete(tbl1) ;
	lt_rename(tbl_temp, tbl1) ;
	lt_delete(tbl_slist) ;

	if(msg_out){
		end = clock();
		printf(" t(%.2f) ", (end - start) / 1000.0);
		printf("end : %d lines\n", lt_search(tbl1)->lines); fflush(stdout);
	}

	free(br);
}


//	結果出力
int logic_function(int field, int mask, int bits, int* conv)
{
	LogicTable* tbl_in=lt_search(LT_INDEX_TEMP_BASE+field) ;

	if(tbl_in==NULL || tbl_in->lines==0)
		return 0 ;

	int tbl_bitlen=tbl_in->bits ;
	uint32_t **line=tbl_in->logic ;

	for(int i=0 ; i<tbl_in->lines ; i++){
		int sum=0 ;
		if(i != 0) printf (" + ");

		for (int n = 0; n < tbl_bitlen; n++) {
			sum = 0;
			for (int m = 0; m < field; m++) {
				sum+= (line[i][m] >>(tbl_bitlen-n-1)) & 1 ; //	bit[n] ;
			}

			if (sum == 0) {
				if(org_format)
					printf ("[`%d]", conv[n]);
				else
					printf ("%c", 'a'+conv[n]);
			}
			else if (sum == field) {
				if(org_format)
					printf ("[%d]", conv[n]);
				else
					printf ("%c", 'A'+conv[n]);
			}
		}
	}
	printf ("\n");

	return 1 ;
}


//	maskした時削除できる行か？
int compare_table(uint32_t *table, char *out, int len, uint32_t mask){
	if(len<=1) return 0 ;

	for(int i=0 ; i<len-1 ; i++){
		for(int m=i+1 ; m<len ; m++){
			if((table[i] & mask) == (table[m] & mask)){
				if(out[i]!=out[m]) return 0 ;
			}
		}
	}
	return 1 ;
}


//	不要なビットを削除するマスクを返す
int least_mask(InTable* in_table)
{
	for(int i=0 ; i<MASK_TABLE_SIZE ; i++){
		if(compare_table(in_table->logic_arg, in_table->out_arg, in_table->nline, mask_table[i])){
			return mask_table[i] ;
		}
	}
	return -1 ;	//	矛盾がある
}


//	マスク、ソート済みデータを作る
int make_table(InTable* in_table){
	int i ;

	int mask=least_mask(in_table) ;

	if(mask<0){	//	入力に矛盾がある
		printf("error table_remake.\n") ;
		return -1 ;
	}

	if(remake==0){
		mask=LOGIC_MASK ;
	}
	else{
		printf(" mask[%03x]", mask) ;
	}
	in_table->rebuild_mask=mask ;

	int l=in_table->nline ;
	int sum=0 ;
	for(i=0 ; i<l ; i++){
		sum+=in_table->out_arg[i]-'0' ;
		in_table->logic[i]=(in_table->logic_arg[i] & mask) | (in_table->out_arg[i]-'0')<<OUT_MASK_SHIFT ;
	}

	if(sum==l){	//	出力指示が全て '1'
		if(msg_out) printf("\nResult") ;
		printf("\n1\n") ;
		return 0;
	}
	if(sum==0){	//	全て '0'
		if(msg_out) printf("\nResult") ;
		printf("\n0\n") ;
		return 0;
	}

	//	未使用のビットを削除して詰める	出力指示ビットはクリアされる
	in_table->bits=0 ;
	for(i=0 ; i<l ; i++){
		int logic=in_table->logic[i] ;
		in_table->logic[i]=0 ;

		for(int m=0, bit=0 ; m<in_table->logic_bits ; m++){
			//	maskのビットが立ってる位置だけ取り出して詰める
			if(mask & (1UL<<m)){
				in_table->logic[i] |= (logic & (1UL<<m))>>(m-bit) ;
				bit++ ;
			}
		}

		int msb = msb16(in_table->logic[i])+1 ;	//	上位の0のビットを除いた長さ
		if(in_table->bits < msb) in_table->bits = msb ;

		in_table->logic[i] |= (logic & OUT_MASK) ;	//	出力指示ビット書き戻し
	}

	if(remake==0){
		//	上位の0は省略するので、maskの上位はクリアしておく。こうしないと出力時にbit位置がずれるから。
		mask &= (LOGIC_MASK >> (LOGIC_MAX_BITS - in_table->bits)) ;
	}

	//	重複行削除	出力バッファはソートされない
	if(sort_table){
		l=sort_and_uniq(in_table->logic, l) ;
		printf(" Sort(%d)", l) ;
	}
	else{
		printf(" Data(%d)", l) ;
	}

	//	入力データテーブル（remake,sort済み）をセット
	in_table->nline_rebuild=l ;

	lt_make(LT_INDEX_IN) ;
	lt_setbits(LT_INDEX_IN, in_table->bits) ;

	for(i=0 ; i<l ; i++){
		lt_add_piece(LT_INDEX_IN, in_table->logic[i] & LOGIC_MASK) ;	//	1行目は出力指示ビットを削除
	}

	lt_newline(LT_INDEX_IN) ;

	for(i=0 ; i<l ; i++){
		lt_add_piece(LT_INDEX_IN, in_table->logic[i] >> OUT_MASK_SHIFT) ;	//	2行目は出力ビットのみ
	}

	//	mask前のビット位置
	int pos = 0 ;
	for(i=0 ; i<in_table->logic_bits ; i++){
		if(mask & (1UL << (in_table->logic_bits - i - 1))){
			in_table->conv[pos] = i ;
			pos++ ;
		}
	}

	printf("\n") ;
	return 1 ;
}


//	圧縮
int compress(InTable* in_table){
	int field = 2;

	int ret=logic_compress_2(LT_INDEX_IN) ;
	while (ret >= 2) {
		ret = logic_compress_n(field);
		if(ret==0){
			remove_dup(field);
		}
		else if(resize(field) > 0){
			remove_dup(field);
		}
		field <<= 1;
	}

	//	結果表示
	if(msg_out){printf("Result\n");}
	while (field) {
		logic_function(field, in_table->rebuild_mask, in_table->logic_bits, in_table->conv);
		field >>= 1;
	}

	return 0 ;
}


InFile in_file[1] ;
InTable in_table[1] ;

int main(int argc, char *argv[])
{
	int file=read_opt(argc, argv) ;

	if (argc < 2 || file<0) {
		printf("Usage : qmc FILE [-r -m -f -s]\n");
		printf("\t-r no remake.\n") ;
		printf("\t-m message out.\n") ;
		printf("\t-f original out format.\n") ;
		printf("\t-s sort input table.\n") ;
		return 1 ;
	}

	if(read_in_file(in_file, argv[file])<0){
		printf("file [%s] not exists.\n", argv[file]);
		return 2 ;
	}

	clock_t start, end;
	start = clock();

	lt_setup() ;

	for(int clmn=0 ; clmn < in_file->out_bits ; clmn++){
		printf("\n# Clumn %d ", clmn+1) ;

		setup_in_table(in_file, in_table, clmn) ;

		if(make_table(in_table) > 0)
			compress(in_table) ;

		lt_freeall() ;
		free_in_table(in_table) ;
	}

	end = clock();
	if(msg_out){printf("time (%.4f) \n", (end - start) / 1000.0);}

	return 0;
}
