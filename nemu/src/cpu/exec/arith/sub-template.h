/*************************************************************************
    > File Name: sub-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年11月19日 星期四 20时55分04秒
 ************************************************************************/

#include "cpu/exec/template-start.h"

#define instr sub


static void do_execute() {
//	printf("%x %x %x %x\n", op_dest->val, op_dest->simm, op_src->val,op_src->simm);
	//int bits = DATA_BYTE << 3;
	DATA_TYPE a = op_dest->val;
	DATA_TYPE b = op_src->val;
	DATA_TYPE ans = a - b;
	OPERAND_W(op_dest, ans); 
	
	//uint64_t tmp = (uint64_t)a - b;
	//cpu.EFLAGS.CF = (tmp >> 8 * DATA_BYTE) & 1;
	cpu.EFLAGS.CF = a < b;
	cpu.EFLAGS.ZF = (ans == 0);
	cpu.EFLAGS.OF = MSB(a) == (MSB(b) ^ 1) && MSB(a) != MSB(ans);
	//cpu.EFLAGS.OF = (((a ^ b) & ans & b) >> (bits - 1)) & 1;
	cpu.EFLAGS.SF = MSB(ans);

	cpu.EFLAGS.PF = get_pf(ans);

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
