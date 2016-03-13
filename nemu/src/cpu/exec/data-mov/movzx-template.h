#include "cpu/exec/template-start.h"

#define instr movzx


static void do_execute() {
    uint32_t mask = 0xffffffff;
    if (op_src->size == 1)
       mask = 0xff;
    else if (op_src->size == 2)
        mask = 0xffff;
    OPERAND_W(op_dest, op_src->val & mask);
    
    print_asm_template2();
}


make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
