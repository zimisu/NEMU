#include "cpu/exec/template-start.h"

#define instr movsx


static void do_execute() {
    /*
    int sign = (op_src->val >> (DATA_BYTE * 8 - 1)) & 1;
    if (sign)
        OPERAND_W(op_dest, op_src->val & 0xffffffff);
    else
        OPERAND_W(op_dest, op_src->val);

    print_asm_template2();
    */
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
