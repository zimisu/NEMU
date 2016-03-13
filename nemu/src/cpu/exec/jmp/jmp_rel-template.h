/*************************************************************************
    > File Name: jmp-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年12月04日 星期五 15时18分51秒
 ************************************************************************/
#include "cpu/exec/template-start.h"

#define instr jmp_rel

static void do_execute() {
	cpu.eip += op_src->val;
    if (DATA_BYTE == 2) cpu.eip &= 0xffff;
	int CODE_LEN = DATA_BYTE + 1;
	if (DATA_BYTE == 4) CODE_LEN += 1;
    if (op_dest->type == OP_TYPE_REG)
        print_asm("jmp" str(SUFFIX) " %%%s", op_dest->str);
    else print_asm("jmp" str(SUFFIX) " *0x%x", cpu.eip + CODE_LEN);
}

make_instr_helper(rm)
make_instr_helper(si)


#include "cpu/exec/template-end.h"
