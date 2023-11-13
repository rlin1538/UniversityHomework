#include <iostream>
using namespace std;

struct LNode //����һ���ڵ�ṹ��
{
    int data;
    struct LNode *next;
};

class LinkList //����һ����������
{
    LNode *L; //ͷָ��
public:
    //��ʼ�������١���ղ���
    void InitList()
    {
        L = new LNode;
        L->data = 0;
        L->next = NULL;
    }
    void CreatList(int n)
    {
        LNode *s;
        LNode *p;
        
        p = L;
        for (int i = 0; i < n; i++)
        {
            s = new LNode;
            s->data=i+1;
            s->next = p->next;
            p->next = s;
            p = p->next;
        }
    }
    void DestroyList()
    {
        LNode *p, *q;
        p = L->next;
        while (p)
        {
            q = p->next;
            delete[] p;
            p = q;
        }
        L = NULL; //����ͷָ��Ϊ�գ��ݻ�����
    }
    void ClearList()
    {
        LNode *p, *q;
        p = L->next;
        while (p) //���ɾ���ڵ�
        {
            q = p->next;
            delete[] p;
            p = q;
        }
        L->next = NULL; //ͷָ��ָ��գ��������
    }
    //�����Ͳ���
    bool ListEmpty()
    {
        if (L != NULL)
            if (L->next == NULL)
                return true;
            else
                return false;
    }
    int ListLength()
    {
        LNode *p;
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
    void GetElem(int i, int &e)
    {
        LNode *p;
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
    int LocateElem(int e)
    {
        int i = 0; //����
        LNode *p;
        if (L)
        {
            p = L->next;
            while (p && (p->data != e)) //��e�������������ݼ���ѭ��
            {
                ++i;
                p = p->next;
            }
            if (i >= ListLength())
            {
                cout << "NotFound";
                return 0;
            }
            return i + 1;
        }
        else
            cout << "LocateElem failed" << endl;
        return 0;
    }
    void PriorElem(int cur_e, int &pre_e)
    {
        int pos;
        if (L)
        {
            pos = LocateElem(cur_e); //��λcur_e��λ��
            if (pos > 1)
            {
                GetElem(pos - 1, pre_e); //����posǰһ���ڵ�����
                cout << "ǰ��Ԫ���ǣ�" << pre_e << endl;
            }
            else
            {
                cout << "NotFound PriorElem" << endl;
            }
        }
    }
    void NextElem(int cur_e, int &next_e)
    {
        int pos;
        if (L)
        {
            pos = LocateElem(cur_e); //��λcur_e��λ��
            if (pos > 0 && pos < ListLength())
            {
                GetElem(pos + 1, next_e);
                cout << "���Ԫ���ǣ�" << next_e << endl;
            }
            else
            {
                cout << "NotFound NextElem" << endl;
            }
        }
    }
    void ListTraverse()
    {
        LNode *p;
        if (L)
        {
            p = L->next;
            while (p) //����������Ч�Ľڵ�
            {
                cout << p->data << '\t';
                p = p->next;
            }
            cout << endl;
        }
        else
            cout << "List isn't exists" << endl;
    }
    //�ӹ��Ͳ���
    void SetElem(int i, int &e)
    {
        LNode *p;
        int j = 1;
        int temp;
        if (L && (1 <= i && i <= ListLength()))
        {
            p = L->next;
            while (j < i)
            {
                p = p->next;
                j++;
            }
            temp = p->data;
            p->data = e;
            e = temp;
        }
        else
            cout << "SetElem Failed->" << endl;
    }
    void InsertElem(int i, int e)
    {
        LNode *s;
        LNode *p;

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
    void DeleteElem(int i, int &e)
    {
        LNode *p, *q;
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
};

int main()
{
    int n,m;
    LinkList List;
    int temp=0;
    int e;
    cin>>n>>m;
    List.InitList();
    List.CreatList(n);
    while (List.ListLength())
    {
        temp = (temp+m) % List.ListLength();
        if (temp == 0) temp=List.ListLength();
        List.DeleteElem(temp,e);
        temp--;
        cout<<e<<"\t";
    }
}