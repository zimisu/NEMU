#include "prefix/prefix.h"

#include "data-mov/mov.h"
#include "data-mov/xchg.h"

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

#include "logic/and.h"
#include "logic/or.h"
#include "logic/not.h"
#include "logic/xor.h"
#include "logic/sar.h"
#include "logic/shl.h"
#include "logic/shr.h"
#include "logic/shrd.h"

#include "string/rep.h"

#include "jcc/je.h"
#include "jcc/jbe.h"
#include "jmp/jmp.h"

#include "misc/misc.h"

#include "special/special.h"

#include "call/call.h"

#include "push/push.h"

#include "test/test.h"

#include "stack/leave.h"
#include "stack/ret.h"
#include "stack/pop.h"
