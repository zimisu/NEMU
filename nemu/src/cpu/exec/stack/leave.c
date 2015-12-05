/*************************************************************************
    > File Name: leave.c
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年12月04日 星期五 17时08分15秒
 ************************************************************************/

#include "cpu/exec/helper.h"


make_helper(leave)
{
	cpu.esp = cpu.ebp;
	cpu.ebp = swaddr_read(cpu.esp, 4);
	cpu.esp += 4;
	//print_asm_template1();
	print_asm("leave");
	return 1;
}
