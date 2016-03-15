#include "cpu/exec/template-start.h"

#define instr movzb
static void do_execute() {
	printf("%d  %d\n", (int)op_src->size, (int)op_dest->size);
	printf("%d \n", (int)op_dest->reg);
    uint32_t mask = 0xff;
    OPERAND_W(op_dest, op_src->val & mask);
    print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

/*-----------------------------------------------*/
#define instr movzw
static void do_execute() {
    uint32_t mask = 0xffff;
    OPERAND_W(op_dest, op_src->val & mask);
    print_asm_template2();
}

make_instr_helper(rm2r)
#undef instr

#include "cpu/exec/template-end.h"
