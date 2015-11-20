/*************************************************************************
    > File Name: push-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年11月20日 星期五 16时08分52秒
 ************************************************************************/

#include "cpu/exec/template-start.h"
#include "cpu/helper.h"

#define instr push

static void do_execute(){
	if (DATA_BYTE == 2)
	{
		MEM_W(cpu.sp-2, REG(op_decoded.opcode & 5));
		cpu.sp -= 2;
	}
	else if (DATA_BYTE == 4)
	{
		MEM_W(cpu.sp-4, REG(op_decoded.opcode & 5));
		cpu.sp -= 4;
	}
	print_asm_template2();
}

#include "cpu/exec/template-end.h"
