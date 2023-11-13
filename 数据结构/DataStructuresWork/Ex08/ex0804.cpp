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
//�󶥶ѵ���
void HeapAdjust(SqList &L, int low, int high)
{
    RecordType temp = L.r[low];
    int i = low, j = 2 * i; //jΪi������

    while (j <= high)
    {
        if (j + 1 <= high && L.r[j + 1].key > L.r[j].key) //��ѡ���Һ��ӽϴ���
            j++;
        if (temp.key >= L.r[j].key) //������Ӳ��ظ���
            break;
        L.r[i] = L.r[j]; //�����������ɸѡ
        i = j;
        j = 2 * i;
    }
    L.r[i] = temp; //��ԭ�����������λ��
}
//������
void HeapSort(SqList &L)
{
    RecordType temp;

    for (int i = L.length / 2; i > 0; i--)
        HeapAdjust(L, i, L.length); //����ʼ���ݵ���Ϊ�󶥶�
    for (int i = L.length; i > 1; i--)
    {
        temp = L.r[1];
        L.r[1] = L.r[i];
        L.r[i] = temp;           //�����Ѷ��͵�ǰλ������
        HeapAdjust(L, 1, i - 1); //����������Ϊ�󶥶�
    }

    cout << "����������" << endl;
    for (int i = 1; i <= L.length; i++)
        cout << L.r[i].key << '\t';
    cout << endl;
}

int main()
{
    SqList a;

    cout << "����Ԫ�ظ�����";
    cin >> a.length;
    for (int i = 1; i <= a.length; i++)
        cin >> a.r[i].key;
    HeapSort(a);
}