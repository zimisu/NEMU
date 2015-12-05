/*************************************************************************
    > File Name: ret.c
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年12月04日 星期五 17时27分59秒
 ************************************************************************/

#include "cpu/exec/helper.h"
#include "memory/memory.h"

make_helper(ret)
{
	cpu.eip = swaddr_read(cpu.esp, 4);
	cpu.esp += 4;
	print_asm_template1();
	return 1;
}
