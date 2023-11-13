#include <iostream>
using namespace std;

int main()
{
    int n;                 //ƻ��������
    int m;                 //������
    long tree[2000] = {0}; //ƻ�����ϵ�ƻ����
    int fall[2000] = {0};  //ƻ�����������
    int temp;
    long ansT = 0;
    int ansD = 0, ansE = 0; //������

    cin >> n;
    for (int i = 0; i < n; i++) //�������ƻ����
    {
        cin >> m;                   //���������
        cin >> tree[i];             //�����һ�μ���ƻ����
        for (int j = 1; j < m; j++) //ѭ��������μ�����
        {
            cin >> temp;   //��¼���μ�����
            if (temp <= 0) //���
            {
                tree[i] += temp;
            }
            else
            {
                if (temp < tree[i]) //�ж��Ƿ���ƻ������
                {
                    fall[i] = 1;
                    tree[i] = temp;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        ansT += tree[i]; //����ƻ������
        if (fall[i])
            ansD++; //�������ƻ��������
        if (i == 0) //���������������ĵ������
        {
            if (fall[n - 1] && fall[i] && fall[i + 1])
                ansE++;
        }
        else
        {
            if (i == n - 1)
            {
                if (fall[i - 1] && fall[i] && fall[0])
                    ansE++;
            }
            else
            {
                if (fall[i - 1] && fall[i] && fall[i + 1])
                    ansE++;
            }
        }
    }
    cout << ansT << ' ' << ansD << ' ' << ansE;
}