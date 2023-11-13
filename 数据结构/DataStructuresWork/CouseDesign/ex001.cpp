//1.ϵͳ����ͳ��
#include <iostream>
using namespace std;
#include "Process_ZX.h"


ProInfo prolist[1024];
int pronum;

struct LNode //����һ����������ṹ��
{
    ProInfo data;
    struct LNode* next;
};
struct DNode //����һ��˫������Ľṹ��
{
    ProInfo data;
    struct DNode* next, * pre;
};

class EndedProcessList //����һ��˫������
{
    DNode* L; //ͷָ��
    DNode* tail;//βָ��
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
        int i = 0; //����
        DNode* p;
        if (L)
        {
            p = L->next;
            while (p && _tcscmp(p->data.Name , e.Name)!=0) //��e�������������ݼ���ѭ��
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
            while (p) //����������Ч�Ľڵ�
            {
                PrintProInfo(p->data);
                p = p->next;
            }
            cout << endl;
        }
        //else
        //cout << "List isn't exists" << endl;
    }
    void InsertElem( ProInfo e) //���������
    {
        DNode* s;
        
            s = new DNode;
            s->data = e; //�����½ڵ�

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

class CurrentProcessList //����һ����������
{
    LNode* L; //ͷָ��
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
        while (p) //���ɾ���ڵ�
        {
            q = p->next;
            delete[] p;
            p = q;
        }
        L->next = NULL; //ͷָ��ָ��գ��������
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
        if (L && (i > 0 && i <= ListLength())) //�ж�L������i���϶�����
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
        int i = 0; //����
        LNode* p;
        if (L)
        {
            p = L->next;
            while (p && (p->data.ID != e.ID)) //��e�������������ݼ���ѭ��
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
            while (p) //����������Ч�Ľڵ�
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
            s->data = e; //�����½ڵ�

            p = L;
            while (j < i) //��λi
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
        if (temp = D.LocateElem(L[i]))       //����µĽ����б����н�����D��
            D.DeleteElem(temp, T);           //�����D��ɾȥ
    for (int i = 0; i < C.ListLength(); i++) //���ѽ����Ľ��̷Ž�D��
    {
        C.GetElem(i + 1, T);
        for (int j = 0; j < n; j++)
        {
            if (T.ID == L[j].ID)
                break;
            else if (j == n - 1)
            {
                D.InsertElem(T); //�������Ľ��̷Ž�D
            }
        }
    }
    C.ClearList(); //���C
    for (int i = 0; i < n; i++)
        C.InsertElem(0, L[i]); //���µĽ����б����C��

    C.Sort(); //��C��������
    D.Sort();
}
int main()
{
    CurrentProcessList CurList; //��ǰ�����б�
    EndedProcessList DelList; //�ѽ��������б�
    //��ʼ��
    AdjustPurview();
    CurList.InitList();
    DelList.InitList();
    GetCurrentProcesses(prolist, pronum, 1024);
    for (int i = 0; i < pronum; i++)
        CurList.InsertElem(0, prolist[i]); //���µĽ����б����C��
    while (1)
    {

        //ִ��
        GetCurrentProcesses(prolist, pronum, 1024);
        FreshList(prolist, pronum, CurList, DelList);
        system("cls");
        cout << "----------------��ǰ��Ľ���----------------" << endl;
        CurList.ListTraverse();
        cout << endl << "----------------�ѽ����Ľ���------------------" << endl;
        DelList.ListTraverse();
        system("pause");
    }
}
