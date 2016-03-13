/*************************************************************************
    > File Name: add-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年12月04日 星期五 16时30分50秒
 ************************************************************************/

#include "cpu/exec/template-start.h"

#define instr add

static void do_execute(){
	//int bits = DATA_BYTE << 3;
	DATA_TYPE_S a = op_dest->val;
	DATA_TYPE_S b = op_src->val;
	DATA_TYPE_S ans = op_dest->val + op_src->val;
   // printf("%x %x %x\n", a, b, ans);
	
	OPERAND_W(op_dest, ans);

	cpu.EFLAGS.CF = MSB(a) + MSB(b) > MSB(ans);
	cpu.EFLAGS.ZF = (ans == 0);
	cpu.EFLAGS.OF = MSB(a) == MSB(b) && MSB(a) != MSB(ans);
	cpu.EFLAGS.SF = MSB(ans);

	cpu.EFLAGS.PF = get_pf(ans);

    printf("0x%x 0x%x a+b = 0x%x CF=%d, OF=%d, ZF=%d\n", a, b, ans, cpu.EFLAGS.CF, cpu.EFLAGS.OF, cpu.EFLAGS.ZF);

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
