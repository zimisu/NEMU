/*************************************************************************
    > File Name: cmp-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年11月22日 星期日 15时33分45秒
 ************************************************************************/
#include "cpu/exec/template-start.h"

#define instr cmp

static void do_execute()
{
	int bits = DATA_BYTE << 3;
	uint32_t mask = (1 << bits) - 1;
    if (mask == 0) mask = 0xffffffff;
	DATA_TYPE a = op_dest->val & mask;
	DATA_TYPE b = op_src->val & mask;
    printf("%d %d\n", a, b);
	DATA_TYPE ans = a - b;
	
	cpu.EFLAGS.CF = (b > a);
	cpu.EFLAGS.ZF = (ans == 0);
	cpu.EFLAGS.OF = (((a ^ b) & ans & b)>> (bits - 1)) & 1;
	cpu.EFLAGS.SF = MSB(ans);
    printf("%d%d%d", cpu.EFLAGS.CF, cpu.EFLAGS.ZF, cpu.EFLAGS.OF);

    //printf("ZF:%d CF:%d SF:%d\n%", cpu.EFLAGS.ZF, cpu.EFLAGS.CF, cpu.EFLAGS.SF);
	DATA_TYPE tmp = ans & 0xff;
	tmp = tmp & (tmp >> 4);
	tmp = tmp & (tmp >> 2);
	tmp = tmp & (tmp >> 1);
	cpu.EFLAGS.PF = tmp ^ 1;

	print_asm_template2();
}

#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
make_instr_helper(r2rm)
make_instr_helper(i2rm)
make_instr_helper(rm2r)
#endif

#if DATA_BYTE == 1
make_instr_helper(r2rm)
make_instr_helper(rm2r)
make_instr_helper(i2rm)
#endif

#include "cpu/exec/template-end.h"
