#include <iostream>
#define LISTINITSIZE 256
#define LISTINCREMENT 128
using namespace std;

struct SequList
{
    int *pData;
    int nLen, nElem;
} List;

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
void ListTraverse(SequList L)
{
    if (L.pData)
    {
        for (int i = 0; i < L.nElem; i++)
            cout << L.pData[i] << '\t';
        cout << endl;
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
int main()
{
    InitList(List);
    CreatList(List);
    SelSort(List);
    cout << "排序后为：";
    ListTraverse(List);
}