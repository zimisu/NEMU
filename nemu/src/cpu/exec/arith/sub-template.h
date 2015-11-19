/*************************************************************************
    > File Name: sub-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年11月19日 星期四 20时55分04秒
 ************************************************************************/

#include "cpu/exec/template-start.h"

#define instr sub

static void do_execute() {
	int bits = DATA_BYTE << 3;
	uint64_t mask = (1 << bits) - 1;
	OPERAND_W(op_dest, (op_dest->val & mask) - op_src->val); 
	

	print_asm_template2();
}


#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif


#include "cpu/exec/template-end.h"
