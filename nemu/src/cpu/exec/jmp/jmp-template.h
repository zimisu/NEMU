/*************************************************************************
    > File Name: jmp-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年12月04日 星期五 15时18分51秒
 ************************************************************************/
#include "cpu/exec/template-start.h"

#define instr jmp

#if DATA_BYTE == 1
#define CODE_LEN 2
#endif
#if DATA_BYTE == 2
#define CODE_LEN 4
#endif
#if DATA_BYTE == 4
#define CODE_LEN 6
#endif

static void do_execute() {
	//int len = get_instr_len();
	if(op_src->type == OP_TYPE_IMM) {
		cpu.eip += op_src->val;
	} else {
		cpu.eip = op_src->val - get_instr_len();
	}
	if (DATA_BYTE == 2) cpu.eip &= 0xffff;	
	print_asm("jmp" str(SUFFIX) " $%x\n", cpu.eip + get_instr_len());
}
#undef CODE_LEN


make_instr_helper(rm)
make_instr_helper(si)

void load_sreg(uint32_t);

make_helper(concat(ljmp_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	uint16_t sreg = instr_fetch(eip + 5, 2);
	cpu.cs = sreg;
	load_sreg(R_CS);
//	printf("%x\n", cpu.cs);
	cpu.eip = addr - 7;
	print_asm("ljmp" str(SUFFIX) " $0x%x,$0x%x", sreg, addr);
	return 7;
}

#include "cpu/exec/template-end.h"
