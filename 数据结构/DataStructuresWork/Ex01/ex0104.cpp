#include <iostream>
using namespace std;

long r,y,g;
long light[4];
long transfor(long l,long sec,long cur_sec)
{
    long temp=cur_sec;
    temp = cur_sec % (r+y+g);
    
    if (temp>sec)
    {
        temp-=sec;
        l++;
        if (l>3) l=1;
        while (temp>light[l])
        {
                temp-=light[l];//cout<<temp<<"-"<<light[l]<<endl;
                l++;
                if (l>3) l=1;
        }
        sec = light[l]-temp;
    }
    else
    {
        sec = sec-temp;
    }

    if (l == 1)
        return sec;
    if (l == 2)
        return 0;
    if (l==3)
        return sec+light[1];
}


int main()
{
    long n;          //道路和红绿灯数
    long long k,t;        //k红绿灯状态，t当前状态剩余时间
    long long time=0;

    cin>>r>>y>>g;
    light[1]=r;light[2]=g;light[3]=y;
    cin>>n;
    for (long i=0;i<n;i++)
    {
        cin>>k>>t;
        if (k == 0)
        {
            time+=t;
        }
        else
        {
            if (k == 2) k= 3;
            else if (k == 3) k= 2;
            time+=transfor(k,t,time);
        }
    }
    cout<<time<<endl;
}