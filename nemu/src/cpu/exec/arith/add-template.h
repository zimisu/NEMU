/*************************************************************************
    > File Name: add-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年12月04日 星期五 16时30分50秒
 ************************************************************************/

#include "cpu/exec/template-start.h"

#define instr add

static void do_execute(){
	if(op_src->type == OP_TYPE_IMM &&  op_src->size == 1 && op_src->val & 0x80)
	{
		printf("===============");
		op_src->val |= 0xffffff00;
		if (DATA_BYTE == 2) op_src->val &= 0xffff;
	}
	DATA_TYPE ans = op_dest->val + op_src->val;
	
	OPERAND_W(op_dest, ans);
	
	//cpu.EFLAGS.CF = (((uint64_t)op_dest->val + op_src->val) >> DATA_BYTE * 8) & 1;
	if(ans < op_dest->val && op_src->val > 0) cpu.EFLAGS.CF = 1; else cpu.EFLAGS.CF = 0;
	if(MSB(op_dest->val) == MSB(op_src->val) && MSB(ans) != MSB(op_dest->val))
		cpu.EFLAGS.OF = 1; else cpu.EFLAGS.OF = 0;
	cpu.EFLAGS.ZF = (ans == 0);
	cpu.EFLAGS.SF = MSB(ans);

	cpu.EFLAGS.PF = get_pf(ans);


	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(rm2r)
make_instr_helper(r2rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif


#include "cpu/exec/template-end.h"
