//8.排序算法速率比较
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <fstream>
#define N 50000 //样例大小，五万个数据
#define RADIX 5 //基数排序中最大基数位数
#define OK 1
#define OVERFLOW 0
#define ERROR 0
using namespace std;

typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode, *QueuePtr;
//队列类
class LinkQueue
{
    QueuePtr front;
    QueuePtr rear;

public:
    //初始化、销毁和清空操作
    int InitQueue()
    {
        front = new LNode;
        if (front == NULL)
            exit(OVERFLOW);
        front->next = NULL;
        rear = front;
        return OK;
    }
    //访问型操作
    bool QueueEmpty()
    {
        if (front)
        {
            if (front == rear)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        return true;
    }
    //加工型操作
    void EnQueue(int e)
    {
        LNode *s;
        if (front)
        {
            s = new LNode;
            if (s == NULL)
                exit(OVERFLOW);
            s->data = e;
            rear->next = s;
            rear = s;
            rear->next = NULL;
        }
    }
    int DeQueue(int &e)
    {
        LNode *p;
        if (front && (front != rear))
        {
            p = front->next;
            e = p->data;
            front->next = p->next;
            if (rear == p)
                rear = front;
            delete p;
            return OK;
        }
        return ERROR;
    }
};

//int S[10][N + 1]; //存储样例用数组
int E[10][N + 1]; //排序用数组
//插入排序
void InsertSort(int a[N + 1])
{
    int j, temp;

    for (int i = 2; i <= N; i++)
    {
        temp = a[i];
        for (j = i; j > 1; j--)
        {
            if (temp < a[j - 1])
                a[j] = a[j - 1];
            else
                break;
        }
        a[j] = temp;
    }
}
//希尔排序
void ShellSort(int a[N + 1])
{
    int d[3] = {5, 3, 1};
    int temp, j;

    for (int k = 0; k < 3; k++)
        for (int i = d[k] + 1; i <= N; i++)
            if (a[i] < a[i - d[k]])
            {
                temp = a[i];
                for (j = i; j > d[k]; j = j - d[k])
                {
                    if (temp < a[j - d[k]])
                        a[j] = a[j - d[k]];
                    else
                        break;
                }
                a[j] = temp;
            }
}
//冒泡排序
void BubbleSort(int a[N + 1])
{
    int temp;

    for (int i = 1; i <= N - 1; i++)
        for (int j = 1; j <= N - i; j++)
            if (a[j + 1] < a[j])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
}
//快速排序
void QuickSort(int k, int head, int tail)
{
    if (head >= tail)
        return; //当头大于等于尾，直接返回

    int randbase = (rand() % (tail - head + 1)) + head;
    int base = E[k][head];
    E[k][head] = E[k][randbase];
    E[k][randbase] = base; //取随机位置做基数

    base = E[k][head]; //设置基数
    int i = head, j = tail;

    if (head >= tail)
        return;   //当头大于等于尾，直接返回
    while (i < j) //否则调整数据
    {
        while (i < j && E[k][j] >= base) //找到右边比基数小的
            j--;
        if (i < j)
            E[k][i] = E[k][j];           //放入左边的坑
        while (i < j && E[k][i] <= base) //找到左边比基数大的
            i++;
        if (i < j)
            E[k][j] = E[k][i]; //放入右边的坑
    }
    E[k][i] = base; //将基数放入中间位置

    QuickSort(k, head, i - 1); //递归排左边
    QuickSort(k, i + 1, tail); //递归排右边
}
//倒序快速排序
void DeQuickSort(int k, int head, int tail)
{
    if (head >= tail)
        return; //当头大于等于尾，直接返回

    int randbase = (rand() % (tail - head + 1)) + head;
    int base = E[k][head];
    E[k][head] = E[k][randbase];
    E[k][randbase] = base; //取随机位置做基数

    base = E[k][head]; //设置基数
    int i = head, j = tail;

    while (i < j) //否则调整数据
    {
        while (i < j && E[k][j] <= base) //找到右边比基数小的
            j--;
        if (i < j)
            E[k][i] = E[k][j];           //放入左边的坑
        while (i < j && E[k][i] >= base) //找到左边比基数大的
            i++;
        if (i < j)
            E[k][j] = E[k][i]; //放入右边的坑
    }
    E[k][i] = base; //将基数放入中间位置

    DeQuickSort(k, head, i - 1); //递归排左边
    DeQuickSort(k, i + 1, tail); //递归排右边
}
//选择排序
void SeleteSort(int a[N + 1])
{
    int min;
    int temp;

    for (int i = 1; i <= N - 1; i++)
    {
        min = i;
        for (int j = i + 1; j <= N; j++)
            if (a[j] < a[min])
                min = j;
        if (min != i)
        {
            temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }
}

//大顶堆调整
void HeapAdjust(int a[N + 1], int low, int high)
{
    int temp = a[low];
    int i = low, j = 2 * i; //j为i的左孩子

    while (j <= high)
    {
        if (j + 1 <= high && a[j + 1] > a[j]) //挑选左右孩子较大者
            j++;
        if (temp >= a[j]) //如果孩子不必根大
            break;
        a[i] = a[j]; //否则继续往下筛选
        i = j;
        j = 2 * i;
    }
    a[i] = temp; //将原根结点放入合适位置
}
//堆排序
void HeapSort(int a[N + 1])
{
    int temp;

    for (int i = N / 2; i > 0; i--)
        HeapAdjust(a, i, N); //将初始数据调整为大顶堆
    for (int i = N; i > 1; i--)
    {
        temp = a[1];
        a[1] = a[i];
        a[i] = temp;             //交换堆顶和当前位置数据
        HeapAdjust(a, 1, i - 1); //继续调整堆为大顶堆
    }
}

//归并两组数据
void Merge(int a[N + 1], int low, int mid, int high)
{
    int *T;
    int i, j, k = 1;

    T = new int[high - low + 1];
    i = low;
    j = mid + 1;

    while (i <= mid && j <= high) //将两组数中较小者依次放入T中
    {
        if (a[i] < a[j])
            T[k++] = a[i++];
        else
            T[k++] = a[j++];
    }
    while (i <= mid)
        T[k++] = a[i++]; //剩余数据存入T数组
    while (j <= high)
        T[k++] = a[j++]; //剩余数据存入T数组
    for (k = 1, i = low; i <= high; k++, i++)
        a[i] = T[k];
}
//归并排序
void MergeSort(int a[N + 1])
{

    for (int len = 1; len <= N; len *= 2)
    {
        int i = 1;
        while (i + 2 * len <= N)
        {
            Merge(a, i, i + len - 1, i + 2 * len - 1); //归并两组长度为len的数据
            i = i + 2 * len;                           //跳到下一组
        }
        if (i + len <= N)
            Merge(a, i, i + len - 1, N); //归并剩下长度不足2个len的数据
    }
}
//基数排序
void RadixSort(int a[N + 1])
{
    LinkQueue Q[10]; //辅助队列
    int radix = 1;   //起始基数
    int m;           //存某位上的数字

    for (int i = 0; i < 10; i++)
        Q[i].InitQueue();
    for (int k = 1; k < RADIX; k++)
    {
        radix *= 10;
        for (int i = 1; i <= N; i++)
        {
            m = (a[i] % radix) / (radix / 10); //取基数位上的数
            Q[m].EnQueue(a[i]);                //将其入队
        }
        for (int i = 1, m = 0; m < 10; m++) //将所有数出队，完成一次排序
        {
            while (!Q[m].QueueEmpty())
            {
                Q[m].DeQueue(a[i]);
                ++i;
            }
        }
    }
}
//测试类
class SortTest
{
public:
    //创建样例
    void CreatSample()
    {
        ofstream fout("sample.txt");
        int temp;

        for (int i = 0; i < 10; i++)
            for (int j = 1; j <= N; j++)
                E[i][j] = rand(); //生成随机数组

        QuickSort(0, 1, N);   //第一组调正序
        DeQuickSort(1, 1, N); //第二组调倒序

        for (int i = 0; i < 10; i++) //写入文件
        {
            for (int j = 1; j <= N; j++)
            {
                fout << E[i][j] << ' ';
                if (j % 100 == 0)
                    fout << endl;
            }
            fout << endl;
        }
        fout.close();
    }
    //测试函数
    void Test(void (*Sort)(int a[N + 1]))
    {
        ifstream fin("sample.txt");
        int start_time;

        for (int i = 0; i < 10; i++)
            for (int j = 1; j <= N; j++)
                fin >> E[i][j]; //每次从样例文件中获取数据到E数组

        start_time = clock(); //计时开始
        for (int i = 0; i < 10; i++)
            Sort(E[i]);                                             //排序十组数据
        cout << "用时：\t" << clock() - start_time << "ms" << endl; //计时结束，输出时间
    }
    void Test(void (*Sort)(int k, int head, int tail)) //Test函数的重载，快排用
    {
        ifstream fin("sample.txt");
        int start_time;

        for (int i = 0; i < 10; i++)
            for (int j = 1; j <= N; j++)
                fin >> E[i][j];

        start_time = clock();
        for (int i = 0; i < 10; i++)
            Sort(i, 1, N);
        cout << "用时：\t" << clock() - start_time << "ms" << endl;

        /* ofstream fout("out.txt"); //排序输出测试

        for (int i = 0; i < 10; i++)
        {    for (int j = 1; j <= N; j++)
            {
                fout<<E[i][j]<<' ';
                if (j%100==0) fout<<endl;
            }
            fout<<endl;
        }
        fout.close();*/
    }
};

int main()
{
    SortTest T;

    T.CreatSample();
    cout << "插入排序";
    T.Test(InsertSort);
    cout << "希尔排序";
    T.Test(ShellSort);
    cout << "冒泡排序";
    T.Test(BubbleSort);
    cout << "快速排序";
    T.Test(QuickSort);
    cout << "选择排序";
    T.Test(SeleteSort);
    cout << "  堆排序";
    T.Test(HeapSort);
    cout << "归并排序";
    T.Test(MergeSort);
    cout << "基数排序";
    T.Test(RadixSort);
}
