#ifndef _READFILE_H_
#define _READFILE_H_

//　入力ファイル　正規化済み
typedef struct tagInFile{
	int nline ;			//	入力データ行数
	int logic_bits ;	//	入力部分のビット数
	uint32_t* logic ;
	int out_bits ;		//	出力の桁数
	char ** out ;
} InFile ;


int read_in_file(InFile* in_file, char* filename);

#endif
