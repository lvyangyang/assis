#pragma once

#define DISKMARKFUNCSDLL_API __declspec(dllexport) 
#include "windows.h"
namespace diskmark 
{
	struct diskmarkoutput
	{
		float writespeed_4k;
		UINT64 writeiops_4k;
		float readspeed_4k;
		UINT64 readiops_4k;
		float writespeed_4k64;
		UINT64 writeiops_4k64;
		float readspeed_4k64;
		UINT64 readiops_4k64;
		float writespeed_serial;
		UINT64 writeiops_serial;
		float readspeed_serial;
		UINT64 readiops_serial;

	};
	//快速测试，使用默认设置，已经包含初始化和结束过程，返回测试结果，直到测试结束函数才会返回。
	DISKMARKFUNCSDLL_API 	diskmarkoutput fasttest(void);
	//初始化，成功则返回1，失败返回0
	DISKMARKFUNCSDLL_API	int initial(void);
	//设置每一项测试最长等待时间（应对低性能磁盘测试过慢的问题）
	DISKMARKFUNCSDLL_API	void setwaittime(long w_time);
	//设置每一项测试的最低测试时间（应对高性能磁盘）
	DISKMARKFUNCSDLL_API    void setmintime(long m_time);
	//开始测试，，直到测试结束函数才会返回。char c设定测试盘符（大写），BOOL t_4k, BOOL t_4k64, BOOL t_serial，设置测试项，0代表不测，1代表测
	DISKMARKFUNCSDLL_API    void startdisktest(char c, BOOL t_4k, BOOL t_4k64, BOOL t_serial);
	//快速结束测试（其实是将等待时间设为0）
	DISKMARKFUNCSDLL_API	void stopall(void);
	//结束处理
	DISKMARKFUNCSDLL_API    void endtest(void);
	//获得测试时的瞬时速度
	DISKMARKFUNCSDLL_API    diskmarkoutput get_instant_data(void);
	//获得测试结果，可获得已经完成的测试项结果，没完成的结果为0
	DISKMARKFUNCSDLL_API	diskmarkoutput get_output_data(void);

}
/*直接调用fasttest,函数结束后会返回测试数据，测试设置全是默认

如要对测试进行设置，先执行initial函数，然后通过setwaittime和setmintime可以设置单项测试时间，接着startdisktest启动测试

测试期间可以通过get_instant_data获得当前测试状态（瞬时速度），也可以通过get_output_data获得已经完成的测试结果，但必须另外开线程，因为测试会阻塞调用相关函数的线程。

*/