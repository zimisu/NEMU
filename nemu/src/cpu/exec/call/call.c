/*************************************************************************
    > File Name: call.c
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年11月20日 星期五 15时17分43秒
 ************************************************************************/

#include "cpu/exec/helper.h"

#define DATA_BYTE 2
#include "call-template.h"
#undef DATA_BYTE 

#define DATA_BYTE 4
#include "call-template.h"
#undef DATA_BYTE 

make_helper_v(call_si)
make_helper_v(call_rm)

