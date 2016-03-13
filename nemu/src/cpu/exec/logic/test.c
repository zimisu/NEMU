/*************************************************************************
    > File Name: test.c
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年11月20日 星期五 20时52分45秒
 ************************************************************************/
#include "cpu/exec/helper.h"


#define DATA_BYTE 1
#include "test-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "test-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "test-template.h"
#undef DATA_BYTE

make_helper_v(test_i2a)
make_helper_v(test_i2rm)
make_helper_v(test_r2rm)

