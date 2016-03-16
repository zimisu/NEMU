#include "cpu/exec/template-start.h"

#define exec_template static void do_execute() {\
	if (IF_COND) OPERAND_W(op_dest, op_src->val);\
	print_asm_template2();\
}\
make_instr_helper(rm2r)

/*-------------------------------------------------------------*/
#define instr cmova
#define IF_COND cpu.EFLAGS.CF == 0 && cpu.EFLAGS.ZF == 0
exec_template;
#undef IF_COND
#undef instr

/*-------------------------------------------------------------*/
#define instr cmove
#define IF_COND cpu.EFLAGS.ZF == 1
exec_template;
#undef IF_COND
#undef instr

/*-------------------------------------------------------------*/
#define instr cmovbe
#define IF_COND cpu.EFLAGS.CF == 1 || cpu.EFLAGS.ZF == 1
exec_template;
#undef IF_COND
#undef instr

/*-------------------------------------------------------------*/
#define instr cmovge
#define IF_COND cpu.EFLAGS.SF == cpu.EFLAGS.OF
exec_template;
#undef IF_COND
#undef instr

/*-------------------------------------------------------------*/
#define instr cmovne
#define IF_COND cpu.EFLAGS.ZF == 0
exec_template;
#undef IF_COND
#undef instr

/*-------------------------------------------------------------*/
#define instr cmovns
#define IF_COND cpu.EFLAGS.SF == 0
exec_template;
#undef IF_COND
#undef instr

/*-------------------------------------------------------------*/
#define instr cmovs
#define IF_COND cpu.EFLAGS.SF == 1
exec_template;
#undef IF_COND
#undef instr



#include "cpu/exec/template-end.h"
