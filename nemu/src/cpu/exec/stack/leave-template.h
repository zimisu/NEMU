/*************************************************************************
    > File Name: leave-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年12月04日 星期五 17时10分54秒
 ************************************************************************/

#include "cpu/exec/template-start.h"

#define instr leave

static void do_execute(){
	esp = ebp;
	ebp = swaddr_read(esp, 4);
	esp += 4;
	print_asm_template1();
}


#include "cpu/exec/template-end.h"
