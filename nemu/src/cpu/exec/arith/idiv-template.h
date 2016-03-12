#include "cpu/exec/template-start.h"

#define instr idiv

static void do_execute() {
	int64_t a;
	int32_t b = (DATA_TYPE_S)op_src->val;
#if DATA_BYTE == 1
	a = reg_w(R_EAX);
#else
	a = ((uint64_t)REG(R_EDX) << (DATA_BYTE * 8)) | REG(R_EAX);
#endif
	REG(R_EAX) = a / b;
	REG(R_EDX) = a % b;

	print_asm_template1();
}

make_instr_helper(rm)

#include "cpu/exec/template-end.h"
