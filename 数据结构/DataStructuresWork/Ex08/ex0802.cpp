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
//��������
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
    cout << "������������" << endl;
    for (int i = 1; i <= n; i++)
        cout << a.r[i].key << '\t';
    cout << endl;
}
//ѡ������
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
    cout << "ѡ����������" << endl;
    for (int i = 1; i <= n; i++)
        cout << a.r[i].key << '\t';
    cout << endl;
}

//�鲢��������
void Merge(SqList &L, int low, int mid, int high)
{
    RecordType *T;
    int i, j, k = 1;
    T = new RecordType[high - low + 1];
    i = low;
    j = mid + 1;

    while (i <= mid && j <= high) //���������н�С�����η���T��
    {
        if (L.r[i].key < L.r[j].key)
            T[k++] = L.r[i++];
        else
            T[k++] = L.r[j++];
    }
    while (i <= mid)
        T[k++] = L.r[i++]; //ʣ�����ݴ���T����
    while (j <= high)
        T[k++] = L.r[j++]; //ʣ�����ݴ���T����
    for (k = 1, i = low; i <= high; k++, i++)
        L.r[i] = T[k];
}
//�鲢�ĵ���
void MSort(SqList &L, int len)
{
    int i = 1;
    while (i + 2 * len <= L.length)
    {
        Merge(L, i, i + len - 1, i + 2 * len - 1); //�鲢���鳤��Ϊlen������
        i = i + 2 * len;                           //������һ��
    }
    if (i + len <= L.length)
        Merge(L, i, i + len - 1, L.length); //�鲢ʣ�³��Ȳ���2��len������
}
//�鲢����
void MergeSort(SqList &L)
{
    for (int len = 1; len <= L.length; len *= 2)
        MSort(L, len); //���ζԸ������ȵ�������鲢
    cout << "�鲢��������" << endl;
    for (int i = 1; i <= L.length; i++)
        cout << L.r[i].key << '\t';
    cout << endl;
}
int main()
{
    SqList a, b, c, d;

    cout << "����Ԫ�ظ�����";
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