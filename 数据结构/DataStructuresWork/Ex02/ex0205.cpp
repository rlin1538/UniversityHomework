#include <iostream>
using namespace std;

int main()
{
    int n;      //装车次数
    int t[1000000];     //装车时间数组
    int s,e;       //单次装车时段
    int sum=0;        //聊天时间

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