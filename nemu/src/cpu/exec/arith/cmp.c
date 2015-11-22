/*************************************************************************
    > File Name: cmp.c
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年11月22日 星期日 15时29分53秒
 ************************************************************************/
#include "cpu/exec/helper.h"

#define DATA_BYTE 2
#include "cmp-template.h"
#undef DATA_BYTE


#define DATA_BYTE 4
#include "cmp-template.h"
#undef DATA_BYTE

make_helper_v(cmp_si2rm)
