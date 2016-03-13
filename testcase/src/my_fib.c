#include "trap.h"


int fib[] = {1, 1, 2};

#define len sizeof(fib) / sizeof(int)

int cal_fib(int a)
{
    if (a == 0 || a == 1) return 1;
    return cal_fib(a-1) + cal_fib(a-2);
}

int main()
{
    int i;
    for (i = 0; i < len; i ++)
        nemu_assert(cal_fib(i) == fib[i]);

    nemu_assert(i == len);

    HIT_GOOD_TRAP;

    return 0;
}
