#include <windows.h>
#include <tlhelp32.h>	//���̿��պ���ͷ�ļ�
#include <stdio.h>
 
int main()
{
	int countProcess=0;									//��ǰ����������������
	PROCESSENTRY32 currentProcess;						//��ſ��ս�����Ϣ��һ���ṹ��
	currentProcess.dwSize = sizeof(currentProcess);		//��ʹ������ṹ֮ǰ�����������Ĵ�С
	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);//��ϵͳ�ڵ����н�����һ������
	
	if (hProcess == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot()����ʧ��!\n");
		return -1;
	}
	
	_Bool bMore=Process32First(hProcess,&currentProcess);  //��ȡ��һ��������Ϣ 

	while(bMore)
	{
		printf("PID=%5u    PName= %s\n",currentProcess.th32ProcessID,currentProcess.szExeFile); //�������̿��գ�������ʾÿ��������Ϣ
        bMore=Process32Next(hProcess,&currentProcess);    //������һ��
		countProcess++;
	}
	
	CloseHandle(hProcess);	//���hProcess���
	printf("��������%d������������\n",countProcess);
	system("pause");
	return 0;
}