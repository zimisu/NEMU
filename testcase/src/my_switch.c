#include "trap.h"
//#include <stdio.h>

int f(int i)
{
    switch (i){
        case 2: case 3: return 1; 
        case 4: case 5:return 2;
        default: return 0;
    }
}

int main()
{
    int i = 0;
    nemu_assert(f(-1) == 0);
    for (i = 1; i < 6; i++)
        nemu_assert(f(i) == i / 2);
    HIT_GOOD_TRAP;
    //printf("%d %d\n", f(0), f(-1));
    return 0;
}
