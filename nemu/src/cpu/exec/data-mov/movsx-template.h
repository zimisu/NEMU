#include "cpu/exec/template-start.h"

#define instr movsx


static void do_execute() {
    uint32_t sign = (op_src->val >> (DATA_BYTE * 8 - 1)) & 1;
    uint32_t mask = 0;
    if (op_src->size == 1 && op_dest->size == 2 && sign)
       mask = 0xff00;
    else if (op_src->size == 1 && op_dest->size == 4 && sign)
        mask = 0xffffff00;
    else if (op_src->size == 2 && op_dest->size == 4 && sign)
        mask = 0xffff0000;
    OPERAND_W(op_dest, op_src->val | mask);
    
    print_asm_template2();
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
