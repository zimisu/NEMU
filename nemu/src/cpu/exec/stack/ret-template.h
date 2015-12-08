/*************************************************************************
    > File Name: ret-template.h
    > Author: Chen Kan
    > Mail: 14307130198@fudan.edu.cn 
    > Created Time: 2015年12月04日 星期五 17时29分35秒
 ************************************************************************/

#include "cpu/exec/template-start.h"

#define instr ret
/*
static void do_execute(){
	eip = swaddr_read(esp, 4);
	esp += 4;
	print_asm_template1();
}
*/

#include "cpu/exec/template-end.h"
