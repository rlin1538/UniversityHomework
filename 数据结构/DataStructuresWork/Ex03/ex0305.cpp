#include <iostream>
using namespace std;

int Search(int num[])
{
    int count = 1;
    int min = 10000, i = 1;

    while (!num[i])
        i++;
    i++;

    for (i; i < 10000; i++)
    {
        if (num[i] > 1) //�������������ͬ�����ֵΪ0
        {
            return 0;
        }

        if (num[i])
        {
            if (count < min)
                min = count;
            count = 1;
        }
        else
        {
            count++;
        }
    }
    return min;
}

int main()
{
    int n;                //����
    int temp;             //ĳ���������
    int num[10000] = {0}; //������ֵ����飬����i���ڣ���num[i]++

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        num[temp]++;
    }
    cout << Search(num);
}