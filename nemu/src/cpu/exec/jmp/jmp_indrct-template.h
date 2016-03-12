#include "cpu/exec/template-start.h"

#define instr jmp_indrct

static void do_execute() {
	cpu.eip = op_src->val;
    if (DATA_BYTE == 2) cpu.eip &= 0xffff;
    if (op_dest->type == OP_TYPE_REG)
        print_asm("jmp" str(SUFFIX) " %%%s", op_dest->str);
    else print_asm("jmp" str(SUFFIX) " *0x%x", op_dest->val);
}

make_instr_helper(rm)


#include "cpu/exec/template-end.h"
