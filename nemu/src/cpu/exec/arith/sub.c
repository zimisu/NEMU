/*************************************************************************
    > File Name: sub.c
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年11月19日 星期四 20时51分15秒
 ************************************************************************/

#include "cpu/exec/helper.h"
/*
#define DATA_BYTE 1
#include "sub-template.h"
#undef DATA_BYTE
*/

#define DATA_BYTE 2
#include "sub-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "sub-template.h"
#undef DATA_BYTE

make_helper_v(sub_si2rm)

