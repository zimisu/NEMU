#include "cpu/exec/helper.h"

make_helper(cvt)
{
    if (ops_decoded.is_data_size_16)
    {
        if (cpu.ax & 0x1000) cpu.dx = 0xffff;
        else cpu.dx = 0;
        
    } 
    else 
    {
        if (cpu.eax & 0x1000)
            cpu.edx = 0xffffffff;
    }
    
    print_asm("cwd/cdq");
    return 1;
}


