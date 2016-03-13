#include "cpu/exec/template-start.h"
#define instr pop

static void do_execute()
{
    int val = cpu.esp;
	//printf("%d %d   ", cpu.esp, DATA_BYTE);
    cpu.esp += DATA_BYTE;
	//printf("%d \n\n", cpu.esp);
	//int opcode = instr_fetch(cpu.eip, 1);
	//if (opcode == 0x8f)
	//{
    	OPERAND_W(op_src, val);
    	print_asm_template1();
	/*} else 
	if (opcode >= 0x58 && opcode < 0x58 + 8)
	{
		reg_l(opcode - 0x58) = val;
		print_asm("pop" str(SUFFIX) " %%%s", REG_NAME(opcode - 0x58));
	}*/
}

make_instr_helper(rm)
make_instr_helper(r)


#include "cpu/exec/template-end.h"
