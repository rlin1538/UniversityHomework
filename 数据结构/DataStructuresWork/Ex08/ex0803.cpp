#include <iostream>
using namespace std;

void QuickSort(int a[], int head, int tail)
{
    int base = a[head]; //设置基数为头一个
    int temp;
    int i = head, j = tail;

    if (head >= tail)
        return;   //当头大于等于尾，直接返回
    while (i < j) //否则调整数据
    {
        while (i < j && a[j] >= base) //找到右边比基数小的
            j--;
        if (i < j)
            a[i++] = a[j];            //放入左边的坑
        while (i < j && a[i] <= base) //找到左边比基数大的
            i++;
        if (i < j)
            a[j--] = a[i]; //放入右边的坑
    }
    a[i] = base; //将基数放入中间位置

    QuickSort(a, head, i - 1); //递归排左边
    QuickSort(a, i + 1, tail); //递归排右边
}

int main()
{
    int a[100];
    int n;
    cout << "输入元素个数：";
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    QuickSort(a, 1, n);
    cout << "快速排序结果：" << endl;
    for (int i = 1; i <= n; i++)
        cout << a[i] << '\t';
    cout << endl;
}
/*8
85 24 63 45 17 31 96 50*/