#include <stdio.h> 
#include <string.h>
#include <inttypes.h>
#include "xoshiro256starstar.h"


#define LEVEL 1
#define D 1

#if LEVEL == 1
	#define R 12323
	#define BITS 13
	#define N 2*R
	#define W 142
	#define T 134
	#define T1 58487
	#define T1_LOG 15
	#define T2 113497866
	#define T3 23
	#define T4 36
	#define R_64_TAB 193
	#define DIFF 4130
	#define RPUI 16384 
	#define RPUI_TAB 256
	#define RPUI2_TAB 512
	#define LOG2W 6
	
uint64_t permut_2[BITS] = {2,4,16,256,3921,7460,932,6014,191,11835,4007,11503,6958}; 
uint64_t r_mod[BITS] = {2, 2, 2, 2, 2, 2597, 2597, 2597, 2597, 2597, 2597, 2597, 4408};

#elif LEVEL == 3
	#define R 24659
	#define BITS 14
	#define N 2*R
	#define W 206
	#define T 199
	#define SEUIL(x) (MAX((32768023488 + (uint64_t)11306501 * (x)) >> 31, 52))
	#define T1 11306501
	#define T1_LOG 23
	#define T2 32768023488
	#define T3 31
	#define T4 52
	#define R_64_TAB 386
	#define RPUI 32768
	#define RPUI_TAB 512
	#define RPUI2_TAB 1024
	#define LOG2W 7
	
uint64_t permut_2[BITS] = {2,4,16,256,16218,10630,9362,8958,5378,22536,19191,12316,6347, 16262}; 
uint64_t r_mod[BITS] = {2, 2, 2, 2, 7777, 7777, 14906, 14906, 14906, 14906, 14906, 14906, 14906, 3402};
	
#elif LEVEL == 5
	#define R 40973
	#define BITS 15
	#define N 2*R
	#define W 274
	#define T 264
	#define SEUIL(x) (MAX((1199805825 + (uint64_t)269987 * (x)) >> 26, 69))
	#define T1 269987
	#define T1_LOG 18
	#define T2 1199805825
	#define T3 26
	#define T4 69
	#define R_64_TAB 641
	#define RPUI 65536
	#define RPUI_TAB 1024
	#define RPUI2_TAB 2048
	#define LOG2W 7
	
uint64_t permut_2[BITS] = {2,4,16,256,24563,13544,3815,8810,13238,3123,1555,618,13167,13126,411}; 
uint64_t r_mod[BITS] = {2, 8, 8, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 3760, 3760};
#endif

