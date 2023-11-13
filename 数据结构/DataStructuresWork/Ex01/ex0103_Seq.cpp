#include <iostream>
#define LISTINITSIZE 256
#define LISTINCREMENT 128
using namespace std;

struct SequList
{
    int *pData;
    int nLen, nElem;
} List;
//初始化、销毁、清空操作
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
//访问型操作
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
//加工型操作
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

void DedupeList(SequList &L) //去重函数
{
    int i = 0;
    int j;
    int e;

    while (i < ListLength(L)) //第一层循环
    {
        j = i + 1;
        while (j < ListLength(L)) //第二层循环
        {
            if (L.pData[j] == L.pData[i]) //删除相同数
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
    cout << "创建一个线性表：" << endl;
    CreatList(List);
    cout << "去重前线性表为：" << endl;
    ListTraverse(List);
    DedupeList(List);
    cout << "去重后线性表为：" << endl;
    ListTraverse(List);
}