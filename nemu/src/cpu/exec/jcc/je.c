/*************************************************************************
    > File Name: jcc.c
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年11月22日 星期日 15时52分49秒
 ************************************************************************/

#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "je-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "je-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "je-template.h"
#undef DATA_BYTE

make_helper_v(je_si)

