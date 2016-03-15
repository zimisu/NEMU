#include "cpu/exec/helper.h"
#include "cpu/decode/modrm.h"

make_helper(cld)
{
	cpu.EFLAGS.DF = 0;
	return 1;
}

make_helper(clc)
{
	cpu.EFLAGS.CF = 0;
	return 1;
}

make_helper(cli)
{
	cpu.EFLAGS.IF = 0;
	return 1;
}
