/*************************************************************************
    > File Name: call-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年11月20日 星期五 15时17分53秒
 ************************************************************************/
#include "cpu/exec/template-start.h"


#define instr call

static void do_execute()
{
	cpu.esp -= 4;
	//swaddr_write(cpu.esp, 4, cpu.eip + get_instr_len());
	swaddr_write(cpu.esp, 4, cpu.eip + DATA_BYTE + 1);

	if (op_src->type == OP_TYPE_IMM)
		cpu.eip += op_src->val;
	else
		cpu.eip = op_src->val - get_instr_len();
		//cpu.eip = op_src->val - 2;
	//printf("%d\n", cpu.eip);
	if (DATA_BYTE == 2) 
		cpu.eip &= 0xffff;
	print_asm("call $0x%x", cpu.eip + get_instr_len());
	//print_asm("call $0x%x", cpu.eip + 2);
	
	//print_asm_template1();
}
make_instr_helper(si);
make_instr_helper(rm);



#include "cpu/exec/template-end.h"

