
#include "cpu/exec/helper.h"

#define DATA_BYTE 2
#include "jmp_indrct-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jmp_indrct-template.h"
#undef DATA_BYTE

make_helper_v(jmp_indrct_rm)
