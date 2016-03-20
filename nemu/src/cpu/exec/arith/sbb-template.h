#include "cpu/exec/template-start.h"

#define instr sbb

static void do_execute() {
	if (op_src->size == 1 && op_dest->size > 1 && op_src->val & 0x80)
	{
		op_src->val |= 0xffffff00;
		if (DATA_BYTE == 2) op_src->val &= 0xffff;
	}
		//op_src->val = (op_src->val << (DATA_BYTE * 8 - 8)) >> (DATA_BYTE * 8 - 8);
	DATA_TYPE a = op_dest->val;
	DATA_TYPE b = op_src->val;
		
	DATA_TYPE ans =  a - b - cpu.EFLAGS.CF;
	OPERAND_W(op_dest, ans);

	cpu.EFLAGS.CF = op_dest->val < op_src->val + cpu.EFLAGS.CF;
	//cpu.EFLAGS.OF = MSB(a) == (MSB(b) ^ 1) && MSB(a) != MSB(ans);	
	if(MSB(op_dest->val) != MSB(op_src->val) && MSB(ans) != MSB(op_dest->val))
		cpu.EFLAGS.OF = 1; else cpu.EFLAGS.OF = 0;
	cpu.EFLAGS.ZF = (ans == 0);
	cpu.EFLAGS.SF = MSB(ans);
	cpu.EFLAGS.PF = get_pf(ans);

	print_asm_template2();
}

#if DATA_BYTE == 2 || DATA_BYTE == 4

make_instr_helper(si2rm)

#endif

make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)
make_instr_helper(i2a)

#include "cpu/exec/template-end.h"
