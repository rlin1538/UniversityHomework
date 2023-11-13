#include <iostream>
#define MAXSIZE 256
using namespace std;

struct RecordType
{
    int key;
    //InfoType info;
};
struct SqList
{
    RecordType r[MAXSIZE + 1];
    int length;
};
//交换排序
void SwapSort(SqList &a, int n)
{
    RecordType temp;

    for (int i = 1; i <= n - 1; i++)
        for (int j = 1; j <= n - i; j++)
            if (a.r[j + 1].key < a.r[j].key)
            {
                temp = a.r[j];
                a.r[j] = a.r[j + 1];
                a.r[j + 1] = temp;
            }
    cout << "交换排序结果：" << endl;
    for (int i = 1; i <= n; i++)
        cout << a.r[i].key << '\t';
    cout << endl;
}
//选择排序
void ChooseSort(SqList a, int n)
{
    int min;
    RecordType temp;

    for (int i = 1; i <= n - 1; i++)
    {
        min = i;
        for (int j = i + 1; j <= n; j++)
            if (a.r[j].key < a.r[min].key)
                min = j;
        if (min != i)
        {
            temp = a.r[i];
            a.r[i] = a.r[min];
            a.r[min] = temp;
        }
    }
    cout << "选择排序结果：" << endl;
    for (int i = 1; i <= n; i++)
        cout << a.r[i].key << '\t';
    cout << endl;
}

//归并两组数据
void Merge(SqList &L, int low, int mid, int high)
{
    RecordType *T;
    int i, j, k = 1;
    T = new RecordType[high - low + 1];
    i = low;
    j = mid + 1;

    while (i <= mid && j <= high) //将两组数中较小者依次放入T中
    {
        if (L.r[i].key < L.r[j].key)
            T[k++] = L.r[i++];
        else
            T[k++] = L.r[j++];
    }
    while (i <= mid)
        T[k++] = L.r[i++]; //剩余数据存入T数组
    while (j <= high)
        T[k++] = L.r[j++]; //剩余数据存入T数组
    for (k = 1, i = low; i <= high; k++, i++)
        L.r[i] = T[k];
}
//归并的调用
void MSort(SqList &L, int len)
{
    int i = 1;
    while (i + 2 * len <= L.length)
    {
        Merge(L, i, i + len - 1, i + 2 * len - 1); //归并两组长度为len的数据
        i = i + 2 * len;                           //跳到下一组
    }
    if (i + len <= L.length)
        Merge(L, i, i + len - 1, L.length); //归并剩下长度不足2个len的数据
}
//归并排序
void MergeSort(SqList &L)
{
    for (int len = 1; len <= L.length; len *= 2)
        MSort(L, len); //依次对各个长度的数据组归并
    cout << "归并排序结果：" << endl;
    for (int i = 1; i <= L.length; i++)
        cout << L.r[i].key << '\t';
    cout << endl;
}
int main()
{
    SqList a, b, c, d;

    cout << "输入元素个数：";
    cin >> a.length;
    b.length = c.length = d.length = a.length;
    for (int i = 1; i <= a.length; i++)
    {
        cin >> a.r[i].key;
        b.r[i].key = c.r[i].key = d.r[i].key = a.r[i].key;
    }
    SwapSort(b, b.length);
    ChooseSort(c, c.length);
    MergeSort(d);
}
/*
10
48 35 66 91 74 18 22 48 57 03
*/