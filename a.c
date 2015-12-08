/*************************************************************************
    > File Name: a.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2015年10月20日 星期二 10时31分06秒
 ************************************************************************/

#include<stdio.h>

void g()
{
	printf("this is g\n");
}

void f()
{
	int a = 1;
	int b = 2;
	printf("%d\n", a + b);
	g();
}

int main()
{
	f();
	return 0;
}
