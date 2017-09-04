#include <stdio.h>

static const int popc_table[16] = {
	0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4
};

int huming_weight16(int a)
{
	a &= 0xffff ;
	return
		popc_table[a & 0x0f] +
		popc_table[(a >> 4) & 0x0f] +
		popc_table[(a >> 8) & 0x0f] +
		popc_table[(a >> 12) & 0x0f];
}

int mask_table[4096] ;

int main(void){
	int i, bit ;
	int pos=0 ;

	for(bit=0 ; bit<=0xfff ; bit++){
		for(i=0 ; i<=0xfff ; i++){
			if(huming_weight16(i)==bit){
				mask_table[pos]=i ;
				pos++ ;
			}
		}
	}

	printf("int mask_table[4096]={");
	for(i=0 ; i<=0xfff ; i++){
		printf("0x%03x, ", mask_table[i]) ;
		if((i & 0x0f)==0) printf("\n") ;
	}
	printf("\n};\n");

	return 0 ;
}
