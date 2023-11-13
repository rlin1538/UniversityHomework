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
    void Sort()
    {
        LNode* t, * p, * q = L;

        p = L->next->next;
        while (p)
        {
            q = L;
            t = p->next;
            while (q->next && p->data > q->next->data)
                q = q->next;
            p->next = q->next;
            q->next = p;
            p = t;
        }
    }
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

int menu_sel() //���Բ˵�
{
    char *m[15] = {(char *)"1.��ʼ�����Ա�",
                   (char *)"2.�������Ա�",
                   (char *)"3.ɾ�����Ա�",
                   (char *)"4.������Ա�",
                   (char *)"5.�ж����Ա�Ϊ��",
                   (char *)"6.���Ա���",
                   (char *)"7.��ȡ���Ա�Ԫ��",
                   (char *)"8.��λԪ��λ��",
                   (char *)"9.Ѱ��ǰ��Ԫ��",
                   (char *)"10.Ѱ�Һ��Ԫ��",
                   (char *)"11.�������Ա�",
                   (char *)"12.�滻Ԫ��",
                   (char *)"13.����Ԫ��",
                   (char *)"14.ɾ��Ԫ��",
                   (char *)"0.�˳�"}; //��VS2017֮��ı������������ó����ַ�����ʼ��char���飬�ʼ���(char*)ǿ��ת��
    int i, choice;
    do
    {
        system("cls");
        cout << "-------���˵�-------" << endl;
        for (i = 0; i < 15; i++)
            cout << m[i] << endl;
        cout << "������ѡ��";
        cin >> choice;
    } while (choice < 0 || choice > 14);
    return choice;
}

int main()
{
    LinkList List;
    int i;
    int e;
    int sel;
    int cur_e, next_e;
    for (;;)
    {
        switch (sel = menu_sel())
        {
        case 1:
            List.InitList();
            system("pause");
            break;
        case 2:
            List.CreatList();List.Sort();
            system("pause");
            break;
        case 3:
            List.DestroyList();
            system("pause");
            break;
        case 4:
            List.ClearList();
            system("pause");
            break;
        case 5:
            if (List.ListEmpty())
                cout << "���Ա�Ϊ��" << endl;
            else
                cout << "���Ա�Ϊ��" << endl;
            system("pause");
            break;
        case 6:
            cout << List.ListLength() << endl;
            system("pause");
            break;
        case 7:
            cout << "����i��";
            cin >> i;
            List.GetElem(i, e);
            cout << "Ԫ���ǣ�" << e << endl;
            system("pause");
            break;
        case 8:
            cout << "����e��";
            cin >> e;
            cout << "Ԫ��λ���ǣ�" << List.LocateElem(e) << endl;
            system("pause");
            break;
        case 9:
            cout << "����Ԫ��cur_e:";
            cin >> cur_e;
            List.PriorElem(cur_e, e);
            system("pause");
            break;
        case 10:
            cout << "����Ԫ��next_e:";
            cin >> next_e;
            List.NextElem(next_e, e);
            system("pause");
            break;
        case 11:
            List.ListTraverse();
            system("pause");
            break;
        case 12:
            cout << "�����滻λ�ã�";
            cin >> i;
            cout << "�����滻Ԫ�أ�";
            cin >> e;
            List.SetElem(i, e);
            cout << "��ֵ�ǣ�" << e << endl;
            system("pause");
            break;
        case 13:
            cout << "�������λ�ã�";
            cin >> i;
            cout << "�������Ԫ�أ�";
            cin >> e;
            List.InsertElem(i, e);
            system("pause");
            break;
        case 14:
            cout << "����ɾ��λ�ã�";
            cin >> i;
            List.DeleteElem(i, e);
            cout << "ԭֵ�ǣ�" << e << endl;
            system("pause");
            break;
        case 0:
            break;
        }
        if (sel == 0)
            break;
    }
}