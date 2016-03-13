#include "trap.h"

int f(int i)
{
    switch (i){
        case 1: case 2: return 1; 
        case 3: case 4:return 2;
        default: return 0;
    }
}

int main()
{
    int i = 0;
    for (i = 0; i < 5; i++)
        nemu_assert(f(i) == i / 2);
    HIT_GOOD_TRAP;
    return 0;
}
