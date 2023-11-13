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
        if (num[i] > 1) //如果有两个数相同，则差值为0
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
    int n;                //个数
    int temp;             //某次输入的数
    int num[10000] = {0}; //存放数字的数组，若数i存在，则num[i]++

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        num[temp]++;
    }
    cout << Search(num);
}