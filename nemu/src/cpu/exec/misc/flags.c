#include "cpu/exec/helper.h"
#include "cpu/decode/modrm.h"

make_helper(cld)
{
	cpu.EFLAGS.DF = 0;
	print_asm("cld");
	return 1;
}

make_helper(clc)
{
	cpu.EFLAGS.CF = 0;
	print_asm("clc");
	return 1;
}

make_helper(cli)
{
	cpu.EFLAGS.IF = 0;
	print_asm("cli");
	return 1;
}
