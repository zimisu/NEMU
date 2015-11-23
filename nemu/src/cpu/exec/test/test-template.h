/*************************************************************************
    > File Name: test-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年11月20日 星期五 20时54分52秒
 ************************************************************************/
#include "cpu/exec/template-start.h"

#define instr test

static void do_execute()
{
	uint32_t result = op_src->val & op_src->val;
	if (DATA_BYTE == 2) result &= 0xffff;
	//printf("test_ result= %x\n", result);
	cpu.EFLAGS.ZF = (result == 0);
	//printf("zf = %x\n", cpu.EFLAGS.ZF);
	cpu.EFLAGS.CF = cpu.EFLAGS.OF = 0;
	cpu.EFLAGS.SF = (result >> 31) & 1;
	uint32_t tmp = result;
	tmp = tmp & (tmp << 16);
	tmp = tmp & (tmp << 8);
	tmp = tmp & (tmp << 4);
	tmp = tmp & (tmp << 2);
	tmp = tmp & (tmp << 1);
	cpu.EFLAGS.PF = (tmp >> 31) & 1;
		print_asm_template2();
}

make_instr_helper(rm)

#include "cpu/exec/template-end.h"
