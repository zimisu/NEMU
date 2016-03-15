#include "cpu/exec/template-start.h"

#define instr dec

static void do_execute () {
	DATA_TYPE result = op_src->val - 1;
	OPERAND_W(op_src, result);

	if(MSB(op_src->val) == 0 && MSB(result) != MSB(op_src->val))
		cpu.EFLAGS.OF = 1; else cpu.EFLAGS.OF = 0;
	cpu.EFLAGS.ZF = result == 0;
	cpu.EFLAGS.SF = MSB(result);
	cpu.EFLAGS.PF = get_pf(result);

	print_asm_template1();
}

make_instr_helper(rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
#endif

#include "cpu/exec/template-end.h"
