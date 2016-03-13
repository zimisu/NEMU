/*************************************************************************
    > File Name: jmp-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年12月04日 星期五 15时18分51秒
 ************************************************************************/
#include "cpu/exec/template-start.h"

#define instr jmp

static void do_execute() {
	int len = get_instr_len();
	if(op_src->type == OP_TYPE_IMM) {
		cpu.eip += op_src->val;
		//snprintf(op_src->str, OP_STR_SIZE, "$0x%x", cpu.eip + len + 1);
	} else {
		cpu.eip = op_src->val - len - 1;
	}
	print_asm("jmp" str(SUFFIX) "%x\n", cpu.eip + len);
}


make_instr_helper(rm)
make_instr_helper(si)


#include "cpu/exec/template-end.h"
