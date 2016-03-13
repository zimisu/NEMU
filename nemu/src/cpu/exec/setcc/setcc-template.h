#include "cpu/exec/template-start.h"



/*----------------------------------------------------*/
#define instr seta
static void do_execute() 
{
	if (cpu.EFLAGS.CF == 0 && cpu.EFLAGS.ZF == 0) 
		OPERAND_W(op_dest, 1);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr
/*----------------------------------------------------*/
#define instr setae
static void do_execute() 
{
	if (cpu.EFLAGS.CF == 0) 
		OPERAND_W(op_dest, 1);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr
/*----------------------------------------------------*/
#define instr setb
static void do_execute() 
{
	if (cpu.EFLAGS.CF) 
		OPERAND_W(op_dest, 1);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr
/*----------------------------------------------------*/
#define instr setbe
static void do_execute() 
{
	if (cpu.EFLAGS.CF || cpu.EFLAGS.ZF) 
		OPERAND_W(op_dest, 1);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr
/*----------------------------------------------------*/
#define instr sete
static void do_execute() 
{
	if (cpu.EFLAGS.ZF) 
		OPERAND_W(op_dest, 1);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr
/*----------------------------------------------------*/
#define instr setg
static void do_execute() 
{
	if (cpu.EFLAGS.ZF == 0 && cpu.EFLAGS.SF == cpu.EFLAGS.OF) 
		OPERAND_W(op_dest, 1);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr
/*----------------------------------------------------*/
#define instr setge
static void do_execute() 
{
	if (cpu.EFLAGS.SF == cpu.EFLAGS.OF) 
		OPERAND_W(op_dest, 1);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr
/*----------------------------------------------------*/
#define instr setle
static void do_execute() 
{
	if (cpu.EFLAGS.ZF || cpu.EFLAGS.SF != cpu.EFLAGS.OF) 
		OPERAND_W(op_dest, 1);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr
/*----------------------------------------------------*/
#define instr setl
static void do_execute() 
{
	if (cpu.EFLAGS.SF != cpu.EFLAGS.OF) 
		OPERAND_W(op_dest, 1);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr
/*----------------------------------------------------*/
#define instr setne
static void do_execute() 
{
	if (cpu.EFLAGS.ZF == 0) 
		OPERAND_W(op_dest, 1);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr
/*----------------------------------------------------*/
#define instr setno
static void do_execute() 
{
	if (cpu.EFLAGS.OF == 0) 
		OPERAND_W(op_dest, 1);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr
/*----------------------------------------------------*/
#define instr setnp
static void do_execute() 
{
	if (cpu.EFLAGS.PF == 0) 
		OPERAND_W(op_dest, 1);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr
/*----------------------------------------------------*/
#define instr setns
static void do_execute() 
{
	if (cpu.EFLAGS.SF == 0) 
		OPERAND_W(op_dest, 1);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr
/*----------------------------------------------------*/
#define instr seto
static void do_execute() 
{
	if (cpu.EFLAGS.OF) 
		OPERAND_W(op_dest, 1);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr
/*----------------------------------------------------*/
#define instr setp
static void do_execute() 
{
	if (cpu.EFLAGS.PF) 
		OPERAND_W(op_dest, 1);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr
/*----------------------------------------------------*/
#define instr sets
static void do_execute() 
{
	if (cpu.EFLAGS.SF) 
		OPERAND_W(op_dest, 1);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr



#include "cpu/exec/template-end.h"
