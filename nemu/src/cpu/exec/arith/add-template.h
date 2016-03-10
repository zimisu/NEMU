/*************************************************************************
    > File Name: add-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年12月04日 星期五 16时30分50秒
 ************************************************************************/

#include "cpu/exec/template-start.h"

#define instr add

static void do_execute(){
	int bits = DATA_BYTE << 3;
	uint32_t a = op_dest->val;
	uint32_t b = op_src->val;
	DATA_TYPE ans = op_dest->val + op_src->val;
	
	OPERAND_W(op_dest, ans);
    printf("a = %d, b = %d, a + b = %d, CF = %d", a, b,
            ans, cpu.EFLAGS.CF);
	cpu.EFLAGS.CF = (b > a);
	cpu.EFLAGS.ZF = (ans == 0);
	cpu.EFLAGS.OF = (((a ^ b) & ans & b) >> (bits - 1)) & 1;
    cpu.EFLAGS.OF = ((a ^ b ^ ans) >> (bits - 1)) & 1;
	cpu.EFLAGS.SF = MSB(ans);

	cpu.EFLAGS.PF = get_pf(ans);


	print_asm_template2();
}

make_instr_helper(r2rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif


#include "cpu/exec/template-end.h"
