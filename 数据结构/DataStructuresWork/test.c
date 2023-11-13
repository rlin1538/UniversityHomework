#include <windows.h>
#include <tlhelp32.h>	//进程快照函数头文件
#include <stdio.h>
 
int main()
{
	int countProcess=0;									//当前进程数量计数变量
	PROCESSENTRY32 currentProcess;						//存放快照进程信息的一个结构体
	currentProcess.dwSize = sizeof(currentProcess);		//在使用这个结构之前，先设置它的大小
	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);//给系统内的所有进程拍一个快照
	
	if (hProcess == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot()调用失败!\n");
		return -1;
	}
	
	_Bool bMore=Process32First(hProcess,&currentProcess);  //获取第一个进程信息 

	while(bMore)
	{
		printf("PID=%5u    PName= %s\n",currentProcess.th32ProcessID,currentProcess.szExeFile); //遍历进程快照，轮流显示每个进程信息
        bMore=Process32Next(hProcess,&currentProcess);    //遍历下一个
		countProcess++;
	}
	
	CloseHandle(hProcess);	//清除hProcess句柄
	printf("共有以上%d个进程在运行\n",countProcess);
	system("pause");
	return 0;
}