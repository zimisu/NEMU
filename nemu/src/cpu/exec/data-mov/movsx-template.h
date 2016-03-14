#include "cpu/exec/template-start.h"

#define instr movsx


static void do_execute() {
	
	uint32_t sign = 1 & (op_src->val >> ((op_src->size << 3) - 1));
	//printf("%d %d %d\n", op_src->type, op_dest->type);		
	printf("%d %d\n", (int)op_src->size, (int)op_dest->size);		
//printf("%d %d   %d %d\n", op_src->type, op_src->size, op_dest->type, op_dest->size);
    //uint32_t sign = MSB(op_src->val);
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
