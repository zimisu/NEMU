/*************************************************************************
    > File Name: add.c
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年12月04日 星期五 16时22分52秒
 ************************************************************************/

#include "cpu/exec/helper.h"

#define DATA_BYTE 2
#include "add-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "add-template.h"
#undef DATA_BYTE

make_helper_v(add_r2rm)

