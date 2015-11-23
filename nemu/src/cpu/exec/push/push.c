/*************************************************************************
    > File Name: push.c
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年11月20日 星期五 16时08分43秒
 ************************************************************************/

#include "cpu/exec/helper.h"
//#include "cpu/helper.h"
#include "memory/memory.h"

/*
#define DATA_BYTE 2
#include "push-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "push-template.h"
#undef DATA_BYTE
*/
make_helper(push)
{
	//printf("%x\n",ops_decoded.opcode & 7);
	//printf("%x\n",cpu.gpr[ops_decoded.opcode & 7]._32);

	swaddr_write(cpu.esp-4, 4, cpu.gpr[ops_decoded.opcode & 7]._32);
//	MEM_W(cpu.sp-4, REG(op_decoded.opcode & 5));
	cpu.sp -= 4;
	print_asm_template1();
	return 1;
}
