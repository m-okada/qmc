/*

	入力ファイルのパース

*/
// #define NODEBUG
#include <assert.h>


//#include <unistd.h>
#include <stdint.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "qmc.h"
#include "qmc_misc.h"
#include "readfile.h"

static int count_textsize(char *filename, int *in_file_numline, int *in_file_maxlen);

//	in_fileへ行を追加
static signed int parse_line(InFile* in_file, unsigned char *line, int pos)
{
	int state = 0;
	uint32_t logic = 0;
	char *out ;
	int logic_len=0 ;
	int out_buff_len=32 ;
	int out_len=0 ;

	out=malloc(out_buff_len) ;

	while (*line) {
		switch (state) {
		case 0:
			if (*line == ' ' || *line == '\t') {
				break;
			}
			else if (*line == '0' || *line == '1') {
				state = 1;
				continue;
			}
			else if(*line==0xEF || *line==0xBB || *line==0xBF){	//	UTF BOM
				break ;
			}
			else {
				return -2;
			}
			break;
		case 1:
			if (*line == '0' || *line == '1') {
				logic <<= 1;
				logic += *line - '0';
				logic_len++ ;
			}
			else {
				state = 2;
				continue;
			}
			break;
		case 2:				//  skip white spaces.
			if (*line == ' ' || *line == '\t') {
				break ;
			}
			else{
				state=3 ;
				continue ;
			}
			break ;
		case 3:
			if (*line == '0' || *line == '1' || *line == 'x') {
				out[out_len]=*line ;
				out_len++ ;
			}
			break;
		}

		if(out_len>=out_buff_len){
			out_buff_len*=2 ;
			out=realloc(out, out_buff_len) ;
		}
		line++;
	}
	if(state==3){	//	最後まで読んだ
		if(out_len==0) return -3 ;	//	出力が未定義
		out[out_len]=0 ;

		if(in_file->logic_bits<logic_len){
			in_file->logic_bits=logic_len;
		}
		in_file->logic[pos]=logic ;
		in_file->out[pos]=out ;
		return logic ;
	}
	return -1;
}


int read_in_file(InFile* in_file, char* filename)
{
	FILE *fp;
	int i ;
	char* linebuff ;
	int linebuff_len ;
	int buffsize = 32;
	int nline = 0;
	int out_len=0 ;

	count_textsize(filename, &buffsize, &linebuff_len) ;
	if(buffsize==0 || linebuff_len==0) return -1 ;

	in_file->logic_bits=0 ;
	in_file->nline=0 ;
	in_file->out_bits=0 ;

	in_file->logic = malloc((sizeof (uint32_t *)) * buffsize);
	in_file->out= malloc((sizeof (char **)) * buffsize);

	linebuff_len+=2 ;
	linebuff=malloc(linebuff_len) ;

	fp = fopen(filename, "r");

	for(i=0 ; i<buffsize ; i++){
		if(fgets(linebuff, linebuff_len, fp)==NULL){
			break ;
		}
		trim_CRLF(linebuff) ;

		int ret = parse_line(in_file, (unsigned char *)linebuff, nline);
		if(ret<0) continue ;

		if(out_len<strlen(in_file->out[nline])){
			out_len=strlen(in_file->out[nline]) ;
		}

		nline++;
		if (nline > buffsize) {
			buffsize *= 2;
			in_file->logic = realloc(in_file->logic, (sizeof (uint32_t *)) * buffsize);
			in_file->out = (char **)realloc(in_file->out, (sizeof (char **)) * buffsize);
		}
	}

	fclose(fp) ;

	in_file->out_bits=out_len ;

	for(i=0 ; i<nline ; i++){
		if(strlen(in_file->out[i])!=out_len){
			int n ;
			in_file->out[i]=realloc(in_file->out[i], out_len+1) ;
			for(n=strlen(in_file->out[i]) ; n<out_len ; n++){
				in_file->out[i][n]='x' ;
			}
			in_file->out[i][n]=0 ;
		}
	}

	in_file->nline=nline ;
	free(linebuff) ;

	return nline ;
}


//  ファイルの最大行の文字数と行数をカウントする。

#define GET_MAX_CHUNK_SIZE 32

static int count_textsize(char *filename, int *in_file_numline, int *in_file_maxlen)
{
	int len = 0;

	FILE *fp;
	char buff[GET_MAX_CHUNK_SIZE + 1];

	in_file_numline[0] = 0 ;
	in_file_maxlen[0] = 0;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		return 0;
	}

	int r_len = 0;

	while (1) {
		buff[0] = 0;
		char *r = fgets(buff, GET_MAX_CHUNK_SIZE + 1, fp);
		if (r == NULL)
			break;

		r_len = strlen(buff);
		if (r_len == 0) {
			break;
		}
		else if (buff[r_len - 1] == '\x0d' || buff[r_len - 1] == '\x0a') {
			in_file_numline[0]++;
			len += r_len - 1;
			if (len > in_file_maxlen[0]) in_file_maxlen[0] = len;
			len = 0;
		}
		else {
			len += r_len;
		}
		if (feof(fp)) {
			if (len > 0) {		//  最後の行が改行無しだった
				in_file_numline[0]++;
				if (len > *in_file_maxlen)
					in_file_maxlen[0] = len;
			}
			break;
		}
	}
	fclose(fp) ;

	return in_file_maxlen[0] ;
}


