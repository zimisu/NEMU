#include "cpu/exec/template-start.h"

#define instr adc

static void do_execute(){
	int bits = DATA_BYTE << 3;
    int sign_bit = 1 << (bits - 1);
	DATA_TYPE_S a = op_dest->val;
	DATA_TYPE_S b = op_src->val;
	DATA_TYPE_S ans = op_dest->val + op_src->val + cpu.EFLAGS.CF;
	
	OPERAND_W(op_dest, ans);
	cpu.EFLAGS.CF = ((a & sign_bit) || (b & sign_bit)) 
        & ((~ans) & sign_bit);
	cpu.EFLAGS.ZF = (ans == 0);
	cpu.EFLAGS.OF = (((a ^ b) & ans & b) >> (bits - 1)) & 1;
    cpu.EFLAGS.OF = ((a ^ b ^ ans) >> (bits - 1)) & 1;
	cpu.EFLAGS.SF = MSB(ans);
 
	cpu.EFLAGS.PF = get_pf(ans);


	print_asm_template2();
}


make_instr_helper(r2rm)
make_instr_helper(i2a)
make_instr_helper(i2r)
make_instr_helper(i2rm)
make_instr_helper(rm2r)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif


#include "cpu/exec/template-end.h"
