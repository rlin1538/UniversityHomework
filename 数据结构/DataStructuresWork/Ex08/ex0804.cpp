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
//大顶堆调整
void HeapAdjust(SqList &L, int low, int high)
{
    RecordType temp = L.r[low];
    int i = low, j = 2 * i; //j为i的左孩子

    while (j <= high)
    {
        if (j + 1 <= high && L.r[j + 1].key > L.r[j].key) //挑选左右孩子较大者
            j++;
        if (temp.key >= L.r[j].key) //如果孩子不必根大
            break;
        L.r[i] = L.r[j]; //否则继续往下筛选
        i = j;
        j = 2 * i;
    }
    L.r[i] = temp; //将原根结点放入合适位置
}
//堆排序
void HeapSort(SqList &L)
{
    RecordType temp;

    for (int i = L.length / 2; i > 0; i--)
        HeapAdjust(L, i, L.length); //将初始数据调整为大顶堆
    for (int i = L.length; i > 1; i--)
    {
        temp = L.r[1];
        L.r[1] = L.r[i];
        L.r[i] = temp;           //交换堆顶和当前位置数据
        HeapAdjust(L, 1, i - 1); //继续调整堆为大顶堆
    }

    cout << "堆排序结果：" << endl;
    for (int i = 1; i <= L.length; i++)
        cout << L.r[i].key << '\t';
    cout << endl;
}

int main()
{
    SqList a;

    cout << "输入元素个数：";
    cin >> a.length;
    for (int i = 1; i <= a.length; i++)
        cin >> a.r[i].key;
    HeapSort(a);
}