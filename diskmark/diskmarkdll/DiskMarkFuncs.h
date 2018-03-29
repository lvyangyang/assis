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
	//���ٲ��ԣ�ʹ��Ĭ�����ã��Ѿ�������ʼ���ͽ������̣����ز��Խ����ֱ�����Խ��������Ż᷵�ء�
	DISKMARKFUNCSDLL_API 	diskmarkoutput fasttest(void);
	//��ʼ�����ɹ��򷵻�1��ʧ�ܷ���0
	DISKMARKFUNCSDLL_API	int initial(void);
	//����ÿһ�������ȴ�ʱ�䣨Ӧ�Ե����ܴ��̲��Թ��������⣩
	DISKMARKFUNCSDLL_API	void setwaittime(long w_time);
	//����ÿһ����Ե���Ͳ���ʱ�䣨Ӧ�Ը����ܴ��̣�
	DISKMARKFUNCSDLL_API    void setmintime(long m_time);
	//��ʼ���ԣ���ֱ�����Խ��������Ż᷵�ء�char c�趨�����̷�����д����BOOL t_4k, BOOL t_4k64, BOOL t_serial�����ò����0�����⣬1�����
	DISKMARKFUNCSDLL_API    void startdisktest(char c, BOOL t_4k, BOOL t_4k64, BOOL t_serial);
	//���ٽ������ԣ���ʵ�ǽ��ȴ�ʱ����Ϊ0��
	DISKMARKFUNCSDLL_API	void stopall(void);
	//��������
	DISKMARKFUNCSDLL_API    void endtest(void);
	//��ò���ʱ��˲ʱ�ٶ�
	DISKMARKFUNCSDLL_API    diskmarkoutput get_instant_data(void);
	//��ò��Խ�����ɻ���Ѿ���ɵĲ���������û��ɵĽ��Ϊ0
	DISKMARKFUNCSDLL_API	diskmarkoutput get_output_data(void);

}
/*ֱ�ӵ���fasttest,����������᷵�ز������ݣ���������ȫ��Ĭ��

��Ҫ�Բ��Խ������ã���ִ��initial������Ȼ��ͨ��setwaittime��setmintime�������õ������ʱ�䣬����startdisktest��������

�����ڼ����ͨ��get_instant_data��õ�ǰ����״̬��˲ʱ�ٶȣ���Ҳ����ͨ��get_output_data����Ѿ���ɵĲ��Խ�������������⿪�̣߳���Ϊ���Ի�����������غ������̡߳�

*/