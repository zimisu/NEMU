/*************************************************************************
    > File Name: push-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年11月20日 星期五 16时08分52秒
 ************************************************************************/

#include "cpu/exec/template-start.h"
#include "cpu/helper.h"

#define instr push

static void do_execute() {
	int len;
	if(DATA_BYTE == 2)len = 2; else len = 4;
	cpu.esp -= len;
	swaddr_write(cpu.esp, len, op_src->val);
	print_asm_template1();
}

#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(rm)
make_instr_helper(r)
#endif

make_instr_helper(i)

#include "cpu/exec/template-end.h"
