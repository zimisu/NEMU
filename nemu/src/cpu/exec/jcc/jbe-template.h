/*************************************************************************
    > File Name: jbe-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年12月04日 星期五 15时37分26秒
 ************************************************************************/
#include "cpu/exec/template-start.h"

#define instr jbe

static void do_execute() {
	if (cpu.EFLAGS.ZF == 1 || cpu.EFLAGS.CF == 1)
	{
		printf("%x\n", op_src->val);
		cpu.eip += op_src->val & 0xff;
		print_asm_template2();
	}
}

make_instr_helper(i)


#include "cpu/exec/template-end.h"
