// diskmarkdlltest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "DiskMarkFuncs.h"
int main()
{
	diskmark::initial();
	char c;
	c=getchar();
	printf("tesst %c\n",c);
	diskmark::startdisktest(c, 1, 1, 1);


	diskmark::endtest();


	return 0;
}
