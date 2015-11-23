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
	
	MEM_W(cpu.sp-DATA_BYTE, REG(op_decoded.opcode & 7));
	cpu.sp -= DATA_BYTE;
	
	print_asm_template2();
}

#include "cpu/exec/template-end.h"
