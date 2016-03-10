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
	DATA_TYPE_S a = op_dest->val;
	DATA_TYPE_S b = op_src->val;
	DATA_TYPE_S ans = a - b;
	
	cpu.EFLAGS.CF = b < a;
    printf("%d %d a-b = %d CF=%d\n", a, b, ans, cpu.EFLAGS.CF);
	cpu.EFLAGS.ZF = (ans == 0);
	cpu.EFLAGS.OF = (((a ^ b) & ans & b)>> (bits - 1)) & 1;
	cpu.EFLAGS.SF = MSB(ans);
    //printf("%d%d%d\n", cpu.EFLAGS.ZF, cpu.EFLAGS.CF, cpu.EFLAGS.SF);

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
