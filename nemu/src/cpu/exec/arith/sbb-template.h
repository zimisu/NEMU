#include "cpu/exec/template-start.h"

#define instr sbb

static void do_execute() {
	DATA_TYPE a = op_dest->val;
	DATA_TYPE b = op_src->val;
	DATA_TYPE ans =  a - b - cpu.EFLAGS.CF;
	OPERAND_W(op_dest, ans);

	cpu.EFLAGS.CF = op_dest->val < op_src->val + cpu.EFLAGS.CF;
	cpu.EFLAGS.OF = MSB(a) == (MSB(b) ^ 1) && MSB(a) != MSB(ans);	
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
