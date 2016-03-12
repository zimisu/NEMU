#include "prefix/prefix.h"

#include "data-mov/mov.h"
#include "data-mov/xchg.h"
#include "data-mov/movsx.h"
#include "data-mov/convert.h"

#include "arith/dec.h"
#include "arith/inc.h"
#include "arith/neg.h"
#include "arith/imul.h"
#include "arith/mul.h"
#include "arith/idiv.h"
#include "arith/div.h"
#include "arith/sub.h"
#include "arith/cmp.h"
#include "arith/add.h"
#include "arith/adc.h"

#include "logic/and.h"
#include "logic/or.h"
#include "logic/not.h"
#include "logic/xor.h"
#include "logic/sar.h"
#include "logic/sal.h"
#include "logic/shl.h"
#include "logic/shr.h"
#include "logic/shrd.h"

#include "string/rep.h"

#include "jcc/je.h"
#include "jcc/jbe.h"
#include "jcc/ja.h"
#include "jcc/jle.h"
#include "jcc/jl.h"
#include "jcc/jge.h"
#include "jmp/jmp_rel.h"
#include "jmp/jmp_indrct.h"

#include "misc/misc.h"

#include "special/special.h"

#include "call/call.h"

#include "push/push.h"

#include "test/test.h"

#include "stack/leave.h"
#include "stack/ret.h"
#include "stack/pop.h"
