/*************************************************************************
    > File Name: ret.c
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年12月04日 星期五 17时27分59秒
 ************************************************************************/

#include "cpu/exec/helper.h"
#include "memory/memory.h"

#define DATA_BYTE 4
#include "cpu/exec/template-start.h"
make_helper(ret)
{
	cpu.eip = swaddr_read(cpu.esp, 4);
	cpu.esp += 4;
	//print_asm_template1();
	if (DATA_BYTE == 2) cpu.eip &= 0xffff;
	print_asm("ret");
	return 0;
}
#undef DATA_BYTE

#include "cpu/exec/template-end.h"
