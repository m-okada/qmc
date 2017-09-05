#ifndef _QMC_MISC_H
#define _QMC_MISC_H

#include "readfile.h"

typedef struct tagLogicTable{
	int index ;		//	0:未使用　1:入力テーブル　0x100～ 圧縮テーブル
	int bits ;		//　データのビット数
	int pieces ;	//	一行のデータ数 １行目追加中のみ増加する
	int lines ;		//	行数
	int t_line ;	//	追加中の行
	int t_pos ;		//	行のはしっこ

	uint32_t** logic ;	//	データ
	uint32_t* logic_buff ;	//	メモリブロックの先頭

	int buff_lines ;	//	確保済み行数
	int buff_len ;		//	確保済み要素数
} LogicTable ;


//	計算一回分のデータ
typedef struct tagInTable{
	int nline ;
	int logic_bits ;	//	入力部分のビット数
	uint32_t* logic_arg ;
	char * out_arg ;

	uint32_t rebuild_mask ;	//	リビルド済み
	int nline_rebuild ;
	int bits ;
	uint32_t* logic ;
	int conv[LOGIC_MAX_BITS] ;	//	ビット位置変換テーブル
} InTable ;


LogicTable *lt_search(int index) ;
int lt_setup(void) ;
void lt_freeall(void);

LogicTable* lt_make(int index) ;
int lt_delete(int index) ;
int lt_rename(int old_index, int new_index) ;

int lt_newline(int index) ;

int lt_add_piece(int index, uint32_t piece) ;
int lt_add_pieces(int index, uint32_t *pieces, int count) ;

int lt_lines(int index);
int lt_pieces(int index);
int lt_bits(int index) ;
uint32_t ** lt_logic(int index);

void lt_setlines(int index, int lines);
void lt_setbits(int index, int bits) ;

void lt_dump(void) ;

void free_in_table(InTable* in_table);
void setup_in_table(InFile* in_file, InTable* in_table, int clmn);

int huming_weight16(uint32_t a);
int msb16(uint32_t v) ;
int trim_CRLF(char *str) ;

#endif
