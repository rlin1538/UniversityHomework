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

int main()
{
    LinkList L;
    L.InitList();
    L.CreatList();
    L.SelSort();
    cout << "�����Ϊ��";
    L.ListTraverse();
}