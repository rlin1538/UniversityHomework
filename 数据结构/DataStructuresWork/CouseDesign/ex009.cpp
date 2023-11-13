//9.¡¾1¡¿Êý×ÖÅÅÐò   CSP 201503-2
#include <iostream>
#define N 1001
using namespace std;

struct Data
{
    int value;
    int count;
};
//Ã°ÅÝ
void BubbleSort(Data a[N])
{
    Data temp;

    for (int i = 0; i < N-1; i++)
        for (int j = 0; j < N-1 - i; j++)
            if (a[j + 1].count > a[j].count)
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
}

int main()
{
    Data a[N];
    int n,temp;

    for (int i = 0; i < N; i++)
    {
        a[i].value=i;
        a[i].count=0;
    }
    cin>>n;
    for (int i = 0; i < n; i++)
    {
        cin>>temp;
        a[temp].count++;
    }
    BubbleSort(a);
    for (int i = 0; i < N; i++)
        if (a[i].count>0)
            cout<<a[i].value<<' '<<a[i].count<<endl;
}