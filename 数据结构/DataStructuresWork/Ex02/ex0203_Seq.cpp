#include <iostream>
#define LISTINITSIZE 256
#define LISTINCREMENT 128
using namespace std;

struct SequList
{
    int *pData;
    int nLen, nElem;
} L;
void InitList(SequList &L)
{
    L.pData = new int[LISTINITSIZE];
    if (L.pData == NULL)
    {
        cout << "InitList failed!" << endl;
        return;
    }
    L.nElem = 0;
    L.nLen = LISTINITSIZE;
}
void CreatList(SequList &L,int n)
{
    L.nElem = n;

    for (int i = 0; i < n; i++)
    {
         *(L.pData + i)=i+1;
    }
}
void DeleteElem(SequList &L, int i, int &e)
{
    if (L.pData)
    {
        if (i < 1 || i > L.nElem)
            return;
        e = L.pData[i - 1];
        for (i; i < L.nElem; i++)
        {
            L.pData[i - 1] = L.pData[i];
        }
        L.nElem--;
    }
}

int main()
{
    int n,m;
    int temp=0;
    int e;
    cin>>n>>m;
    InitList(L);
    CreatList(L,n);
    while (L.nElem)
    {
        temp = (temp+m) % L.nElem;
        if (temp == 0) temp=L.nElem;
        DeleteElem(L,temp,e);
        temp--;
        cout<<e<<"\t";
    }
    
}