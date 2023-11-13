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

    void InvertList() //���ú���
    {
        LNode *p, *q;
        int i = ListLength() - 1;
        p = L->next;

        L->next = NULL; //ժ��ͷ���

        while (i--) //ѭ�������½ڵ����β���ͷ�ڵ�֮��
        {
            q = p->next;
            p->next = L->next;
            L->next = p;
            p = q;
        }
        p->next = L->next; //�����һ���ڵ����ͷ�ڵ�֮��
        L->next = p;
    }
};

int main()
{
    LinkList List;
    List.InitList();
    cout << "����һ�����Ա�" << endl;
    List.CreatList();
    cout << "����ǰ���Ա�Ϊ��" << endl;
    List.ListTraverse();
    List.InvertList();
    cout << "���ú����Ա�Ϊ��" << endl;
    List.ListTraverse();
}