#include "cpu/exec/template-start.h"

#define instr movs

static void do_execute() {
	swaddr_write(cpu.edi, DATA_BYTE, swaddr_read(cpu.esi, DATA_BYTE, R_DS));
	cpu.edi += cpu.EFLAGS.DF == 0? DATA_BYTE : -DATA_BYTE;
	cpu.esi += cpu.EFLAGS.DF == 0? DATA_BYTE : -DATA_BYTE;
	if (DATA_BYTE == 2)
		print_asm("movs" str(SUFFIX) " %%si,%%di");
	else
		print_asm("movs" str(SUFFIX) " %%esi,%%edi");
}

make_instr_helper(none)

#include "cpu/exec/template-end.h"
