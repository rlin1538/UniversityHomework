#include <iostream>
#define LISTINITSIZE 256
#define LISTINCREMENT 128
using namespace std;

struct SequList
{
    int *pData;
    int nLen, nElem;
} List;
//��ʼ�������١���ղ���
void InitList(SequList &L)
{
    L.pData = new int[LISTINITSIZE];
    if (L.pData == NULL)
    {
        cout << "InitList failed!" << endl;
        return;
    }
    L.nElem = 0;
    L.nLen = LISTINITSIZE;
}
void CreatList(SequList &L)
{
    int n;
    cout << "����Ԫ�ظ�����";
    cin >> n;
    L.nElem = n;

    for (int i = 0; i < n; i++)
    {
        cout << "�����" << i + 1 << "��Ԫ�أ�";
        cin >> *(L.pData + i);
    }
}
void DestroyList(SequList &L)
{
    if (L.pData)
    {
        delete[] L.pData;
        L.pData = NULL;
        L.nLen = 0;
        L.nElem = 0;
    }
}
void ClearList(SequList &L)
{
    if (L.pData)
    {
        L.nElem = 0;
    }
}
//�����Ͳ���
bool ListEmpty(SequList L)
{
    if (L.pData)
    {
        if (L.nElem == 0)
            return true;
        else
            return false;
    }
    return true;
}
int ListLength(SequList L)
{
    if (L.pData)
    {
        return L.nElem;
    }
    return 0;
}
void GetElem(SequList L, int i, int &e)
{
    if (L.pData && (1 <= i && i <= ListLength(L)))
    {
        e = L.pData[i - 1];
    }
    else
        cout << "GetElem failed!" << endl;
}
int LocateElem(SequList L, int e)
{
    int i = 0; //����
    if (L.pData)
    {
        while (i < L.nElem)
        {
            if (L.pData[i] == e)
                return ++i;
            else
                i++;
        }
    }
    else
        return 0;
    return 0;
}
void PriorElem(SequList L, int cur_e, int &pre_e)
{
    if (L.pData)
    {
        for (int i = 1; i < L.nElem; i++)
        {
            if (L.pData[i] == cur_e)
            {
                pre_e = L.pData[i - 1];
                return;
            }
        }
        cout << "PriorElem failed.";
    }
}
void NextElem(SequList L, int cur_e, int &next_e)
{
    if (L.pData)
    {
        for (int i = 0; i < L.nElem - 1; i++)
        {
            if (L.pData[i] == cur_e)
            {
                next_e = L.pData[i + 1];
                return;
            }
        }
        cout << "Operation failed.";
    }
}
void ListTraverse(SequList L)
{
    if (L.pData)
    {
        for (int i = 0; i < L.nElem; i++)
            cout << L.pData[i] << '\t';
        cout << endl;
    }
}
//�ӹ��Ͳ���
void SetElem(SequList &L, int i, int &e)
{
    int temp;
    if (L.pData != NULL && (i >= 1 && i <= ListLength(L)))
    {
        temp = L.pData[i - 1];
        L.pData[i - 1] = e;
        e = temp;
    }
}
void InsertElem(SequList &L, int i, int e)
{
    int *temp;
    if (L.pData)
    {
        if (i < 1 || i > L.nElem+1)
            return;
        if (L.nLen >= L.nElem) //����������ռ�
        {
            temp = new int[L.nLen + 10];
            for (int i = 0; i < L.nLen; i++)
                *(temp + i) = L.pData[i];
            L.pData = temp;
            L.nLen += LISTINCREMENT;
        }
        for (int j = L.nElem; j >= i; j--)
        {
            L.pData[j] = L.pData[j - 1];
        }
        L.pData[i - 1] = e;
        L.nElem++;
    }
}
void DeleteElem(SequList &L, int i, int &e)
{
    if (L.pData)
    {
        if (i < 1 || i > L.nElem)
            return;
        e = L.pData[i - 1];
        for (i; i < L.nElem; i++)
        {
            L.pData[i - 1] = L.pData[i];
        }
        L.nElem--;
    }
}

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
    int i;
    int e;
    int sel;
    int cur_e, next_e;
    for (;;)
    {
        switch (sel = menu_sel())
        {
        case 1:
            InitList(List);
            system("pause");
            break;
        case 2:
            CreatList(List);
            system("pause");
            break;
        case 3:
            DestroyList(List);
            system("pause");
            break;
        case 4:
            ClearList(List);
            system("pause");
            break;
        case 5:
            if (ListEmpty(List))
                cout << "���Ա�Ϊ��" << endl;
            else
                cout << "���Ա�Ϊ��" << endl;
            system("pause");
            break;
        case 6:
            cout << ListLength(List) << endl;
            system("pause");
            break;
        case 7:
            cout << "����i��";
            cin >> i;
            GetElem(List, i, e);
            cout << "Ԫ���ǣ�" << e << endl;
            system("pause");
            break;
        case 8:
            cout << "����e��";
            cin >> e;
            cout << "Ԫ��λ���ǣ�" << LocateElem(List, e) << endl;
            system("pause");
            break;
        case 9:
            cout << "����Ԫ��cur_e:";
            cin >> cur_e;
            PriorElem(List, cur_e, e);
            cout << "ǰ��Ԫ���ǣ�" << e;
            system("pause");
            break;
        case 10:
            cout << "����Ԫ��next_e:";
            cin >> next_e;
            NextElem(List, next_e, e);
            cout << "���Ԫ���ǣ�" << e;
            system("pause");
            break;
        case 11:
            ListTraverse(List);
            system("pause");
            break;
        case 12:
            cout << "�����滻λ�ã�";
            cin >> i;
            cout << "�����滻Ԫ�أ�";
            cin >> e;
            SetElem(List, i, e);
            cout << "��ֵ�ǣ�" << e << endl;
            system("pause");
            break;
        case 13:
            cout << "�������λ�ã�";
            cin >> i;
            cout << "�������Ԫ�أ�";
            cin >> e;
            InsertElem(List, i, e);
            system("pause");
            break;
        case 14:
            cout << "����ɾ��λ�ã�";
            cin >> i;
            DeleteElem(List, i, e);
            cout << "ԭֵ�ǣ�" << e << endl;
            system("pause");
            break;
        case 0:
            system("pause");
            break;
        }
        if (sel == 0)
            break;
    }
}