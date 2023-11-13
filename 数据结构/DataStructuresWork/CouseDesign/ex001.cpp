//1.系统进程统计
#include <iostream>
using namespace std;
#include "Process_ZX.h"


ProInfo prolist[1024];
int pronum;

struct LNode //定义一个单链表结点结构体
{
    ProInfo data;
    struct LNode* next;
};
struct DNode //定义一个双链表结点的结构体
{
    ProInfo data;
    struct DNode* next, * pre;
};

class EndedProcessList //抽象一个双链表类
{
    DNode* L; //头指针
    DNode* tail;//尾指针
public:
    void InitList()
    {
        L = new DNode;
        //L->data = 0;
        L->next = NULL;
        L->pre = NULL;
        tail = L;
    }
    int ListLength()
    {
        DNode* p;
        int count = 0;
        if (L)
        {
            p = L->next;
            while (p != NULL)
            {
                count++;
                p = p->next;
            }
        }
        //else
        //cout << "List isn't exists->" << endl;
        return count;
    }
    int LocateElem(ProInfo e)
    {
        int i = 0; //计数
        DNode* p;
        if (L)
        {
            p = L->next;
            while (p && _tcscmp(p->data.Name , e.Name)!=0) //当e不是链表中数据继续循环
            {
                ++i;
                p = p->next;
            }
            if (i >= ListLength())
            {
                //cout << "NotFound";
                return 0;
            }
            return i + 1;
        }
        //else
        //cout << "LocateElem failed" << endl;
        return 0;
    }
    void ListTraverse()
    {
        DNode* p;
        if (L)
        {
            p = L->next;
            while (p) //遍历所有有效的节点
            {
                PrintProInfo(p->data);
                p = p->next;
            }
            cout << endl;
        }
        //else
        //cout << "List isn't exists" << endl;
    }
    void InsertElem( ProInfo e) //插入最后面
    {
        DNode* s;
        
            s = new DNode;
            s->data = e; //创建新节点

            s->next = tail->next;
            s->pre = tail;
            tail->next = s;

            tail = tail->next;
    }
    void DeleteElem(int i, ProInfo& e)
    {
        DNode* p, * q;
        int j = 1;
        if (L != NULL)
        {
            p = L->next;
            q = L;
            while (j < i)
            {
                q = p;
                p = p->next;
                j++;
            }
            if (p->next)
            {
                p->next->pre = q;
                q->next = p->next;
            }
            else
                q->next = NULL;
            e = p->data;
            delete[] p;
        }
    }
    void Sort()
    {
        DNode* t, * p, * q = L;

        p = L->next;
        L->next = NULL;
        while (p)
        {
            q = L;
            t = p->next;
            while (q->next && MSTimeCMP(p->data.DuraTime, q->next->data.DuraTime) == 1)
                q = q->next;
            p->next = q->next;
            p->pre = q;
            if (q->next)
                q->next->pre = p;
            q->next = p;
            p = t;
        }
    }
};

class CurrentProcessList //抽象一个单链表类
{
    LNode* L; //头指针
public:
    void InitList()
    {
        L = new LNode;
        //L->data = 0;
        L->next = NULL;
    }
    void ClearList()
    {
        LNode* p, * q;
        p = L->next;
        while (p) //逐个删除节点
        {
            q = p->next;
            delete[] p;
            p = q;
        }
        L->next = NULL; //头指针指向空，链表清空
    }
    int ListLength()
    {
        LNode* p;
        int count = 0;
        if (L)
        {
            p = L->next;
            while (p != NULL)
            {
                count++;
                p = p->next;
            }
        }
        else
            cout << "List isn't exists->" << endl;
        return count;
    }
    void GetElem(int i, ProInfo& e)
    {
        LNode* p;
        int j = 1;
        if (L && (i > 0 && i <= ListLength())) //判断L存在且i符合定义域
        {
            p = L->next;
            while (j < i)
            {
                p = p->next;
                j++;
            }
            e = p->data;
        }
        else
            cout << "GetElem failed!" << endl;
    }
    int LocateElem(ProInfo e)
    {
        int i = 0; //计数
        LNode* p;
        if (L)
        {
            p = L->next;
            while (p && (p->data.ID != e.ID)) //当e不是链表中数据继续循环
            {
                ++i;
                p = p->next;
            }
            if (i >= ListLength())
            {
                //cout << "NotFound";
                return 0;
            }
            return i + 1;
        }
        else
            //cout << "LocateElem failed" << endl;
            return 0;
    }
    void ListTraverse()
    {
        LNode* p;
        if (L)
        {
            p = L->next;
            while (p) //遍历所有有效的节点
            {
                PrintProInfo(p->data);
                p = p->next;
            }
            cout << endl;
        }
        else
            cout << "List isn't exists" << endl;
    }
    void InsertElem(int i, ProInfo e)
    {
        LNode* s;
        LNode* p;

        int j = 1;
        if (L && (i >= 0 && i <= ListLength()))
        {
            s = new LNode;
            s->data = e; //创建新节点

            p = L;
            while (j < i) //定位i
            {
                p = p->next;
                j++;
            }
            s->next = p->next;
            p->next = s;
        }
    }
    void DeleteElem(int i, ProInfo& e)
    {
        LNode* p, * q;
        int j = 1;
        if (L != NULL)
        {
            p = L->next;
            q = L;
            while (j < i)
            {
                q = p;
                p = p->next;
                j++;
            }
            q->next = p->next;
            e = p->data;
            delete[] p;
        }
    }
    void Sort()
    {
        LNode* t, * p, * q = L;

        p = L->next;
        L->next = NULL;
        while (p)
        {
            q = L;
            t = p->next;
            while (q->next && p->data.Memory < q->next->data.Memory)
                q = q->next;
            p->next = q->next;
            q->next = p;
            p = t;
        }
    }
};

void FreshList(ProInfo L[], int n, CurrentProcessList C, EndedProcessList D)
{
    int temp;
    ProInfo T;
    for (int i = 0; i < n; i++)
        if (temp = D.LocateElem(L[i]))       //如果新的进程列表里有进程在D中
            D.DeleteElem(temp, T);           //则将其从D中删去
    for (int i = 0; i < C.ListLength(); i++) //找已结束的进程放进D里
    {
        C.GetElem(i + 1, T);
        for (int j = 0; j < n; j++)
        {
            if (T.ID == L[j].ID)
                break;
            else if (j == n - 1)
            {
                D.InsertElem(T); //将结束的进程放进D
            }
        }
    }
    C.ClearList(); //清空C
    for (int i = 0; i < n; i++)
        C.InsertElem(0, L[i]); //将新的进程列表插入C中

    C.Sort(); //对C进行排序
    D.Sort();
}
int main()
{
    CurrentProcessList CurList; //当前进程列表
    EndedProcessList DelList; //已结束进程列表
    //初始化
    AdjustPurview();
    CurList.InitList();
    DelList.InitList();
    GetCurrentProcesses(prolist, pronum, 1024);
    for (int i = 0; i < pronum; i++)
        CurList.InsertElem(0, prolist[i]); //将新的进程列表插入C中
    while (1)
    {

        //执行
        GetCurrentProcesses(prolist, pronum, 1024);
        FreshList(prolist, pronum, CurList, DelList);
        system("cls");
        cout << "----------------当前活动的进程----------------" << endl;
        CurList.ListTraverse();
        cout << endl << "----------------已结束的进程------------------" << endl;
        DelList.ListTraverse();
        system("pause");
    }
}
