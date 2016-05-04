#include "cpu/exec/template-start.h"

#define instr movsp

make_helper(concat(movsp_cr2rm_, SUFFIX)) {
	uint8_t tmp = instr_fetch(eip + 1, 1);
	REG(tmp & 0x7) = cpu.cr._[(tmp >> 3) & 0x7];
	print_asm("movsp" str(SUFFIX) " %%cr%d,%%%s", (tmp >> 3) & 0x7, REG_NAME(tmp & 0x7));
	return 2;
}

make_helper(concat(movsp_rm2cr_, SUFFIX)) {
	uint8_t tmp = instr_fetch(eip + 1, 1);
	cpu.cr._[(tmp >> 3) & 0x7] = REG(tmp & 0x7);
	print_asm("movsp" str(SUFFIX) " %%%s,%%cr%d", REG_NAME(tmp & 0x7), (tmp >> 3) & 0x7);
	return 2;
}


#include "cpu/exec/template-end.h"
