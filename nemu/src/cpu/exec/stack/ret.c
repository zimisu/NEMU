/*************************************************************************
    > File Name: ret.c
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年12月04日 星期五 17时27分59秒
 ************************************************************************/

#include "cpu/exec/helper.h"
#include "memory/memory.h"

#define DATA_BYTE 2
#include "ret-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "ret-template.h"
#undef DATA_BYTE

/*
make_helper(ret)
{
	cpu.eip = swaddr_read(cpu.esp, 4);
	cpu.esp += 4;
	if (DATA_BYTE == 2) cpu.eip &= 0xffff;
	print_asm("ret");
	return 0;
}
*/
#include "cpu/exec/template-end.h"
