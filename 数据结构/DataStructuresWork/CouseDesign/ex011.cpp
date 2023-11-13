//11.【1】魔法优惠券    PTA 7-39
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

bool cmp(int a,int b)
{
    return a>b;
}

class quen
{
    int* a;
    int head, tail;
public:
    quen(int n)
    {
        a=new int[n];
        head = 0;
        tail = 0;
    }
    void EnQ(int e)
    {
        a[tail] = e;
        tail++;
    }
    int DeQ()
    {
        head++;
        return a[head-1];
    }
    void Sort()
    {
        //sort(a+head,a+tail,cmp);
    int temp;
        for (int i = head; i < tail - head - 1; i++)
            for (int j = head; j < tail - head - 1 - i; j++)
                if (abs(a[j + 1]) > abs(a[j]))
                {
                    temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                }
    }
    bool Empty()
    {
        if (head==tail)
            return true;
        else
            return false;
    }
};

int main()
{
    int n,m,e,ans=0;

    cin>>n; //输入优惠券
    quen QZ(n),QF(n);
    for (int i = 0; i < n; i++)
    {
        cin>>e;
        if (e>0)
            QZ.EnQ(e);//正的
        else
            QF.EnQ(e);//负的
    }
    cin>>m;//输入商品
    quen SZ(m),SF(m);
    for (int i = 0; i < m; i++)
    {
        cin>>e;
        if (e>0)
            SZ.EnQ(e);
        else
            SF.EnQ(e);
    }
    QF.Sort();QZ.Sort();SZ.Sort();SF.Sort();
    while (!QZ.Empty()&& !SZ.Empty())
    {
        ans+=QZ.DeQ()*SZ.DeQ(); //正正相乘
    }
    while (!QF.Empty()&& !SF.Empty())
    {
        ans+=QF.DeQ()*SF.DeQ(); //负负相乘
    }
    cout<<ans;
}