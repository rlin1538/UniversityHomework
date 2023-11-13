#include <iostream>
#define LISTINITSIZE 256
#define LISTINCREMENT 128
using namespace std;

struct SequList
{
    int *pData;
    int nLen, nElem;
} SequList;

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
void CreatList(SequList &L)
{
}
void DestroyList(SequList &L)
{
    if (L.pData)
    {
        delete[] L.pData;
        pData = NULL;
        L.nLen = 0;
        L.nElem = 0;
    }
}
void ClearList(SequList &L)
{
    if (L.pData)
    {
        L.nElem = 0;
    }
}

bool ListEmpty(SequList L)
{
    if (pData)
    {
        if (nElem == 0)
            return true;
        else
            return false;
    }
}
int ListLength(SequList L)
{
    if (L.pData)
    {
        return L.nElem;
    }
}
void GetElem(SequList L, int i, int &e)
{
    if (L.pData && (1 <= i && i <= ListLength(L)))
    {
        e = L.pData[i - 1];
    }
    cout << "GetElem failed!" << endl;
}
int LocateElem(SequList L, int e)
{
    int i = 0; //计数
    if (L.pData)
    {
        while (i < L.nElem)
        {
            if (L.pData[i] == e)
                return ++i;
            else
                i++;
        }
    }
    else
        return 0;
}
void PriorElem(SequList L, int cur_e, int &pre_e)
{
    if (L.pData)
    {
        for (int i = 1; i < L.nElem; i++)
        {
            if (L.pData[i] == cur_e)
            {
                pre_e = L.pData[i - 1];
                return;
            }
        }
        cout >> "PriorElem failed.";
    }
}
void NextElem(SequList L, int cur_e, int &next_e)
{
    if (L.pData)
    {
        for (int i = 0; i < L.nElem - 1; i++)
        {
            if (L.pData[i] == cur_e)
            {
                next_e = L.pData[i + 1];
                return;
            }
        }
        cout >> "Operation failed.";
    }
}
void ListTraverse(SequList L)
{
    if (pData)
    {
        for (int i = 0; i < nElem; i++)
            cout << *(pData + i) << '\t';
        cout << endl;
    }
}

void SetElem(SequList &L, int i, int &e)
{
    int temp;
    if (L.pData && (1 <= i && i <= ListLength(L)))
    {
        if (L.pData[i] == e)
        {
            temp = L.pData[i];
            L.pData[i] = e;
            e = temp;
        }
    }
}
void InsertElem(SequList L, int i, int e)
{
    int *temp;
    if (L.pData)
    {
        if (i < 1 || i > L.nElem)
            return;
        if (L.nLen >= L.nElem) //表满了扩大空间
        {
            temp = new char[L.nLen + 10];
            for (int i = 0; i < L.nLen; i++)
                *(temp + i) = L.pData[i];
            L.pData = temp;
            L.nLen += LISTINCREMENT;
        }
        for (int j = L.nElem; j >= i; j--)
        {
            L.pData[j] = L.pData[j - 1];
        }
        L.pData[i - 1] = e;
        L.nElem++;
    }
}
void DeleteElem(SequList L, int i, int &e)
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
}