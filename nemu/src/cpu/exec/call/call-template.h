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
//	if (DATA_BYTE == 2)
//		REG(REG_EIP) = (REG(REG_EIP) + op_src->val) & 0xffff;
	MEM_W(cpu.esp-DATA_BYTE, cpu.eip);	
	cpu.esp -= DATA_BYTE;
	cpu.eip = (cpu.eip + op_src->val);
/*	else if (DATA_BYTE == 4)
		MEM_W(cpu.esp-4, cpu.eip);
		cpu.esp -= 4;
        cpu.eip = cpu.eip + op_src->val;*/
//		REG(REG_EIP) = REG(REG_EIP) + op_src->val;
	//printf("------------%x\n", cpu.eip);
	print_asm_template1();
}

make_instr_helper(i)



#include "cpu/exec/template-end.h"

