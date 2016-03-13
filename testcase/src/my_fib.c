#include "trap.h"
//#include "stdio.h"

int fib[] = {1, 1, 2, 3, 5, 8};

#define len sizeof(fib) / sizeof(int)

int cal_fib(int a)
{
    if (a == 0) return 0;
    return cal_fib(a-1);
    //if (a == 0 || a == 1) return 1;
    //return cal_fib(a-1) + cal_fib(a-2);
}

int main()
{
    int i = 1;
    nemu_assert(cal_fib(i) == i);
    //for (i = 0; i < len; i ++)
        //if (cal_fib(i) != fib[i])
          //  printf("error\n");
        //nemu_assert(cal_fib(i) == fib[i]);

    //nemu_assert(i == len);

    HIT_GOOD_TRAP;

    return 0;
}
