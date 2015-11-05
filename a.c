/*************************************************************************
    > File Name: a.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2015年10月20日 星期二 10时31分06秒
 ************************************************************************/

#include<stdio.h>

double fun(int i)
{
	volatile double d[1] = {3.14};
	volatile long int a[2];
	//printf("  a: 0x%08x\n", a);
	//printf("  d: 0x%08x\n", d);
	a[i] = 1073741824;
	return d[0];
}

int main()
{
	int ch;
	int *c = & c;
	printf("0x%08x\n", c);
	printf("0x%08x\n", ++c);
	return 0;
}
