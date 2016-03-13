#include "cpu/exec/helper.h"

make_helper(cvt)
{
    if (ops_decoded.is_data_size_16)
    {
        if (cpu.ax & 0x8000) cpu.dx = 0xffff;
        else cpu.dx = 0;
        
    } 
    else 
    {
        if (cpu.eax & 0x80000000)
            cpu.edx = 0xffffffff;
		else cpu.edx = 0;
    }
    
    print_asm("cwd/cdq");
    return 1;
}


