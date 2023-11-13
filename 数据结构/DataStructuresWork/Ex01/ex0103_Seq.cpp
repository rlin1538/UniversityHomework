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
//�����Ͳ���
int ListLength(SequList L)
{
    if (L.pData)
    {
        return L.nElem;
    }
    return 0;
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

void DedupeList(SequList &L) //ȥ�غ���
{
    int i = 0;
    int j;
    int e;

    while (i < ListLength(L)) //��һ��ѭ��
    {
        j = i + 1;
        while (j < ListLength(L)) //�ڶ���ѭ��
        {
            if (L.pData[j] == L.pData[i]) //ɾ����ͬ��
            {
                DeleteElem(L, j + 1, e);
                j--;
            }
            j++;
        }
        i++;
    }
}

int main()
{

    InitList(List);
    cout << "����һ�����Ա�" << endl;
    CreatList(List);
    cout << "ȥ��ǰ���Ա�Ϊ��" << endl;
    ListTraverse(List);
    DedupeList(List);
    cout << "ȥ�غ����Ա�Ϊ��" << endl;
    ListTraverse(List);
}