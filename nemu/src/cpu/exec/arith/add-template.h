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
	DATA_TYPE_S a = op_dest->val;
	DATA_TYPE_S b = op_src->val;
	DATA_TYPE_S ans = op_dest->val + op_src->val;
   // printf("%x %x %x\n", a, b, ans);
	
	OPERAND_W(op_dest, ans);
    printf("a = %x, b = %x, a + b = %x, CF = %d\n", a, b,
            ans, cpu.EFLAGS.CF);
	cpu.EFLAGS.CF = (b > a);
	cpu.EFLAGS.ZF = (ans == 0);
	cpu.EFLAGS.OF = (((a ^ b) & ans & b) >> (bits - 1)) & 1;
    cpu.EFLAGS.OF = ((a ^ b ^ ans) >> (bits - 1)) & 1;
	cpu.EFLAGS.SF = MSB(ans);

	cpu.EFLAGS.PF = get_pf(ans);


	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(rm2r)
make_instr_helper(r2rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif


#include "cpu/exec/template-end.h"
