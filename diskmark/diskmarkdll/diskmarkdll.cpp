// diskmarkdll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include"DiskMarkFuncs.h"

//#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <Wmistr.h>
#include <string.h>
#include <time.h>
#include <vector>
#define INITGUID	
#include <Evntrace.h>
#include <iostream>
using namespace std;
namespace diskmark
{//命名空间开始
	DEFINE_GUID( /* 3d6fa8d4-fe05-11d0-9dda-00c04fd7ba7c */
		DiskIoGuid,
		0x3d6fa8d4,
		0xfe05,
		0x11d0,
		0x9d, 0xda, 0x00, 0xc0, 0x4f, 0xd7, 0xba, 0x7c
	);
	struct ETWEventCounters
	{
		UINT64 ullIORead;                   // Read
		UINT64 ullIOWrite;                  // Write
		UINT64 ullMMTransitionFault;        // Transition fault
		UINT64 ullMMDemandZeroFault;        // Demand Zero fault
		UINT64 ullMMCopyOnWrite;            // Copy on Write
		UINT64 ullMMGuardPageFault;         // Guard Page fault
		UINT64 ullMMHardPageFault;          // Hard page fault
		UINT64 ullNetTcpSend;               // Send
		UINT64 ullNetTcpReceive;            // Receive
		UINT64 ullNetUdpSend;               // Send
		UINT64 ullNetUdpReceive;            // Receive
		UINT64 ullNetConnect;               // Connect
		UINT64 ullNetDisconnect;            // Disconnect
		UINT64 ullNetRetransmit;            // ReTransmit
		UINT64 ullNetAccept;                // Accept
		UINT64 ullNetReconnect;             // ReConnect
		UINT64 ullRegCreate;                // NtCreateKey
		UINT64 ullRegOpen;                  // NtOpenKey
		UINT64 ullRegDelete;                // NtDeleteKey
		UINT64 ullRegQuery;                 // NtQueryKey
		UINT64 ullRegSetValue;              // NtSetValueKey
		UINT64 ullRegDeleteValue;           // NtDeleteValueKey
		UINT64 ullRegQueryValue;            // NtQueryValueKey
		UINT64 ullRegEnumerateKey;          // NtEnumerateKey
		UINT64 ullRegEnumerateValueKey;     // NtEnumerateValueKey
		UINT64 ullRegQueryMultipleValue;    // NtQueryMultipleValueKey
		UINT64 ullRegSetInformation;        // NtSetInformationKey
		UINT64 ullRegFlush;                 // NtFlushKey
		UINT64 ullRegKcbDmp;                // KcbDump/create
		UINT64 ullThreadstart;
		UINT64 ullThreadEnd;
		UINT64 ullProcessStart;
		UINT64 ullProcessEnd;
		UINT64 ullImageLoad;
	};
	struct speedtest
	{

		LARGE_INTEGER latesttimestamp;
		UINT64 totaldata;

	};
	struct processdata
	{
		LARGE_INTEGER firsttimestamp;
		LARGE_INTEGER oldtimestamp;
		clock_t begin;
		UINT64 initialio;

		UINT64 oldio;
		UINT64 oldtotaldata;
		UINT64 init_totaldata;

		LARGE_INTEGER instant_latency;
		UINT64 instant_iops;
		float instant_mbytespersec;

		LARGE_INTEGER avg_latency;
		UINT64 iops;
		float mbytespersec;

	};

	//ERROR_BAD_LENGTH
	PEVENT_TRACE_PROPERTIES pProperties;
	struct ETWEventCounters g_EtwEventCounters;
	struct speedtest writespeeddata, readspeeddata, speeddata_write_4k64, speeddata_read_4k64, speeddata_write_serial, speeddata_read_serial;
	struct processdata writeprocessdata, readprocessdata, writeprocessdata_4k64, readprocessdata_4k64, writeprocessdata_serial, readprocessdata_serial;
	BOOL iswriteend = 0, isreadend = 0, iswriteend_4k64 = 0, isreadend_4k64 = 0, iswriteend_serial = 0, isreadend_serial = 0;
	BOOL timeout_4kwrite = 0, timeout_4kread = 0, timeout_4k64write = 0, timeout_4k64read = 0, timeout_serialwrite = 0, timeout_serialread = 0;
	BOOL is_test_4k = 1, is_test_4k64 = 1, is_test_serial = 1;
	HANDLE hwritestart4k, hreadstart4k, hwritestart4k64, hreadstart4k64, hwritestartserial, hreadstartserial;
	HANDLE hwrite4k_end, hread4k_end, hwrite4k64_end, hread4k64_end, hwriteserial_end, hreadserial_end;
	clock_t waittime = 60000, min_time = 30000;
	char part_c = 'E';
	UINT64 testfilesize = 1024 * 1024 * 1024;

	PEVENT_TRACE_PROPERTIES allocateEventTraceProperties()
	{
		PEVENT_TRACE_PROPERTIES pProperties = NULL;
		size_t size = 0;


		size = sizeof(EVENT_TRACE_PROPERTIES) + sizeof(KERNEL_LOGGER_NAME);
		pProperties = (PEVENT_TRACE_PROPERTIES)malloc(size);
		if (NULL == pProperties)
		{
			printf("FATAL ERROR: unable to allocate memory (error code: %d)\n", GetLastError());
			return NULL;
		}


		memset(pProperties, 0, size);

		pProperties->Wnode.BufferSize = (ULONG)size;
		pProperties->LoggerNameOffset = sizeof(EVENT_TRACE_PROPERTIES);

		pProperties->Wnode.Flags = WNODE_FLAG_TRACED_GUID;
		pProperties->Wnode.ClientContext = 1;
		pProperties->Wnode.Guid = SystemTraceControlGuid;
		pProperties->LogFileMode = EVENT_TRACE_FILE_MODE_SEQUENTIAL | EVENT_TRACE_REAL_TIME_MODE;
		pProperties->EnableFlags = EVENT_TRACE_FLAG_DISK_IO;
		pProperties->FlushTimer = 1;

		strcpy_s((char *)pProperties + pProperties->LoggerNameOffset,
			size - pProperties->LoggerNameOffset, KERNEL_LOGGER_NAME);

		return pProperties;
	}


	void WINAPI eventDiskIo(PEVENT_TRACE pEvent)
	{
		if (EVENT_TRACE_TYPE_IO_READ == pEvent->Header.Class.Type)
		{
			++g_EtwEventCounters.ullIORead;
			readspeeddata.latesttimestamp = pEvent->Header.TimeStamp;

		}
		else if (EVENT_TRACE_TYPE_IO_WRITE == pEvent->Header.Class.Type)
		{
			++g_EtwEventCounters.ullIOWrite;
			writespeeddata.latesttimestamp = pEvent->Header.TimeStamp;

		}
	}

	DWORD WINAPI TraceEvents(LPVOID lparam)
	{
		TRACEHANDLE handles[1];
		EVENT_TRACE_LOGFILE logfile;

		memset(&logfile, 0, sizeof(EVENT_TRACE_LOGFILE));

		logfile.LoggerName = KERNEL_LOGGER_NAME;
		logfile.LogFileName = NULL;
		logfile.LogFileMode = EVENT_TRACE_REAL_TIME_MODE;

		logfile.IsKernelTrace = true;

		handles[0] = OpenTrace(&logfile);
		if ((TRACEHANDLE)INVALID_HANDLE_VALUE == handles[0])
		{
			printf("ETW ERROR: OpenTrace failed (error code: %d)\n", GetLastError());
			return false;
		}
		else
		{
			ProcessTrace(handles, 1, 0, 0);
			CloseTrace(handles[0]);
		}

		return true;
	}

	void monitor_4k()
	{//bgin 4k info collect
		memset(&g_EtwEventCounters, 0, sizeof(struct ETWEventCounters));
		
		SetEvent(hwritestart4k);
		Sleep(3000);
		printf("begin 4K write\n");
		//write
		writeprocessdata.initialio = g_EtwEventCounters.ullIOWrite;
		writeprocessdata.begin = clock();
		writeprocessdata.init_totaldata = writespeeddata.totaldata;
		while (writeprocessdata.oldtotaldata<testfilesize*1.3||clock()-writeprocessdata.begin<min_time)
		{

			writeprocessdata.oldio = g_EtwEventCounters.ullIOWrite;

			writeprocessdata.oldtotaldata = writespeeddata.totaldata;
			clock_t t_c = clock();
			Sleep(2000);
			writeprocessdata.instant_iops = (UINT64)((g_EtwEventCounters.ullIOWrite - writeprocessdata.oldio) * 1000 / (clock() - t_c));
			writeprocessdata.instant_mbytespersec = (float)(writespeeddata.totaldata - writeprocessdata.oldtotaldata) / 1024 / 1.024 / (clock() - t_c);
			printf("iowrite: %d iops ", writeprocessdata.instant_iops);
			printf(" %f mb/s \n", writeprocessdata.instant_mbytespersec);
			if (clock() - writeprocessdata.begin > waittime)
						break;

		}
		writeprocessdata.iops = (g_EtwEventCounters.ullIOWrite - writeprocessdata.initialio) * 1000 / (clock() - writeprocessdata.begin);
		writeprocessdata.mbytespersec = (float)(writespeeddata.totaldata - writeprocessdata.init_totaldata) / 1000 / (clock() - writeprocessdata.begin);
		printf("average iowrite: %d iops\n ", writeprocessdata.iops);
		printf(" %f mb/s\n ", writeprocessdata.mbytespersec);
		//瞬时速度置零
		writeprocessdata.instant_iops = 0;
		writeprocessdata.instant_mbytespersec = 0;
		iswriteend = 1;
		WaitForSingleObject(hwrite4k_end,INFINITE);

		//read
	
		SetEvent(hreadstart4k);
		Sleep(3000);
		printf("begin 4K read\n");
		readprocessdata.begin = clock();
		readprocessdata.initialio = g_EtwEventCounters.ullIORead;
		readprocessdata.init_totaldata = readspeeddata.totaldata;
		while (readprocessdata.oldtotaldata<testfilesize*1.2||clock()-readprocessdata.begin<min_time)
		{

			readprocessdata.oldio = g_EtwEventCounters.ullIORead;
			//		readprocessdata.firsttimestamp = readspeeddata.latesttimestamp;
			readprocessdata.oldtotaldata = readspeeddata.totaldata;

			clock_t t_c = clock();
			Sleep(2000);
			readprocessdata.instant_iops = (UINT64)((g_EtwEventCounters.ullIORead - readprocessdata.oldio) * 1000 / (clock() - t_c));
			readprocessdata.instant_mbytespersec = (float)(readspeeddata.totaldata - readprocessdata.oldtotaldata) / 1024 / 1.024 / (clock() - t_c);
			printf("ioread:%d iops\t", readprocessdata.instant_iops);
			printf(" %f mb/s \n", readprocessdata.instant_mbytespersec);
			if (clock() - readprocessdata.begin > waittime)
				break;

		}
		readprocessdata.iops = (g_EtwEventCounters.ullIOWrite - readprocessdata.initialio) * 1000 / (clock() - readprocessdata.begin);
		readprocessdata.mbytespersec = (float)(readspeeddata.totaldata - readprocessdata.init_totaldata) / (1024 * 1.024) / (clock() - readprocessdata.begin);
		printf("average ioread: %d iops\n ", readprocessdata.iops);
		printf(" %f mb/s\n ", readprocessdata.mbytespersec);
		//瞬时速度置零
		readprocessdata.instant_iops = 0;
		readprocessdata.instant_mbytespersec = 0;
		isreadend = 1;
		WaitForSingleObject(hread4k_end,INFINITE);
		//end of 4k info collect
	}


	void monitor_4k_64()
	{//bgin 4k info collect
		memset(&g_EtwEventCounters, 0, sizeof(struct ETWEventCounters));
		SetEvent(hwritestart4k64);
		Sleep(3000);
		printf("begin 4K-64thread write\n");
		//write
		writeprocessdata_4k64.initialio = g_EtwEventCounters.ullIOWrite;
		writeprocessdata_4k64.begin = clock();
		writeprocessdata_4k64.init_totaldata = speeddata_write_4k64.totaldata;
		while (writeprocessdata_4k64.oldtotaldata<testfilesize*1.2||clock()- writeprocessdata_4k64.begin<min_time)
		{

			writeprocessdata_4k64.oldio = g_EtwEventCounters.ullIOWrite;

			writeprocessdata_4k64.oldtotaldata = speeddata_write_4k64.totaldata;
			clock_t t_c = clock();
			Sleep(2000);
			writeprocessdata_4k64.instant_iops = (UINT64)((g_EtwEventCounters.ullIOWrite - writeprocessdata_4k64.oldio) * 1000 / (clock() - t_c));
			writeprocessdata_4k64.instant_mbytespersec = (float)(speeddata_write_4k64.totaldata - writeprocessdata_4k64.oldtotaldata) / 1024 / 1.024 / (clock() - t_c);
			printf("iowrite: %d iops ", writeprocessdata_4k64.instant_iops);
			printf(" %f mb/s \n", writeprocessdata_4k64.instant_mbytespersec);
			if (clock() - writeprocessdata_4k64.begin > waittime)
				break;
			

		}
		writeprocessdata_4k64.iops = (g_EtwEventCounters.ullIOWrite - writeprocessdata_4k64.initialio) * 1000 / (clock() - writeprocessdata_4k64.begin);
		writeprocessdata_4k64.mbytespersec = (float)(speeddata_write_4k64.totaldata - writeprocessdata_4k64.init_totaldata) / 1000 / (clock() - writeprocessdata_4k64.begin);
		printf("average iowrite: %d iops\n ", writeprocessdata_4k64.iops);
		printf(" %f mb/s\n ", writeprocessdata_4k64.mbytespersec);
		//瞬时速度置零
		writeprocessdata_4k64.instant_iops = 0;
		writeprocessdata_4k64.instant_mbytespersec = 0;
		iswriteend_4k64 = 1;
		WaitForSingleObject(hwrite4k64_end,INFINITE);

		//read
		
		SetEvent(hreadstart4k64);
		Sleep(3000);
		printf("begin 4K-64thread read\n");
		readprocessdata_4k64.begin = clock();
		readprocessdata_4k64.initialio = g_EtwEventCounters.ullIORead;
		readprocessdata_4k64.init_totaldata = speeddata_read_4k64.totaldata;
		while (readprocessdata_4k64.oldtotaldata<testfilesize*1.2||clock()- readprocessdata_4k64.begin<min_time)
		{

			readprocessdata_4k64.oldio = g_EtwEventCounters.ullIORead;
			readprocessdata_4k64.oldtotaldata = speeddata_read_4k64.totaldata;
			clock_t t_c = clock();

			Sleep(2000);
			readprocessdata_4k64.instant_iops = (UINT64)((g_EtwEventCounters.ullIORead - readprocessdata_4k64.oldio) * 1000 / (clock() - t_c));
			readprocessdata_4k64.instant_mbytespersec = (float)(speeddata_read_4k64.totaldata - readprocessdata_4k64.oldtotaldata) / 1024 / 1.024 / (clock() - t_c);
			printf("ioread:%d iops\t", readprocessdata_4k64.instant_iops);
			printf(" %f mb/s \n", readprocessdata_4k64.instant_mbytespersec);
			if (clock() - readprocessdata_4k64.begin > waittime)
				break;

		}

		readprocessdata_4k64.iops = (g_EtwEventCounters.ullIOWrite - readprocessdata_4k64.initialio) * 1000 / (clock() - readprocessdata_4k64.begin);
		readprocessdata_4k64.mbytespersec = (float)(speeddata_read_4k64.totaldata - readprocessdata_4k64.init_totaldata) / (1024 * 1.024) / (clock() - readprocessdata_4k64.begin);
		printf("average ioread: %d iops\n ", readprocessdata_4k64.iops);
		printf(" %f mb/s\n ", readprocessdata_4k64.mbytespersec);
		readprocessdata_4k64.instant_iops = 0;
		readprocessdata_4k64.instant_mbytespersec = 0;
		isreadend_4k64 = 1;
		WaitForSingleObject(hread4k64_end,INFINITE);
		//end of 4k info collect
	}

	void monitor_serial()
	{//bgin 4k info collect
		memset(&g_EtwEventCounters, 0, sizeof(struct ETWEventCounters));
	
		SetEvent(hwritestartserial);
		Sleep(3000);
		printf("begin serial write\n");
		//write
		writeprocessdata_serial.initialio = g_EtwEventCounters.ullIOWrite;
		writeprocessdata_serial.begin = clock();
		writeprocessdata_serial.init_totaldata = speeddata_write_serial.totaldata;
		while (writeprocessdata_serial.oldtotaldata<testfilesize*4||clock()- writeprocessdata_serial.begin<min_time)
		{

			writeprocessdata_serial.oldio = g_EtwEventCounters.ullIOWrite;

			writeprocessdata_serial.oldtotaldata = speeddata_write_serial.totaldata;
			clock_t t_c = clock();
			Sleep(2000);
			writeprocessdata_serial.instant_iops = (UINT64)((g_EtwEventCounters.ullIOWrite - writeprocessdata_serial.oldio) * 1000 / (clock() - t_c));
			writeprocessdata_serial.instant_mbytespersec = (float)(speeddata_write_serial.totaldata - writeprocessdata_serial.oldtotaldata) / 1024 / 1.024 / (clock() - t_c);
			printf("iowrite: %d iops ", writeprocessdata_serial.instant_iops);
			printf(" %f mb/s \n", writeprocessdata_serial.instant_mbytespersec);
			if (clock() - writeprocessdata_serial.begin > waittime)
				break;

		}
		writeprocessdata_serial.iops = (g_EtwEventCounters.ullIOWrite - writeprocessdata_serial.initialio) * 1000 / (clock() - writeprocessdata_serial.begin);
		writeprocessdata_serial.mbytespersec = (float)(speeddata_write_serial.totaldata - writeprocessdata_serial.init_totaldata) / 1000 / (clock() - writeprocessdata_serial.begin);
		printf("average iowrite: %d iops\n ", writeprocessdata_serial.iops);
		printf(" %f mb/s\n ", writeprocessdata_serial.mbytespersec);
		//瞬时速度置零
		writeprocessdata_serial.instant_iops = 0;
		writeprocessdata_serial.instant_mbytespersec = 0;
		iswriteend_serial = 1;
		WaitForSingleObject(hwriteserial_end, INFINITE);
		//read
		
		SetEvent(hreadstartserial);
		Sleep(3000);
		printf("begin serial read\n");
		readprocessdata_serial.begin = clock();
		readprocessdata_serial.initialio = g_EtwEventCounters.ullIORead;
		readprocessdata_serial.init_totaldata = speeddata_read_serial.totaldata;
		while (readprocessdata_serial.oldtotaldata<testfilesize*4||clock()- readprocessdata_serial.begin<min_time)
		{

			readprocessdata_serial.oldio = g_EtwEventCounters.ullIORead;
			//		readprocessdata_serial.firsttimestamp = speeddata_read_serial.latesttimestamp;
			readprocessdata_serial.oldtotaldata = speeddata_read_serial.totaldata;

			clock_t t_c = clock();
			Sleep(2000);
			readprocessdata_serial.instant_iops = (UINT64)((g_EtwEventCounters.ullIORead - readprocessdata_serial.oldio) * 1000 / (clock() - t_c));
			readprocessdata_serial.instant_mbytespersec = (float)(speeddata_read_serial.totaldata - readprocessdata_serial.oldtotaldata) / 1024 / 1.024 / (clock() - t_c);
			printf("ioread:%d iops\t", readprocessdata_serial.instant_iops);
			printf(" %f mb/s \n", readprocessdata_serial.instant_mbytespersec);
			if (clock() - readprocessdata_serial.begin > waittime)
				break;

		}
		readprocessdata_serial.iops = (g_EtwEventCounters.ullIOWrite - readprocessdata_serial.initialio) * 1000 / (clock() - readprocessdata_serial.begin);
		readprocessdata_serial.mbytespersec = (float)(speeddata_read_serial.totaldata - readprocessdata_serial.init_totaldata) / (1024 * 1.024) / (clock() - readprocessdata_serial.begin);
		printf("average ioread: %d iops\n ", readprocessdata_serial.iops);
		printf(" %f mb/s\n ", readprocessdata_serial.mbytespersec);
		//瞬时速度置零
		readprocessdata_serial.instant_iops = 0;
		readprocessdata_serial.instant_mbytespersec = 0;
		isreadend_serial = 1;
		WaitForSingleObject(hreadserial_end,INFINITE);
	}



	DWORD WINAPI etwThreadFunc(LPVOID lparam)
	{

		if (is_test_serial)
			monitor_serial();

		if (is_test_4k)
			monitor_4k();

		if (is_test_4k64)
			monitor_4k_64();

	
		Sleep(2000);


		return 1;
	}

	void test_4k()
	{
		int i = 0, j = 0, k = 1;

		DWORD buffersize = 1024 * 4;


		char tempname_write[20];
		sprintf_s(tempname_write, 20, "%c:\\1.data", part_c);
		LPCSTR filepath = tempname_write;


		HANDLE hfile = CreateFile(filepath, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_NO_BUFFERING, NULL);
		if (INVALID_HANDLE_VALUE == hfile)
			int error = GetLastError();


		char *buffer = (char *)malloc(sizeof(char)*	buffersize);
		for (j = 0; j < buffersize; j++)
			*(buffer + j) = rand() % 256;

		SetFilePointer(hfile, 0, NULL, FILE_BEGIN);
		DWORD dwBytesWritten, dwBytesReaden;
		BOOL state = 1;
		int beginoffset = 0, endoffset = testfilesize;


//-------------------性能计数同步--------------------------
		WaitForSingleObject(hwritestart4k,INFINITE);
		clock_t begin_time = clock();
		while (!iswriteend) //-------------------性能计数同步--------------------------
		{
			WriteFile(
				hfile,           // open file handle
				buffer,      // start of data to write
				buffersize,  // number of bytes to write
				&dwBytesWritten, // number of bytes that were written
				NULL);
			writespeeddata.totaldata += dwBytesWritten;

			int u = (double)rand() / (RAND_MAX + 1) * (testfilesize / 4096 - 1) + 1;
			beginoffset = 1024 * 4 * u;
			SetFilePointer(hfile, beginoffset, NULL, FILE_BEGIN);

		}
		SetEvent(hwrite4k_end);
		

		//-------------------性能计数同步--------------------------
		WaitForSingleObject(hreadstart4k,INFINITE);
		begin_time = clock();
		while (!isreadend)//-------------------性能计数同步--------------------------
		{

			ReadFile(
				hfile,           // open file handle
				buffer,      // start of data to write
				buffersize,  // number of bytes to write
				&dwBytesReaden, // number of bytes that were written
				NULL);
			readspeeddata.totaldata += dwBytesReaden;
			int u = (double)rand() / (RAND_MAX + 1) * (testfilesize / 4096 - 1) + 1;

			beginoffset = 1024 * 4 * u;
			SetFilePointer(hfile, beginoffset, NULL, FILE_BEGIN);

		}

		if (!::CloseHandle(hfile))
		{
			// Closing the handle failed for some reason.
			printf("close file error\n");
		}
		remove(filepath);
		SetEvent(hread4k_end);
		//end of 4k test task

	}

	DWORD WINAPI write_workthread_4k64k(LPVOID lparam)
	{
		int i, j;

		int buffersize = 1024 * 4;
		char *buffer = (char *)malloc(sizeof(char)*	buffersize);
		for (j = 0; j < buffersize; j++)
			*(buffer + j) = rand() % 256;
		//获得参数
		struct workthread_param
		{
			vector<HANDLE> *phfiles;
			vector<char *> *vreadfile_buffer;
			HANDLE hiocp;

		};
		workthread_param *pmyparam = (workthread_param *)lparam;

		int bytestransfered;
		LPOVERLAPPED poverlptemp;
		clock_t begin_time = clock();
		while (!iswriteend_4k64)
		{

			
			BOOL bRet = GetQueuedCompletionStatus(pmyparam->hiocp, (LPDWORD)&bytestransfered, (PULONG_PTR)&i, &poverlptemp, INFINITE);
			if (FALSE == bRet)
			{
				DWORD dwErr = GetLastError();
				if (NULL == poverlptemp)
				{
					printf("线程函数返回错误， 错误原因:");
					cout << dwErr << endl;
					break;
				}

			}
			//统计数据-------------
			speeddata_write_4k64.totaldata += bytestransfered;

			//继续接着原来的写----------------------------------------------------
			int u = (double)rand() / (RAND_MAX + 1) * (1024 * 4 - 1) + 1;

			poverlptemp->Offset = u * 1024 * 4;
			WriteFile(pmyparam->phfiles->at(i), buffer, buffersize, NULL, poverlptemp);
			//--------------------------------------------------------------------
		}

		return  4;
	}

	DWORD WINAPI read_workthread_4k64k(LPVOID lparam)
	{
		int i, j;

		int buffersize = 1024 * 4;
		/*	char *buffer = (char *)malloc(sizeof(char)*	buffersize);
		for (j = 0; j < buffersize; j++)
		*(buffer + j) = rand() % 256;
		*/
		//获得参数
		struct workthread_param
		{
			vector<HANDLE> *phfiles;
			vector<char *> *vreadfile_buffer;
			HANDLE hiocp;

		};
		workthread_param *pmyparam = (workthread_param *)lparam;

		int bytestransfered;
		LPOVERLAPPED poverlptemp;
		clock_t begin_time = clock();
		while (!isreadend_4k64)
		{

			BOOL bRet = GetQueuedCompletionStatus(pmyparam->hiocp, (LPDWORD)&bytestransfered, (PULONG_PTR)&i, &poverlptemp, INFINITE);
			if (FALSE == bRet)
			{
				DWORD dwErr = GetLastError();
				if (NULL == poverlptemp)
				{
					printf("线程函数返回错误， 错误原因:");
					cout << dwErr << endl;
					break;
				}

			}
			//统计数据-------------
			speeddata_read_4k64.totaldata += bytestransfered;

			//继续接着原来的读----------------------------------------------------
			int u = (double)rand() / (RAND_MAX + 1) * (1024 * 4 - 1) + 1;

			poverlptemp->Offset = u * 1024 * 4;
			ReadFile(pmyparam->phfiles->at(i), pmyparam->vreadfile_buffer->at(i), buffersize, NULL, poverlptemp);
			//--------------------------------------------------------------------
		}

		return  5;
	}


	void test_4k64()
	{//------------基础变量预备-------------------
		int i, j;
		LPCSTR filepath;
		char *tempfilename = (char *)malloc(20);

		int buffersize = 4096;
		char *buffer = (char *)malloc(sizeof(char)*	buffersize);
		for (j = 0; j < buffersize; j++)
			*(buffer + j) = rand() % 256;

		SYSTEM_INFO si;
		GetSystemInfo(&si);

		int writethread_num_4k64 = 2 * si.dwNumberOfProcessors;//工作线程数量
		int readthread_num_4k64 = 2 * si.dwNumberOfProcessors;//线程池线程数量
		int concurent_file_num = 64;//文件数量


		HANDLE hiocp = NULL;
		hiocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, writethread_num_4k64);
		//创建文件--------绑定io完成端口------------
		vector<HANDLE> hfiles;
		for (i = 0; i < concurent_file_num; i++)
		{
			sprintf_s(tempfilename, 20, "%c:\\000.d%02d", part_c, i);
			filepath = tempfilename;
			HANDLE hfile = CreateFile(filepath, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED, NULL);
			if (INVALID_HANDLE_VALUE == hfile)
				int error = GetLastError();
			hiocp = CreateIoCompletionPort(hfile, hiocp, i, 1);
			hfiles.push_back(hfile);
		}
		vector<OVERLAPPED> povp(concurent_file_num);

		//读文件需要的每个文件的buffer
		vector<char *> vreadfile_buffer;
		for (i = 0; i < concurent_file_num; i++)
		{
			char *tempbuffer = (char *)malloc(sizeof(char)*	buffersize);
			vreadfile_buffer.push_back(tempbuffer);
		}
		//线程传参准备-------------	
		struct workthread_param
		{
			vector<HANDLE> *phfiles;
			vector<char *> *vreadfile_buffer;
			HANDLE hiocp;

		};
		workthread_param myparam;
		myparam.hiocp = hiocp;
		myparam.phfiles = &hfiles;
		myparam.vreadfile_buffer = &vreadfile_buffer;


		WaitForSingleObject(hwritestart4k64,INFINITE);
		//-----------------------4k --------64写开始-------------------------
		//--------------------创建4k64随机写工作线程-------------------------
		HANDLE phwritework4k64[20];
		for (i = 0; i < writethread_num_4k64; i++)
			phwritework4k64[i] = CreateThread(NULL, NULL, write_workthread_4k64k, &myparam, 0, NULL);


		//第一次写文件---------		
		for (i = 0; i < concurent_file_num; i++)
		{
			int u = (double)rand() / (RAND_MAX + 1) * (1024 * 4 - 1) + 1;
			(povp.at(i)).Offset = u * 1024 * 4;
			if (!WriteFile(hfiles.at(i), buffer, buffersize, NULL, &povp.at(i)))
			{
				//	printf("write file error\n");

				int error = GetLastError();
			}
		}

		
		WaitForMultipleObjects(writethread_num_4k64, phwritework4k64, TRUE, INFINITE);
		SetEvent(hwrite4k64_end);
		
		//-----------------------4k --------64写结束-------------------------

		WaitForSingleObject(hreadstart4k64,INFINITE);
		//-----------------------4k --------64读开始--------------------------------------
		HANDLE phreadwork4k64[20];
		for (i = 0; i < readthread_num_4k64; i++)
			phreadwork4k64[i] = CreateThread(NULL, NULL, read_workthread_4k64k, &myparam, 0, NULL);


		//---------第一次读文件----	
		for (i = 0; i < concurent_file_num; i++)
		{
			int u = (double)rand() / (RAND_MAX + 1) * (1024 * 4 - 1) + 1;
			(povp.at(i)).Offset = u * 1024 * 4;
			if (!ReadFile(hfiles.at(i), vreadfile_buffer.at(i), buffersize, NULL, &povp.at(i)))
			{
				//	printf("write file error\n");

				int error = GetLastError();
			}
		}

		WaitForMultipleObjects(readthread_num_4k64, phreadwork4k64, TRUE, INFINITE);
		SetEvent(hread4k64_end);
	
		//-----------------------4k --------64读结束-------------------------	
		//删除测试文件----------------------
		for (i = 0; i < concurent_file_num; i++)
			CloseHandle(hfiles.at(i));
		for (i = 0; i < concurent_file_num; i++)
		{
			sprintf_s(tempfilename, 20, "C:\\000.d%02d", i);
			filepath = tempfilename;
			remove(tempfilename);
		}
		//释放分配的内存空间
		free(buffer);
		for (i = 0; i < concurent_file_num; i++)
			free(vreadfile_buffer.at(i));


	}
	void test_serial()
	{
		int i = 0, j = 0, k = 1;
		DWORD buffersize = 1024 * 1024 * 4;
		char  tempname_write[20];
		sprintf_s(tempname_write, 20, "%c:\\serial.data", part_c);
		LPCSTR filepath_write = tempname_write;

		HANDLE hfile = CreateFile(filepath_write, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_FLAG_WRITE_THROUGH, NULL);
		if (INVALID_HANDLE_VALUE == hfile)
			int error = GetLastError();


		char *buffer = (char *)malloc(sizeof(char)*	buffersize);
		for (j = 0; j < buffersize; j++)
			*(buffer + j) = rand() % 256;

		//	SetFilePointer(hfile,0,NULL,FILE_BEGIN);
		DWORD dwBytesWritten, dwBytesReaden;
		BOOL state = 1;
		//	int beginoffset = 0,endoffset=testfilesize;
		speeddata_write_serial.totaldata = 0;
		clock_t warm_begin = clock();

		//-------------------性能计数同步--------------------------
		WaitForSingleObject(hwritestartserial,INFINITE);
		clock_t begin_time = clock();
		while (!iswriteend_serial) //-------------------性能计数同步--------------------------
		{
			WriteFile(
				hfile,           // open file handle
				buffer,      // start of data to write
				buffersize,  // number of bytes to write
				&dwBytesWritten, // number of bytes that were written
				NULL);


			speeddata_write_serial.totaldata += dwBytesWritten;


		}
	
		if (!::CloseHandle(hfile))
		{
			// Closing the handle failed for some reason.
			printf("close file error\n");
		}
		remove(tempname_write);
		SetEvent(hwriteserial_end);

		speeddata_read_serial.totaldata = 0;
		char tempfilename[30];
		sprintf_s(tempfilename, 20, "\\\\?\\%c:", part_c);
		LPCSTR partion_path_read = tempfilename;
		HANDLE hpartion_read = CreateFile(partion_path_read, GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
		if (INVALID_HANDLE_VALUE == hpartion_read)
			int error = GetLastError();

		
		//-------------------性能计数同步--------------------------

		WaitForSingleObject(hreadstartserial,INFINITE);
		begin_time = clock();
		while (!isreadend_serial)//-------------------性能计数同步--------------------------
		{

			ReadFile(
				hpartion_read,           // open file handle
				buffer,      // start of data to write
				buffersize,  // number of bytes to write
				&dwBytesReaden, // number of bytes that were written
				NULL);
			speeddata_read_serial.totaldata += dwBytesReaden;

		}
		SetEvent(hreadserial_end);
		//		remove("C:\\serial.data");

		//end of 4k test task

	}

	DWORD WINAPI createtest(LPVOID lparam)
	{

	
		if (is_test_serial)
			test_serial();

		if (is_test_4k)
			test_4k();

		if (is_test_4k64)
			test_4k64();


		return 3;
	}

	int initial()
	{
		pProperties = allocateEventTraceProperties();
		if (nullptr == pProperties)
		{
			return 0;
		}
		TRACEHANDLE hTraceSession;
		//	ControlTrace((TRACEHANDLE)0, KERNEL_LOGGER_NAME,pProperties, EVENT_TRACE_CONTROL_STOP);
		ULONG ret = StartTrace(&hTraceSession, KERNEL_LOGGER_NAME, pProperties);

		if (ERROR_SUCCESS != ret)
		{

			if (ret == ERROR_ALREADY_EXISTS)
			{
				printf("NT Kernel Logger session is already in use\n");
			}
			else
			{
				printf("error during start NT Kernel Logger session e\n");
				return 0;

			}

		}
		//	memset(&g_EtwEventCounters, 0, sizeof(struct ETWEventCounters));
		memset(&writespeeddata, 0, sizeof(speedtest));
		memset(&readspeeddata, 0, sizeof(speedtest));
		memset(&speeddata_write_4k64, 0, sizeof(speedtest));
		memset(&speeddata_read_4k64, 0, sizeof(speedtest));
		memset(&speeddata_write_serial, 0, sizeof(speedtest));
		memset(&speeddata_read_serial, 0, sizeof(speedtest));

		memset(&writeprocessdata, 0, sizeof(processdata));
		memset(&readprocessdata, 0, sizeof(processdata));
		memset(&writeprocessdata_4k64, 0, sizeof(processdata));
		memset(&readprocessdata_4k64, 0, sizeof(processdata));
		memset(&writeprocessdata_serial, 0, sizeof(processdata));
		memset(&readprocessdata_serial, 0, sizeof(processdata));

		SetTraceCallback(&DiskIoGuid, eventDiskIo);

		 hwritestart4k = CreateEvent(NULL, FALSE, FALSE, NULL);
		 hreadstart4k = CreateEvent(NULL, FALSE, FALSE, NULL);
		 hwritestart4k64 = CreateEvent(NULL, FALSE, FALSE, NULL);
		 hreadstart4k64 = CreateEvent(NULL, FALSE, FALSE, NULL);
		 hwritestartserial = CreateEvent(NULL, FALSE, FALSE, NULL);
		 hreadstartserial = CreateEvent(NULL, FALSE, FALSE, NULL);

		 hwrite4k_end = CreateEvent(NULL, FALSE, FALSE, NULL);
		 hread4k_end = CreateEvent(NULL, FALSE, FALSE, NULL);
		 hwrite4k64_end = CreateEvent(NULL, FALSE, FALSE, NULL);
		 hread4k64_end = CreateEvent(NULL, FALSE, FALSE, NULL);
		 hwriteserial_end = CreateEvent(NULL, FALSE, FALSE, NULL);
		 hreadserial_end = CreateEvent(NULL, FALSE, FALSE, NULL);

		HANDLE htraceevent = CreateThread(NULL, NULL, TraceEvents, NULL, 0, NULL);

		return 1;

	}



	void startdisktest(char c, BOOL t_4k, BOOL t_4k64, BOOL t_serial)
	{
		part_c = c;
		is_test_4k = t_4k;
		is_test_4k64 = t_4k64;
		is_test_serial = t_serial;
		HANDLE hthread = CreateThread(NULL, NULL, etwThreadFunc, pProperties, 0, NULL);
		HANDLE htest = CreateThread(NULL, NULL, createtest, NULL, 0, NULL);
		WaitForSingleObject(hthread, INFINITE);
		WaitForSingleObject(htest, INFINITE);
	}

	void endtest()
	{
		ControlTrace((TRACEHANDLE)0, KERNEL_LOGGER_NAME, pProperties, EVENT_TRACE_CONTROL_STOP);

		free(pProperties);
		printf("exit\n");
	}

	void setwaittime(long w_time)
	{
		waittime = w_time;
	}

	void setmintime(long m_time)
	{
		min_time = m_time;

	}

	void stopall()
	{
		waittime = 0;

	}
	//-----------瞬时速度----------------------------------
	diskmarkoutput get_instant_data()
	{
		diskmarkoutput output;
		output.writeiops_4k = writeprocessdata.instant_iops;
		output.writespeed_4k = writeprocessdata.instant_mbytespersec;
		output.readiops_4k = readprocessdata.instant_iops;
		output.readspeed_4k = readprocessdata.instant_mbytespersec;

		output.writeiops_4k64 = writeprocessdata_4k64.instant_iops;
		output.writespeed_4k64 = writeprocessdata_4k64.instant_mbytespersec;
		output.readiops_4k64 = readprocessdata_4k64.instant_iops;
		output.readspeed_4k64 = readprocessdata_4k64.instant_mbytespersec;

		output.writeiops_serial = writeprocessdata_serial.instant_iops;
		output.writespeed_serial = writeprocessdata_serial.instant_mbytespersec;
		output.readiops_serial = readprocessdata_serial.instant_iops;
		output.readspeed_serial = readprocessdata_serial.instant_mbytespersec;
		return output;
	
	}

	diskmarkoutput get_output_data()
	{
		diskmarkoutput output;
		output.writeiops_4k = writeprocessdata.iops;
		output.writespeed_4k = writeprocessdata.mbytespersec;
		output.readiops_4k = readprocessdata.iops;
		output.readspeed_4k = readprocessdata.mbytespersec;

		output.writeiops_4k64 = writeprocessdata_4k64.iops;
		output.writespeed_4k64 = writeprocessdata_4k64.mbytespersec;
		output.readiops_4k64 = readprocessdata_4k64.iops;
		output.readspeed_4k64 = readprocessdata_4k64.mbytespersec;

		output.writeiops_serial = writeprocessdata_serial.iops;
		output.writespeed_serial = writeprocessdata_serial.mbytespersec;
		output.readiops_serial = readprocessdata_serial.iops;
		output.readspeed_serial = readprocessdata_serial.mbytespersec;
		return output;
	}


	diskmarkoutput fasttest()
	{

		initial();

		startdisktest('C', 1, 1, 1);

		endtest();

		return get_output_data();
	}

/*	int main()
	{
		initial();


		startdisktest('C', 0, 0, 1);


		endtest();


		return 0;
	}
	*/
}//命名空间结束
/*
int main()
{

PEVENT_TRACE_PROPERTIES pProperties;

pProperties = allocateEventTraceProperties();
if (nullptr == pProperties)
{
return 0;
}
TRACEHANDLE hTraceSession;
//	ControlTrace((TRACEHANDLE)0, KERNEL_LOGGER_NAME,pProperties, EVENT_TRACE_CONTROL_STOP);
ULONG ret = StartTrace(&hTraceSession, KERNEL_LOGGER_NAME, pProperties);

if (ERROR_SUCCESS != ret)
{

if (ret == ERROR_ALREADY_EXISTS)
{
printf("NT Kernel Logger session is already in use\n");
}

}
//	memset(&g_EtwEventCounters, 0, sizeof(struct ETWEventCounters));
memset(&writespeeddata, 0, sizeof(speedtest));
memset(&readspeeddata, 0, sizeof(speedtest));
SetTraceCallback(&DiskIoGuid, eventDiskIo);

HANDLE hwritestart4k = CreateEvent(NULL, FALSE, FALSE, NULL);
HANDLE hreadstart4k = CreateEvent(NULL, FALSE, FALSE, NULL);
HANDLE hwritestart4k64 = CreateEvent(NULL, FALSE, FALSE, NULL);
HANDLE hreadstart4k64 = CreateEvent(NULL, FALSE, FALSE, NULL);
HANDLE hwritestartserial = CreateEvent(NULL, FALSE, FALSE, NULL);
HANDLE hreadstartserial = CreateEvent(NULL, FALSE, FALSE, NULL);

HANDLE htraceevent = CreateThread(NULL, NULL, TraceEvents, NULL, 0, NULL);

HANDLE hthread = CreateThread(NULL, NULL, etwThreadFunc, pProperties, 0, NULL);
HANDLE htest = CreateThread(NULL, NULL, createtest, NULL, 0, NULL);
//	TraceEvents();
printf("ready\n");

WaitForSingleObject(hthread, INFINITE);
WaitForSingleObject(htest, INFINITE);

ControlTrace((TRACEHANDLE)0, KERNEL_LOGGER_NAME, pProperties, EVENT_TRACE_CONTROL_STOP);

free(pProperties);
printf("exit\n");
return 0;
}
*/