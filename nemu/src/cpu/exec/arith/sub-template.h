/*************************************************************************
    > File Name: sub-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年11月19日 星期四 20时55分04秒
 ************************************************************************/

#include "cpu/exec/template-start.h"

#define instr sub

static void do_execute() {
	printf("%x %x %x %x\n", op_dest->val, op_dest->simm, op_src->val,op_src->simm);
	int bits = DATA_BYTE << 3;
	DATA_TYPE mask = (1 << bits) - 1;
	DATA_TYPE a = op_dest->val & mask;
	DATA_TYPE b = op_src->val & mask;
	DATA_TYPE ans = op_dest->val - op_src->val;
	OPERAND_W(op_dest, ans); 
	
	cpu.EFLAGS.CF = (b > a);
	cpu.EFLAGS.ZF = (a - b == 0);
	cpu.EFLAGS.OF = ((a ^ b ^ (a-b)) >> 31) & 1;
	cpu.EFLAGS.SF = MSB(ans);

	DATA_TYPE tmp = ans & 0xffff;
	tmp = tmp & (tmp >> 4);
	tmp = tmp & (tmp >> 2);
	tmp = tmp & (tmp >> 1);
	cpu.EFLAGS.PF = tmp & 1;

	print_asm_template2();
}


#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
