#include <iostream>
using namespace std;

void QuickSort(int a[], int head, int tail)
{
    int base = a[head]; //���û���Ϊͷһ��
    int temp;
    int i = head, j = tail;

    if (head >= tail)
        return;   //��ͷ���ڵ���β��ֱ�ӷ���
    while (i < j) //�����������
    {
        while (i < j && a[j] >= base) //�ҵ��ұ߱Ȼ���С��
            j--;
        if (i < j)
            a[i++] = a[j];            //������ߵĿ�
        while (i < j && a[i] <= base) //�ҵ���߱Ȼ������
            i++;
        if (i < j)
            a[j--] = a[i]; //�����ұߵĿ�
    }
    a[i] = base; //�����������м�λ��

    QuickSort(a, head, i - 1); //�ݹ������
    QuickSort(a, i + 1, tail); //�ݹ����ұ�
}

int main()
{
    int a[100];
    int n;
    cout << "����Ԫ�ظ�����";
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    QuickSort(a, 1, n);
    cout << "������������" << endl;
    for (int i = 1; i <= n; i++)
        cout << a[i] << '\t';
    cout << endl;
}
/*8
85 24 63 45 17 31 96 50*/