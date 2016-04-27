#include "cpu/exec/template-start.h"

#define instr cmps

static void do_execute() {
	op_src->type = op_dest->type = OP_TYPE_REG;
	op_src->reg = R_ESI; 
	op_dest->reg = R_EDI;
	
	op_src->val = swaddr_read(cpu.edi, DATA_BYTE, R_ES);
	op_dest->val = swaddr_read(cpu.esi, DATA_BYTE, R_DS);
	
	DATA_TYPE result = op_dest->val - op_src->val;
	if(op_dest->val < op_src->val) cpu.EFLAGS.CF = 1; else cpu.EFLAGS.CF = 0;
	cpu.EFLAGS.OF = MSB(op_dest->val) == (MSB(op_src->val) ^ 1) && MSB(op_dest->val) != MSB(result);
	cpu.EFLAGS.ZF = result == 0;
	cpu.EFLAGS.SF = MSB(result);
	cpu.EFLAGS.PF = get_pf(result);
	cpu.edi += cpu.EFLAGS.DF == 0 ? DATA_BYTE : -DATA_BYTE;
	cpu.esi += cpu.EFLAGS.DF == 0 ? DATA_BYTE : -DATA_BYTE;
	print_asm_template2();
}

make_instr_helper(none)

#include "cpu/exec/template-end.h"
