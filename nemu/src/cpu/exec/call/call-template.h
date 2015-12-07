/*************************************************************************
    > File Name: call-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年11月20日 星期五 15时17分53秒
 ************************************************************************/
#include "cpu/exec/template-start.h"

#define instr call

static void do_execute()
{
	MEM_W(cpu.esp-4, cpu.eip + DATA_BYTE);	
	cpu.esp -= 4;
#if DATA_BYTE == 2
	cpu.eip = (cpu.eip + op_src->simm) & 0xffff;
#elif DATA_BYTE == 4
	cpu.eip = cpu.eip + op_src->simm;
#endif
	print_asm_template1();
}

make_instr_helper(i);



#include "cpu/exec/template-end.h"

