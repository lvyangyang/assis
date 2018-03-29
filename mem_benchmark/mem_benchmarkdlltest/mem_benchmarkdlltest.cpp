// mem_benchmarkdlltest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "mem_benchmarkfuncs.h"
#include "windows.h"
int main()
{
//	double latency;
	double bandwidth,latency;

	int test_bw_lat;
	int test_lenth,test_stride,test_func;
	printf("input 1 for bandwidth 2 for latency\n");
	scanf_s("%d", &test_bw_lat);
	if (test_bw_lat != 1 && test_bw_lat != 2)
		return 0;
//	latency =mem_benchmark::mem_latency(1024 * 128, 32);
	if (test_bw_lat == 1)
	{
		printf("input mem length\n");
		scanf_s("%d", &test_lenth);
		printf("test mem length is %d KB\n", test_lenth);

		printf(" test function:\n");
		printf("ReaderSSE2_fun 10\nWriterSSE2_fun 11\nCopySSE_fun   12\nWriterSSE2_bypass_fun 13\nCopySSE_bypass_fun 14\nReaderAVX_fun 20\nWriterAVX_fun 21\nCopyAVX_fun 22\n");
		printf(" select test function:");
		scanf_s("%d", &test_func);
		printf("test function is %d \n", test_func);

		bandwidth = mem_benchmark::mem_bw(1024 * test_lenth, test_func, 0, 1);
		//	bandwidth = mem_benchmark::mem_benchmark(mem_benchmark_lat,mem_benchmark_l1,0);
		printf("%f GB\s", bandwidth);
	}

	if (test_bw_lat == 2)
	{
		printf("input mem length\n");
		scanf_s("%d", &test_lenth);
		printf("test mem length is %d KB\n", test_lenth);

		printf("input mem stride\n");
		scanf_s("%d", &test_stride);
		printf("test mem length is %d Bytes\n", test_stride);
		latency = mem_benchmark::mem_latency(1024 * test_lenth, test_stride);
		printf("%e s", latency);
	}

	Sleep(3000);
    return 0;
}

