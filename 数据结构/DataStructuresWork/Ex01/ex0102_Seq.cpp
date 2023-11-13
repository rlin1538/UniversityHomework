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

void InvertList(SequList &L) //倒置函数
{
    int i, j;
    int temp;
    i = 0;
    j = ListLength(L) - 1;
    while (i < j)
    {
        temp = *(L.pData + i);
        *(L.pData + i) = *(L.pData + j);
        *(L.pData + j) = temp;
        i++;
        j--;
    }
}

int main()
{
    InitList(List);
    cout << "创建一个线性表：" << endl;
    CreatList(List);
    cout << "倒置前线性表为：" << endl;
    ListTraverse(List);
    InvertList(List);
    cout << "倒置后线性表为：" << endl;
    ListTraverse(List);
}