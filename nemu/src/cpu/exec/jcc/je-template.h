/*************************************************************************
    > File Name: je-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年11月22日 星期日 16时15分23秒
 ************************************************************************/
#include "cpu/exec/template-start.h"

#define instr je

static void do_execute() {
	if (cpu.EFLAGS.ZF == 1)
	{
        //printf("jump!\n");
		cpu.eip = (cpu.eip>>8<<8)+((cpu.eip + op_src->val) & 0xff);
	}
    print_asm_template1();
}

make_instr_helper(i)


#include "cpu/exec/template-end.h"
