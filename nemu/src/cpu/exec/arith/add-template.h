/*************************************************************************
    > File Name: add-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年12月04日 星期五 16时30分50秒
 ************************************************************************/

#include "cpu/exec/template-start.h"

#define instr add

static void do_execute(){
	int bits = DATA_BYTE << 3;
	uint32_t a = op_dest->val;
	uint32_t b = op_src->val;
	uint64_t ans = op_dest->val + op_src->val;
	
	OPERAND_W(op_dest, (uint32_t)ans);

	cpu.EFLAGS.CF = (ans >> bits) & 1;
	cpu.EFLAGS.ZF = (ans == 0);
	cpu.EFLAGS.OF = ((a ^ b ^ ans) >> 31) & 1;
	cpu.EFLAGS.SF = (ans >> 31) & 1;
	uint32_t tmp = 1;
	int i;
	for (i = 0; i < bits-1; i++)
	{
		tmp &= (ans & 1);
		ans >>= 1;
	}
	cpu.EFLAGS.PF = tmp & 1;

	print_asm_template2();
}

#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r2rm)
make_instr_helper(si2rm)
#endif


#include "cpu/exec/template-end.h"
