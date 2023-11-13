#pragma once
#ifndef PROCESS_ZX_H
#define PROCESS_ZX_H
/*ͷ�ļ�����*/
#include <windows.h>
#include <stdio.h>
#include <psapi.h>
#include <iostream>
#include <time.h> 
using namespace std;
#define  ProcessNum 1024

/*���ݽṹ����*/
typedef struct MSTime
{
    int minute;
    int second;
} MSTime ;
typedef struct Time
{
    int Year;
    int Month;
    int Day;
    int Hour;
    int Minute;
    int Second;
} Time ;
typedef struct ProcessInfo
{
	DWORD  ID ;                              //����ID,DWORD
	TCHAR  Name[MAX_PATH];                   //��������,TCHAR
	SIZE_T Memory;                           //����ռ���ڴ�,��KΪ��λ
	Time   BeginTime;                        //���̿�ʼʱ��,Time
	MSTime DuraTime;                         //���̳���ʱ��,int (min)
	Time   EndTime;							 //���̽���ʱ��,Time
} ProInfo ;

//��������Ȩ��
#pragma comment(lib, "psapi.lib") 
bool AdjustPurview()
{
    TOKEN_PRIVILEGES TokenPrivileges;
    BOOL bRet;
    HANDLE hToken;

    LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &TokenPrivileges.Privileges[0].Luid);
    OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);

    TokenPrivileges.PrivilegeCount = 1;
    TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    bRet = AdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges, 0, NULL, NULL);

    CloseHandle(hToken);
    return bRet == TRUE;
}
//��ȡ��Ϣ
bool GetCurrentProcesses(ProInfo pil[] ,  int& pronum , int sizeofpil = 1024 )  //��ȡ������Ϣ���ɹ�����true,ʧ�ܷ���false
{//pil ������Ϣ����  pronum ���ؽ������� sizeofpil ������Ϣ������Ԫ�ظ���
    HANDLE hProcess ;                       //���̾����ָ�����
    DWORD ProID;                            //����ID
    PROCESS_MEMORY_COUNTERS pmc ;           //������Ϣ�⣨ʹ�����е��ڴ���Ϣ��
    FILETIME begintime, endtime , ipker , ipuser ;  //���̵Ŀ�ʼʱ�䣬����ʱ��ͽ���ʱ��(�����Ǵ��ں��ġ��û�״̬ʱ��)

    //��ȡ�����б�
    DWORD Processes[1024], cbNeeded , cProcess ;
    if ( !EnumProcesses( Processes , sizeof(Processes), &cbNeeded) )
        return false;
    cProcess = cbNeeded / sizeof(DWORD);
    //�������б����δ򿪽��̻�ȡ��Ϣ
    LPSYSTEMTIME pSystemTime = new SYSTEMTIME;//������filetimeת��Ϊsystemtime��systemtime�������˿���
    DWORD btime = 0, etime = 0;               //DWORD��ʽ�Ŀ�ʼ����ʱ�䣬�����������ʱ��
    int i = 0;
    
    //��ȡϵͳʱ��
    LPSYSTEMTIME systime = new SYSTEMTIME;
    ::GetSystemTime(systime);
    systime->wHour = (systime->wHour + 8) % 24; //ת��UTCʱ��Ϊ����ʱ��
    DWORD stime = systime->wHour * 60 * 60 + systime->wMinute * 60 + systime->wSecond ;//ת��ΪDWORD��,��λS

    //��ʼѭ��Ѱ��
    int j = -1;                  //��Ч���ݵļ�¼index
    for ( i = 0; i < cProcess ; i++ )
    {
        //�򿪽���
        ProID = Processes[i];
        if (ProID == 0)
            continue;
        hProcess = OpenProcess( PROCESS_QUERY_INFORMATION|PROCESS_VM_READ ,FALSE , ProID ); //��IDָ��Ľ��̣���ò鿴��Ϣ����ȡ�ڴ��Ȩ��
        if ( NULL == hProcess)  //���δ�ܳɹ��򿪽��̣����ش���
            continue;

        j++;
        //��ȡ����ID
        pil[j].ID = ProID; 
        //��ȡ��������
        GetModuleFileNameEx( hProcess , NULL, pil[j].Name , MAX_PATH );
        //��ȡ�����ڴ�
        GetProcessMemoryInfo( hProcess , &pmc , sizeof(pmc) );
        pil[j].Memory = pmc.PeakWorkingSetSize / 1024;
        //��ȡ����ʱ��
        GetProcessTimes( hProcess, &begintime, &endtime, &ipker, &ipuser);//��ʼ������
        //��ʼʱ��
        FileTimeToSystemTime( &begintime , pSystemTime );
        pSystemTime->wHour = ( pSystemTime->wHour + 8) % 24;  //��UTCʱ��(ʱ���׼ʱ��)ת��Ϊ����ʱ��
        btime = pSystemTime->wHour * 60 * 60 + pSystemTime->wMinute * 60 + pSystemTime->wSecond ; //����DWORD��ʽ��ʼʱ�䣬��λΪS

        pil[j].BeginTime.Year  = pSystemTime->wYear;
        pil[j].BeginTime.Month = pSystemTime->wMonth;
        pil[j].BeginTime.Day = pSystemTime->wDay;
        pil[j].BeginTime.Hour = pSystemTime->wHour;
        pil[j].BeginTime.Minute = pSystemTime->wMinute;
        pil[j].BeginTime.Second = pSystemTime->wSecond;
        //����ʱ��
        FileTimeToSystemTime( &endtime, pSystemTime );
        pSystemTime->wHour = (pSystemTime->wHour + 8) % 24;  //��UTCʱ��(ʱ���׼ʱ��)ת��Ϊ����ʱ��
        etime = pSystemTime->wHour * 60 * 60 + pSystemTime->wMinute * 60 + pSystemTime->wSecond;//����DWORD��ʽ����ʱ�䣬��λΪS

        pil[j].EndTime.Year = pSystemTime->wYear;
        pil[j].EndTime.Month = pSystemTime->wMonth;
        pil[j].EndTime.Day = pSystemTime->wDay;
        pil[j].EndTime.Hour = pSystemTime->wHour;
        pil[j].EndTime.Minute = pSystemTime->wMinute;
        pil[j].EndTime.Second = pSystemTime->wSecond;
        //����ʱ��
        pil[j].DuraTime.minute = (stime - btime) / 60;
        pil[j].DuraTime.second = (stime - btime) % 60;
    }
    pronum = j + 1;

    return true;
}
//��ӡ��Ϣ
void PrintTime(Time T)
{
    cout << T.Year << "��" << T.Month << "��" << T.Day << "��"<< T.Hour << "ʱ" << T.Minute << "��" << T.Second << "��" <<"\n";
}

void PrintProInfo(ProInfo PI)
{
    if (PI.ID == 0) return;
    cout << "------------------------------------------------" << "\n";
    cout << "����ID��" << PI.ID << "\n";
    printf("�������ƣ�%ws", PI.Name);
    cout << "\n";
    cout << "�����ڴ棺" << PI.Memory << "K" << "\n" ; 
    cout << "��ʼʱ�䣺";
    PrintTime(PI.BeginTime);
    cout << "����ʱ�䣺" << PI.DuraTime.minute << " min "  << PI.DuraTime.second << " s"<< "\n";
    cout << "����ʱ�䣺";
    if ( PI.EndTime.Year == 1601 )  //��ʼʱ�䣬��δ����
    {
        cout << "---" << "\n";
    }
    else
    {
        PrintTime(PI.EndTime);
    }
}

//��ȡϵͳʱ��
void GetSystime(Time& time)
{
    LPSYSTEMTIME systime = new SYSTEMTIME;
    ::GetSystemTime(systime);
    systime->wHour = (systime->wHour + 8) % 24; //ת��UTCʱ��Ϊ����ʱ��

    time.Year = systime->wYear;
    time.Month = systime->wMonth;
    time.Day = systime->wDay;
    time.Hour = systime->wHour;
    time.Minute = systime->wMinute;
    time.Second = systime->wSecond;
}

//����Time
void TimeCPY(Time& mbt, const Time sourcet)
{
    mbt.Year = sourcet.Year;
    mbt.Month = sourcet.Month;
    mbt.Day = sourcet.Day;
    mbt.Hour = sourcet.Hour;
    mbt.Minute = sourcet.Minute;
    mbt.Second = sourcet.Second;
}
//����ProInfo
void ProInfoCPY(ProInfo& mbp, const ProInfo sourcep)
{
    mbp.ID = sourcep.ID;
    mbp.Memory = sourcep.Memory;
    ua_tcscpy_s(mbp.Name, sourcep.Name);
    TimeCPY(mbp.BeginTime, sourcep.BeginTime);
    mbp.DuraTime.minute = sourcep.DuraTime.minute;
    mbp.DuraTime.second = sourcep.DuraTime.second;
    TimeCPY(mbp.EndTime, sourcep.EndTime);
}
//�Ƚ�MSTime
int MSTimeCMP(MSTime time_a, MSTime time_b)//�Ƚ�time_a��time_b,���a����b����1�����aС��b����-1;��ȷ���0
{
    if (time_a.minute > time_b.minute)
    {
        return 1;
    }
    else
    {
        if (time_a.minute < time_b.minute)
            return -1;
        else
        {
            if (time_a.second > time_b.second)
            {
                return 1;
            }
            else
            {
                if (time_a.second < time_b.second)
                {
                    return -1;
                }
                else
                {
                    return 0;
                }
            }
        }
    }
}
#endif // !PROCESS_ZX_H
