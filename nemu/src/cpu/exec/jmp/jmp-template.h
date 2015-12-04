/*************************************************************************
    > File Name: jmp-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年12月04日 星期五 15时18分51秒
 ************************************************************************/
#include "cpu/exec/template-start.h"

#define instr jmp

static void do_execute() {
	cpu.eip += op_src->val;
	print_asm_template2();
}

make_instr_helper(i)


#include "cpu/exec/template-end.h"
