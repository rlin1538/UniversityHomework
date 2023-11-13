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

    void DedupeList() //ȥ�غ���
    {
        LNode *p, *i, *j;
        int count = 0;
        p = L->next;
        while (p != NULL) //��һ��ѭ��
        {
            i = p;
            while (i->next != NULL) //�ڶ���ѭ��
            {
                j = i->next;
                if (j->data == p->data) //ɾ����ͬ��
                {
                    i->next = j->next;
                    delete[] j;
                    j = i->next;
                    continue;
                }
                i = j;
                j = i->next;
            }
            p = p->next;
        }
    }
};

int main()
{
    LinkList List;
    List.InitList();
    cout << "����һ�����Ա�" << endl;
    List.CreatList();
    cout << "ȥ��ǰ���Ա�Ϊ��" << endl;
    List.ListTraverse();
    List.DedupeList();
    cout << "ȥ�غ����Ա�Ϊ��" << endl;
    List.ListTraverse();
}