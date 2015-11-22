/*************************************************************************
    > File Name: cmp-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年11月22日 星期日 15时33分45秒
 ************************************************************************/
#include "cpu/exec/template-start.h"

#define instr cmp

static void do_execute()
{
	int bits = DATA_BYTE << 3;
	uint32_t mask = (1 << bits) - 1;
	printf("op_dest = %x, mask = %x\n", op_dest->val, mask);
	uint32_t a = op_dest->val & mask;
	uint32_t b = op_src->val;
	//OPERAND_W(op_dest, ans); 
	
	cpu.EFLAGS.CF = (b > a);
	cpu.EFLAGS.ZF = (a - b == 0);
	printf("a = %x, b = %x, a-b = %x, zf = %x\n", a,  b , a-b, cpu.EFLAGS.ZF);
	cpu.EFLAGS.OF = ((a ^ b ^ (a-b)) >> 31) & 1;
	cpu.EFLAGS.SF = ((a - b) >> 31) & 1;
	uint32_t tmp = a - b;
	tmp = tmp & (tmp << 16);
	tmp = tmp & (tmp << 8);
	tmp = tmp & (tmp << 4);
	tmp = tmp & (tmp << 2);
	tmp = tmp & (tmp << 1);
	cpu.EFLAGS.PF = (tmp >> 31) & 1;

	print_asm_template2();
}

#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(rm_imm)
#endif

#include "cpu/exec/template-end.h"
