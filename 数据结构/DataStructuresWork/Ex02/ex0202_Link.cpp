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
    void InitList()
    {
        L = new LNode;
        L->data = 0;
        L->next = NULL;
    }
    void CreatList()
    {
        int n;
        LNode *s;
        LNode *p;
        cout << "����Ԫ�ظ�����";
        cin >> n;

        p = L;
        for (int i = 0; i < n; i++)
        {
            s = new LNode;
            cout << "�����" << i + 1 << "��Ԫ�أ�";
            cin >> s->data;
            s->next = p->next;
            p->next = s;
            p = p->next;
        }
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
                //cout << "NotFound";
                return 0;
            }
            return i + 1;
        }

        //cout << "LocateElem failed" << endl;
        return 0;
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
    void SelSort()
    {
        LNode *p, *q, *min;
        int temp;
        for (p = L->next; p->next != NULL; p = p->next)
        {
            min = p;
            for (q = p->next; q; q = q->next)
            {
                if (q->data < min->data)
                    min = q;
            }
            temp = p->data;
            p->data = min->data;
            min->data = temp;
        }
    }
};

void Combine(LinkList &A, LinkList &B)
{
    int e;
    for (int i = 1; i <= B.ListLength(); i++)
    {
        B.GetElem(i, e);
        if (A.LocateElem(e))
            continue;
        A.InsertElem(1, e);
    }
    A.SelSort();
}

int main()
{
    LinkList A, B;
    A.InitList();
    B.InitList();
    A.CreatList();
    B.CreatList();
    cout << "�ϲ���";
    Combine(A, B);
    A.ListTraverse();
}