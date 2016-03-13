#include "cpu/exec/template-start.h"

		//new_eip = (new_eip << (32 - l)) >> (32 - l);

#define get_new_eip()\
		int CODE_LEN = 0;\
		if (DATA_BYTE == 1) CODE_LEN = 2; else\
		if (DATA_BYTE == 2) CODE_LEN = 4; else\
		if (DATA_BYTE == 4) CODE_LEN = 6;\
		int32_t new_eip = op_src->val + cpu.eip;\
       	 	if (DATA_BYTE == 2) new_eip &= 0xffff;

/*----------------------------------------------------*/
#define instr je
static void do_execute() 
{
	get_new_eip()
	if (cpu.EFLAGS.ZF == 1)
		cpu.eip = new_eip;
	print_asm(str(instr) " $0x%x", new_eip + CODE_LEN);
}
make_instr_helper(si)
#undef instr
/*----------------------------------------------------*/
#define instr ja
static void do_execute() 
{
	get_new_eip()
	if (cpu.EFLAGS.ZF == 0 && cpu.EFLAGS.CF == 0)
		cpu.eip = new_eip;
	print_asm(str(instr) " $0x%x", new_eip + CODE_LEN);
}
make_instr_helper(si)
#undef instr
/*----------------------------------------------------*/
#define instr jle
static void do_execute() 
{	
	//printf("cf:%d zf:%d sf:%d of:%d\n", 
		//	cpu.EFLAGS.CF, cpu.EFLAGS.ZF, cpu.EFLAGS.SF, cpu.EFLAGS.OF);
	get_new_eip()
	if (cpu.EFLAGS.ZF == 1 || cpu.EFLAGS.SF != cpu.EFLAGS.OF)
		cpu.eip = new_eip;
	print_asm(str(instr) " $0x%x", new_eip + CODE_LEN);
}
make_instr_helper(si)
#undef instr
/*----------------------------------------------------*/
#define instr jbe
static void do_execute() 
{
	get_new_eip()
	if (cpu.EFLAGS.ZF == 1 || cpu.EFLAGS.CF == 1)
		cpu.eip = new_eip;
	print_asm(str(instr) " $0x%x", new_eip + CODE_LEN);
}
make_instr_helper(si)
#undef instr
/*----------------------------------------------------*/
#define instr jae
static void do_execute() 
{
	get_new_eip()
	if (cpu.EFLAGS.CF == 0)
		cpu.eip = new_eip;
	print_asm(str(instr) " $0x%x", new_eip + CODE_LEN);
}
make_instr_helper(si)
#undef instr
/*----------------------------------------------------*/
#define instr jb
static void do_execute() 
{
	get_new_eip()
	if (cpu.EFLAGS.CF == 1)
		cpu.eip = new_eip;
	print_asm(str(instr) " $0x%x", new_eip + CODE_LEN);
}
make_instr_helper(si)
#undef instr
/*----------------------------------------------------*/
#define instr jg
static void do_execute() 
{
	get_new_eip()
	if (cpu.EFLAGS.ZF == 0 && cpu.EFLAGS.SF == cpu.EFLAGS.OF)
		cpu.eip = new_eip;
	print_asm(str(instr) " $0x%x", new_eip + CODE_LEN);
}
make_instr_helper(si)
#undef instr
/*----------------------------------------------------*/
#define instr jge
static void do_execute() 
{
	get_new_eip()
	if (cpu.EFLAGS.SF == cpu.EFLAGS.OF)
		cpu.eip = new_eip;
	print_asm(str(instr) " $0x%x", new_eip + CODE_LEN);
}
make_instr_helper(si)
#undef instr
/*----------------------------------------------------*/
#define instr jl
static void do_execute() 
{
	get_new_eip()
	if (cpu.EFLAGS.SF != cpu.EFLAGS.OF)
		cpu.eip = new_eip;
	print_asm(str(instr) " $0x%x", new_eip + CODE_LEN);
}
make_instr_helper(si)
#undef instr
/*----------------------------------------------------*/
#define instr jne
static void do_execute() 
{
	get_new_eip()
	if (cpu.EFLAGS.ZF == 0)
		cpu.eip = new_eip;
	print_asm(str(instr) " $0x%x", new_eip + CODE_LEN);
}
make_instr_helper(si)
#undef instr
/*----------------------------------------------------*/
#define instr jno
static void do_execute() 
{
	get_new_eip()
	if (cpu.EFLAGS.OF == 0)
		cpu.eip = new_eip;
	print_asm(str(instr) " $0x%x", new_eip + CODE_LEN);
}
make_instr_helper(si)
#undef instr
/*----------------------------------------------------*/
#define instr jnp
static void do_execute() 
{
	get_new_eip()
	if (cpu.EFLAGS.PF == 0)
		cpu.eip = new_eip;
	print_asm(str(instr) " $0x%x", new_eip + CODE_LEN);
}
make_instr_helper(si)
#undef instr
/*----------------------------------------------------*/
#define instr jns
static void do_execute() 
{
	get_new_eip()
	if (cpu.EFLAGS.SF == 0)
		cpu.eip = new_eip;
	print_asm(str(instr) " $0x%x", new_eip + CODE_LEN);
}
make_instr_helper(si)
#undef instr
/*----------------------------------------------------*/
#define instr jo
static void do_execute() 
{
	get_new_eip()
	if (cpu.EFLAGS.OF == 1)
		cpu.eip = new_eip;
	print_asm(str(instr) " $0x%x", new_eip + CODE_LEN);
}
make_instr_helper(si)
#undef instr
/*----------------------------------------------------*/
#define instr jp
static void do_execute() 
{
	get_new_eip()
	if (cpu.EFLAGS.PF == 1)
		cpu.eip = new_eip;
	print_asm(str(instr) " $0x%x", new_eip + CODE_LEN);
}
make_instr_helper(si)
#undef instr
/*----------------------------------------------------*/
#define instr js
static void do_execute() 
{
	get_new_eip()
	if (cpu.EFLAGS.SF == 0)
		cpu.eip = new_eip;
	print_asm(str(instr) " $0x%x", new_eip + CODE_LEN);
}
make_instr_helper(si)
#undef instr
/*----------------------------------------------------*/


//make_instr_helper(si)
#undef get_new_eip


#include "cpu/exec/template-end.h"
