/*************************************************************************
    > File Name: call-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年11月20日 星期五 15时17分53秒
 ************************************************************************/
#include "cpu/exec/template-start.h"

#define instr call
/*
static void do_execute()
{
	cpu.esp -= 4;
	swaddr_write(cpu.esp, 4, cpu.eip + get_instr_len());

	if (op_src->type == OP_TYPE_IMM)
		cpu.eip += op_src->val;
	else
		cpu.eip = op_src->val - get_instr_len() - 1;
	//if (DATA_BYTE == 2) cpu.eip &= 0xffff;

	print_asm("call 0x%x", cpu.eip + get_instr_len());
	//print_asm_template1();
}*/

static void do_execute() {
	int len = get_instr_len();
	cpu.esp -= 4;
	swaddr_write(cpu.esp, 4, cpu.eip + len);
	if(op_src->type == OP_TYPE_IMM) {
		cpu.eip += op_src->val;
		snprintf(op_src->str, OP_STR_SIZE, "$0x%x", cpu.eip + len + 1);
	}else {
		cpu.eip = op_src->val - len - 1;
	}
	print_asm_template1();
}


make_instr_helper(si);
make_instr_helper(rm);



#include "cpu/exec/template-end.h"

