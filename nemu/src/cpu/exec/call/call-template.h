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
	cpu.esp -= 4;
	swaddr_write(reg_l(R_ESP), 4, cpu.eip + DATA_BYTE);
//	MEM_W(cpu.esp, cpu.eip + DATA_BYTE);

#if DATA_BYTE == 2
	cpu.eip = (cpu.eip + op_src->val) & 0xffff;
#elif DATA_BYTE == 4
	cpu.eip = cpu.eip + op_src->val;
#endif

//	cpu.eip = cpu.eip + op_src->simm;
	print_asm_template1();
	return;
}

make_instr_helper(i);



#include "cpu/exec/template-end.h"

