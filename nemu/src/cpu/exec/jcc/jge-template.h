#include "cpu/exec/template-start.h"

#define instr jge

static void do_execute() {
	if (cpu.EFLAGS.SF == cpu.EFLAGS.OF)
	{
        /*
        int l = DATA_BYTE * 8;
        int mask = 0;
        if (l == 8) mask = 0xff;
        else if (l == 16) mask = 0xffff;
        else mask = 0xffffffff;
		cpu.eip = ((cpu.eip>>l)<<l)+((cpu.eip + op_src->val) & mask);*/
        cpu.eip += op_src->val;
        if (DATA_BYTE == 2) cpu.eip &= 0xffff;
        
	}
	print_asm_template1();
}

make_instr_helper(i)


#include "cpu/exec/template-end.h"
