#include <iostream>
#define LISTINITSIZE 256
#define LISTINCREMENT 128
using namespace std;

struct SequList
{
    int *pData;
    int nLen, nElem;
};
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
    cout << "输入元素个数：";
    cin >> n;
    L.nElem = n;

    for (int i = 0; i < n; i++)
    {
        cout << "输入第" << i + 1 << "个元素：";
        cin >> *(L.pData + i);
    }
}

int LocateElem(SequList L, int e)
{
    int i = 0; //计数
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
void ListTraverse(SequList L)
{
    if (L.pData)
    {
        for (int i = 0; i < L.nElem; i++)
            cout << L.pData[i] << '\t';
        cout << endl;
    }
}
void InsertElem(SequList &L, int i, int e)
{
    int *temp;
    if (L.pData)
    {
        if (i < 1 || i > L.nElem)
            return;
        if (L.nLen >= L.nElem) //表满了扩大空间
        {
            temp = new int[L.nLen + LISTINCREMENT];
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

void Swap(SequList &L, int i, int min)
{
    int temp;
    temp = L.pData[i];
    L.pData[i] = L.pData[min];
    L.pData[min] = temp;
}
void SelSort(SequList &L)
{
    int min;
    for (int i = 0; i < L.nElem - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < L.nElem; j++)
        {
            if (L.pData[j] < L.pData[min])
                min = j;
        }
        if (i != min)
            Swap(L, i, min);
    }
}

void Combine(SequList &A, SequList &B)
{
    for (int j = 0; j < B.nElem; j++)
    {
        if (LocateElem(A, B.pData[j]))
            continue;
        InsertElem(A, 1, B.pData[j]);
    }
    SelSort(A);
}

int main()
{
    SequList ListA, ListB;
    InitList(ListA);
    InitList(ListB);
    CreatList(ListA);
    CreatList(ListB);
    Combine(ListA, ListB);
    cout << "合并后为：";
    ListTraverse(ListA);
}