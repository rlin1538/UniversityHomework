#include <iostream>
using namespace std;

int main()
{
    int n;      //װ������
    int t[1000000];     //װ��ʱ������
    int s,e;       //����װ��ʱ��
    int sum=0;        //����ʱ��

    for (int i=0;i<1000000;i++)    t[i] = 0;
    cin>>n;
    for (int i=0;i<n;i++)
    {
        cin>>s>>e;
        for (int j=s;j<e;j++)
            t[j] = 1;
    }
    for (int i=0;i<n;i++)
    {
        cin>>s>>e;
        for (int j=s;j<e;j++)
        {
            if (t[j])
            {
                sum++;
            }
        }
    }
    cout<<sum;

    return 0;
}