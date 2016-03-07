/*************************************************************************
    > File Name: jbe.c
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年12月04日 星期五 15时35分58秒
 ************************************************************************/

#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "jbe-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jbe-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jbe-template.h"
#undef DATA_BYTE

make_helper_v(jbe_i)
