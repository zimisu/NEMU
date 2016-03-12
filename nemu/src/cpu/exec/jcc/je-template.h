/*************************************************************************
    > File Name: je-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年11月22日 星期日 16时15分23秒
 ************************************************************************/
#include "cpu/exec/template-start.h"

#define instr je

static void do_execute() {
	if (cpu.EFLAGS.SF != cpu.EFLAGS.OF)
	{
        int l = DATA_BYTE * 8;
        int mask = 0;
        if (l == 8) mask = 0xff;
        else if (l == 16) mask = 0xffff;
        else mask = 0xffffffff;
		cpu.eip = ((cpu.eip>>l)<<l)+((cpu.eip + op_src->val) & mask);
        
	}
	print_asm_template1();
}

make_instr_helper(si)


#include "cpu/exec/template-end.h"
