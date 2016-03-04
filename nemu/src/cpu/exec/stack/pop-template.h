#include "cpu/exec/template-start.h"
#define instr pop

static void do_execute()
{
    int val = cpu.esp;
    cpu.esp += DATA_BYTE;
    OPERAND_W(op_dest, val);
}

make_instr_helper(rm)
make_instr_helper(r)


#include "cpu/exec/template-end.h"
