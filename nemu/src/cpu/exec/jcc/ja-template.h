#include "cpu/exec/template-start.h"

#define instr ja

static void do_execute() {
    int l = DATA_BYTE << 3;
    int mask = 0xffffffff;
    if (DATA_BYTE == 1) mask = 0xff;
    else if (DATA_BYTE == 2) mask = 0xffff;
    printf("op_src->val : %x\n", op_src->val);
	if (cpu.EFLAGS.ZF == 0 &&  cpu.EFLAGS.CF == 0)
	{
        //cpu.eip += op_src->val;
		cpu.eip = ((cpu.eip>>l)<<l)+((cpu.eip + op_src->val) & mask);
        if (DATA_BYTE == 2)
            cpu.eip &= 0xffff;
	}
	print_asm_template1();
}




make_instr_helper(si)


#include "cpu/exec/template-end.h"
