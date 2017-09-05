/*
	色々
*/
// #define NODEBUG
// #define DEBUG
#include <assert.h>

#include <stdint.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>

#include "qmc.h"
#include "qmc_misc.h"

int nlogic_table = 0;
LogicTable *logic_table = NULL;

//  バッファが一杯ならlogic、logic_buffをreallocする
static int lt_grow_buff(LogicTable * ptr)
{
	if ((ptr->t_line+1) >= ptr->buff_lines) {
		ptr->buff_lines *= 2;
		ptr->logic = realloc(ptr->logic, ptr->buff_lines * sizeof(uint32_t *));
	}

	int buff_size = (ptr->t_line+2) * ptr->pieces * sizeof(uint32_t) ;
	if (buff_size > ptr->buff_len) {
		while(buff_size >= ptr->buff_len){
			ptr->buff_len *= 2 ;
		}

		ptr->logic_buff = realloc(ptr->logic_buff, ptr->buff_len);

		//  ポインタ付け替え
		for (int i = 0; i < ptr->t_line; i++) {
			ptr->logic[i] = ptr->logic_buff + i * ptr->pieces;
		}
	}

	ptr->logic[ptr->t_line] = ptr->logic_buff + ptr->t_line * ptr->pieces;
	ptr->logic[ptr->t_line+1] = NULL ;

	return ptr->buff_len;
}


static LogicTable *cache_ptr = NULL;	//  キャッシュ

//  indexで探す
//	これが返すポインタは、テーブルが増えて再配置された時に未定義になるので注意
LogicTable *lt_search(int index)
{
	if (cache_ptr != NULL && cache_ptr->index == index) {
		return cache_ptr;
	}

	LogicTable *ptr = logic_table;

	for (int i = 0; i < nlogic_table; i++) {
		if (ptr->index == index) {
			cache_ptr = ptr;
			return ptr;
		}
		ptr++ ;
	}

	return NULL;
}


//  初期化
int lt_setup(void)
{
	nlogic_table=8 ;
	logic_table = malloc(sizeof(LogicTable) * nlogic_table);
	int i;
	for (i = 0; i < nlogic_table; i++) {
		logic_table[i].index = LT_INDEX_NOT_USE;
		logic_table[i].logic_buff = NULL;
		logic_table[i].logic = NULL;
	}

	return nlogic_table;
}


void lt_freeall(void){
	int i ;

	for (i = 0; i < nlogic_table; i++) {
		if (logic_table[i].index != 0) {
			lt_delete(logic_table[i].index) ;
		}
	}
}


LogicTable* lt_make(int index)
{
	int i;
	assert(logic_table!=NULL) ;

	for (i = 0; i < nlogic_table; i++) {
		if (logic_table[i].index == index) {
			lt_delete(index) ;
		}
	}

	for (i = 0; i < nlogic_table; i++) {
		if (logic_table[i].index == LT_INDEX_NOT_USE) {
			break;
		}
	}

	if (i == nlogic_table) {	//  満員
		int old_size = nlogic_table;
		nlogic_table *= 2;

		cache_ptr=NULL ;	//	テーブルを移動するので、ポインタキャッシュをクリア
		logic_table = realloc(logic_table, sizeof(LogicTable) * nlogic_table);

		for (i = old_size + 1; i < nlogic_table; i++) {
			logic_table[i].index = LT_INDEX_NOT_USE;
			logic_table[i].logic_buff = NULL;
			logic_table[i].logic = NULL;
		}
		i = old_size;
	}

	LogicTable *ptr = logic_table + i;

	ptr->index = index;
	ptr->bits = 0;
	ptr->pieces = 0;
	ptr->lines = 0;
	ptr->t_line = 0;
	ptr->t_pos = 0;
	ptr->buff_lines = 4 ;
	ptr->buff_len = 8 ;

	ptr->logic_buff = malloc(sizeof(uint32_t) * ptr->buff_len);
	ptr->logic = malloc(sizeof(uint32_t **) * ptr->buff_lines);

	ptr->logic[0] = ptr->logic_buff ;
	ptr->logic[1] = NULL ;

	return ptr ;
}

int lt_delete(int index)
{
	LogicTable *ptr = lt_search(index);
	assert(ptr != NULL) ;

	if (ptr->buff_len != 0 && ptr->logic != NULL) {
		free(ptr->logic);
	}
	if (ptr->buff_lines != 0 && ptr->logic_buff != NULL) {
		free(ptr->logic_buff);
	}
	ptr->index = LT_INDEX_NOT_USE;
	ptr->logic = NULL;
	ptr->logic_buff = NULL;
	ptr->buff_len = 0;
	ptr->buff_lines = 0;
	return 1;
}


int lt_newline(int index)
{
	LogicTable *ptr = lt_search(index);
	assert(ptr != NULL) ;

	ptr->t_line++;
	ptr->t_pos = 0;

	lt_grow_buff(ptr);

	return -1;
}




void lt_setbits(int index, int bits)
{
	LogicTable *ptr = lt_search(index);
	assert(ptr != NULL) ;

	ptr->bits = bits;
}


int lt_rename(int old_index, int new_index){
	LogicTable *ptr = lt_search(old_index);
	assert(ptr != NULL) ;

	ptr->index=new_index ;

	return old_index ;
}


//  追加　行があふれたらエラー
int lt_add_piece(int index, uint32_t piece)
{
	LogicTable *ptr = lt_search(index);
	assert(ptr != NULL) ;

	if (ptr->t_line == 0) {		//  １行目なら際限なく追加
		if(ptr->lines==0) ptr->lines=1 ;
		ptr->pieces++;
		lt_grow_buff(ptr);
		ptr->logic[ptr->t_line][ptr->t_pos] = piece;
		ptr->t_pos++;
	}
	else {						//  ２行目以降は１ラインのデータ数に制限がある
		assert(ptr->t_pos < ptr->pieces) ;
		ptr->lines=ptr->t_line+1 ;	//	linesは要素追加時に更新
		ptr->logic[ptr->t_line][ptr->t_pos] = piece;
		ptr->t_pos++;
	}

	return ptr->t_pos;
}

int lt_add_pieces(int index, uint32_t *pieces, int count){
	LogicTable *ptr = lt_search(index);
	assert(ptr != NULL) ;

	int i ;

	if(ptr->t_line==0){
		if(ptr->lines==0) ptr->lines=1 ;
		ptr->pieces+=count ;	//	先に数を増やして
		lt_grow_buff(ptr);		//	バッファ更新
		for(i=0 ; i<count ; i++){
			ptr->logic[0][ptr->t_pos++] = pieces[i] ;
		}
	}
	else{
		assert(ptr->t_pos+count <= ptr->pieces) ;
		ptr->lines=ptr->t_line+1 ;	//	lines更新
		for(i=0 ; i<count ; i++){
			ptr->logic[ptr->t_line][ptr->t_pos++] = pieces[i] ;
		}
	}

	return ptr->t_pos;
}

int lt_lines(int index){
	LogicTable *ptr = lt_search(index);
	assert(ptr != NULL) ;

	return ptr->lines ;
}

int lt_pieces(int index){
	LogicTable *ptr = lt_search(index);
	assert(ptr != NULL) ;

	return ptr->pieces ;
}
int lt_bits(int index){
	LogicTable *ptr = lt_search(index);
	assert(ptr != NULL) ;

	return ptr->bits ;
}

uint32_t ** lt_logic(int index){
	LogicTable *ptr = lt_search(index);
	assert(ptr != NULL) ;

	return ptr->logic ;
}

void lt_setlines(int index, int lines){
	LogicTable *ptr = lt_search(index);
	assert(ptr != NULL) ;

	int wlines=ptr->t_line ;
	ptr->t_line=lines ;
	ptr->lines=lines+1 ;

	if(wlines < lines){	//	拡張
		lt_grow_buff(ptr) ;
	}
}



static const uint32_t popc_table[16] = {
	0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4
};

// 16bits
int huming_weight16(uint32_t a)
{
	a &= 0xffff ;
	return
		popc_table[a & 0x0f] +
		popc_table[(a >> 4) & 0x0f] +
		popc_table[(a >> 8) & 0x0f] +
		popc_table[(a >> 12) & 0x0f];
}

int msb16(uint32_t v) {
	v &= 0xffff ;
	if (v == 0) return 0;
	v |= (v >> 1);
	v |= (v >> 2);
	v |= (v >> 4);
	v |= (v >> 8);
	return huming_weight16(v) - 1 ;
}



//  文字列末の改行を削除する

int trim_CRLF(char *str)
{
	int l = strlen(str)-1;
	if(l>=0){
		if (str[l] == '\x0d' || str[l] == '\x0a') {
			str[l] = 0;
		}
	}
	l-- ;

	if(l>=0){
		if (str[l] == '\x0d' || str[l] == '\x0a') {
			str[l] = 0;
		}
	}
	return 0;
}


void setup_in_table(InFile* in_file, InTable* in_table, int clmn){
	int i, l=0 ;

	in_table->logic_bits=in_file->logic_bits ;
	in_table->nline=in_file->nline ;

	in_table->logic_arg=malloc(sizeof (uint32_t) * (in_file->nline)) ;
	in_table->out_arg=malloc(in_file->nline+1) ;
	in_table->out_arg[0]=0 ;

	in_table->nline_rebuild=0 ;
	in_table->rebuild_mask=LOGIC_MASK ;
	in_table->logic=malloc(sizeof (uint32_t) * (in_file->nline)) ;

	for(i=0 ; i<in_file->nline ; i++){
		if(in_file->out[i][clmn]!='x'){	//	Don't careの行は除く
			in_table->logic_arg[l]=in_file->logic[i] ;
			in_table->out_arg[l]=in_file->out[i][clmn] ;
			l++ ;
		}
	}
	in_table->nline= l ;
}


void free_in_table(InTable* in_table){
	assert(in_table->logic_arg!=NULL) ;
	free(in_table->logic_arg) ;

	assert(in_table->logic!=NULL) ;
	free(in_table->logic) ;

	assert(in_table->out_arg!=NULL) ;
	free(in_table->out_arg) ;
}


#if 1
void lt_dump(void)
{
	int i;

	printf("nlogic_table:%d -----\n", nlogic_table);

	for (i = 0; i < nlogic_table; i++) {
		int n, m;
		printf("[%d]\n", i);
		printf("  index: %03x\n", logic_table[i].index);	//  0:未使用　1:入力テーブル　0x100～ 圧縮テーブル
		printf("  bits: %d\n", logic_table[i].bits);	//　データのビット数
		printf("  pieces: %d\n", logic_table[i].pieces);	//  一行のデータ数 １行目追加中のみ増加する
		printf("  lines: %d\n", logic_table[i].lines);	//  行数
		printf("  t_line: %d\n", logic_table[i].t_line);	//  追加中の行
		printf("  t_pos: %d\n", logic_table[i].t_pos);	//  行のはしっこ
		printf("  logic[%p] buff[%p]\n", logic_table[i].logic, logic_table[i].logic_buff);	//  データ
		if (logic_table[i].logic == NULL) {
			printf("      (null)\n");
		}
		else {
			for (m = 0; /* m < 8 &&*/ m < logic_table[i].lines; m++) {
				printf("   %3d:", m);
//				printf("[%p]", logic_table[i].logic[m]);
				for (n = 0; n<logic_table[i].pieces && n < 8; n++) {
					printf("%05x ", logic_table[i].logic[m][n]);
				}
				printf("\n");
			}
		}
		printf("  buff_lines: %d\n", logic_table[i].buff_lines);	//  確保済み行領域
		printf("  buff_len: %d\n", logic_table[i].buff_len);	//  確保済み領域
		printf("----------------------\n");
	}
}

#endif
