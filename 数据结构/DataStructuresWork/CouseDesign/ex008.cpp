//8.�����㷨���ʱȽ�
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <fstream>
#define N 50000 //������С�����������
#define RADIX 5 //����������������λ��
#define OK 1
#define OVERFLOW 0
#define ERROR 0
using namespace std;

typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode, *QueuePtr;
//������
class LinkQueue
{
    QueuePtr front;
    QueuePtr rear;

public:
    //��ʼ�������ٺ���ղ���
    int InitQueue()
    {
        front = new LNode;
        if (front == NULL)
            exit(OVERFLOW);
        front->next = NULL;
        rear = front;
        return OK;
    }
    //�����Ͳ���
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
    //�ӹ��Ͳ���
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

//int S[10][N + 1]; //�洢����������
int E[10][N + 1]; //����������
//��������
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
//ϣ������
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
//ð������
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
//��������
void QuickSort(int k, int head, int tail)
{
    if (head >= tail)
        return; //��ͷ���ڵ���β��ֱ�ӷ���

    int randbase = (rand() % (tail - head + 1)) + head;
    int base = E[k][head];
    E[k][head] = E[k][randbase];
    E[k][randbase] = base; //ȡ���λ��������

    base = E[k][head]; //���û���
    int i = head, j = tail;

    if (head >= tail)
        return;   //��ͷ���ڵ���β��ֱ�ӷ���
    while (i < j) //�����������
    {
        while (i < j && E[k][j] >= base) //�ҵ��ұ߱Ȼ���С��
            j--;
        if (i < j)
            E[k][i] = E[k][j];           //������ߵĿ�
        while (i < j && E[k][i] <= base) //�ҵ���߱Ȼ������
            i++;
        if (i < j)
            E[k][j] = E[k][i]; //�����ұߵĿ�
    }
    E[k][i] = base; //�����������м�λ��

    QuickSort(k, head, i - 1); //�ݹ������
    QuickSort(k, i + 1, tail); //�ݹ����ұ�
}
//�����������
void DeQuickSort(int k, int head, int tail)
{
    if (head >= tail)
        return; //��ͷ���ڵ���β��ֱ�ӷ���

    int randbase = (rand() % (tail - head + 1)) + head;
    int base = E[k][head];
    E[k][head] = E[k][randbase];
    E[k][randbase] = base; //ȡ���λ��������

    base = E[k][head]; //���û���
    int i = head, j = tail;

    while (i < j) //�����������
    {
        while (i < j && E[k][j] <= base) //�ҵ��ұ߱Ȼ���С��
            j--;
        if (i < j)
            E[k][i] = E[k][j];           //������ߵĿ�
        while (i < j && E[k][i] >= base) //�ҵ���߱Ȼ������
            i++;
        if (i < j)
            E[k][j] = E[k][i]; //�����ұߵĿ�
    }
    E[k][i] = base; //�����������м�λ��

    DeQuickSort(k, head, i - 1); //�ݹ������
    DeQuickSort(k, i + 1, tail); //�ݹ����ұ�
}
//ѡ������
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

//�󶥶ѵ���
void HeapAdjust(int a[N + 1], int low, int high)
{
    int temp = a[low];
    int i = low, j = 2 * i; //jΪi������

    while (j <= high)
    {
        if (j + 1 <= high && a[j + 1] > a[j]) //��ѡ���Һ��ӽϴ���
            j++;
        if (temp >= a[j]) //������Ӳ��ظ���
            break;
        a[i] = a[j]; //�����������ɸѡ
        i = j;
        j = 2 * i;
    }
    a[i] = temp; //��ԭ�����������λ��
}
//������
void HeapSort(int a[N + 1])
{
    int temp;

    for (int i = N / 2; i > 0; i--)
        HeapAdjust(a, i, N); //����ʼ���ݵ���Ϊ�󶥶�
    for (int i = N; i > 1; i--)
    {
        temp = a[1];
        a[1] = a[i];
        a[i] = temp;             //�����Ѷ��͵�ǰλ������
        HeapAdjust(a, 1, i - 1); //����������Ϊ�󶥶�
    }
}

//�鲢��������
void Merge(int a[N + 1], int low, int mid, int high)
{
    int *T;
    int i, j, k = 1;

    T = new int[high - low + 1];
    i = low;
    j = mid + 1;

    while (i <= mid && j <= high) //���������н�С�����η���T��
    {
        if (a[i] < a[j])
            T[k++] = a[i++];
        else
            T[k++] = a[j++];
    }
    while (i <= mid)
        T[k++] = a[i++]; //ʣ�����ݴ���T����
    while (j <= high)
        T[k++] = a[j++]; //ʣ�����ݴ���T����
    for (k = 1, i = low; i <= high; k++, i++)
        a[i] = T[k];
}
//�鲢����
void MergeSort(int a[N + 1])
{

    for (int len = 1; len <= N; len *= 2)
    {
        int i = 1;
        while (i + 2 * len <= N)
        {
            Merge(a, i, i + len - 1, i + 2 * len - 1); //�鲢���鳤��Ϊlen������
            i = i + 2 * len;                           //������һ��
        }
        if (i + len <= N)
            Merge(a, i, i + len - 1, N); //�鲢ʣ�³��Ȳ���2��len������
    }
}
//��������
void RadixSort(int a[N + 1])
{
    LinkQueue Q[10]; //��������
    int radix = 1;   //��ʼ����
    int m;           //��ĳλ�ϵ�����

    for (int i = 0; i < 10; i++)
        Q[i].InitQueue();
    for (int k = 1; k < RADIX; k++)
    {
        radix *= 10;
        for (int i = 1; i <= N; i++)
        {
            m = (a[i] % radix) / (radix / 10); //ȡ����λ�ϵ���
            Q[m].EnQueue(a[i]);                //�������
        }
        for (int i = 1, m = 0; m < 10; m++) //�����������ӣ����һ������
        {
            while (!Q[m].QueueEmpty())
            {
                Q[m].DeQueue(a[i]);
                ++i;
            }
        }
    }
}
//������
class SortTest
{
public:
    //��������
    void CreatSample()
    {
        ofstream fout("sample.txt");
        int temp;

        for (int i = 0; i < 10; i++)
            for (int j = 1; j <= N; j++)
                E[i][j] = rand(); //�����������

        QuickSort(0, 1, N);   //��һ�������
        DeQuickSort(1, 1, N); //�ڶ��������

        for (int i = 0; i < 10; i++) //д���ļ�
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
    //���Ժ���
    void Test(void (*Sort)(int a[N + 1]))
    {
        ifstream fin("sample.txt");
        int start_time;

        for (int i = 0; i < 10; i++)
            for (int j = 1; j <= N; j++)
                fin >> E[i][j]; //ÿ�δ������ļ��л�ȡ���ݵ�E����

        start_time = clock(); //��ʱ��ʼ
        for (int i = 0; i < 10; i++)
            Sort(E[i]);                                             //����ʮ������
        cout << "��ʱ��\t" << clock() - start_time << "ms" << endl; //��ʱ���������ʱ��
    }
    void Test(void (*Sort)(int k, int head, int tail)) //Test���������أ�������
    {
        ifstream fin("sample.txt");
        int start_time;

        for (int i = 0; i < 10; i++)
            for (int j = 1; j <= N; j++)
                fin >> E[i][j];

        start_time = clock();
        for (int i = 0; i < 10; i++)
            Sort(i, 1, N);
        cout << "��ʱ��\t" << clock() - start_time << "ms" << endl;

        /* ofstream fout("out.txt"); //�����������

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
    cout << "��������";
    T.Test(InsertSort);
    cout << "ϣ������";
    T.Test(ShellSort);
    cout << "ð������";
    T.Test(BubbleSort);
    cout << "��������";
    T.Test(QuickSort);
    cout << "ѡ������";
    T.Test(SeleteSort);
    cout << "  ������";
    T.Test(HeapSort);
    cout << "�鲢����";
    T.Test(MergeSort);
    cout << "��������";
    T.Test(RadixSort);
}
