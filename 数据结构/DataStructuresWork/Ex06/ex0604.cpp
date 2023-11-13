#include <iostream>
#include <stdio.h>
#include <conio.h>
#define OK 1
#define OVERFLOW 0
#define ERROR 0
#define MAXSIZE 256
using namespace std;

typedef struct BCTNode
{
    char data;                //Ԫ��ֵ
    int layoutnum;            //���
    BCTNode *brother, *child; //�ֵ�ָ�롢����ָ��
} BCTNode, *BCTree;

int CreateBCTree(BCTree &T, int l) //�����ֵ�-����������������������ķ���
{
    char c;
    c = getche();
    if (c == ' ')
        T = NULL;
    else
    {
        T = new BCTNode;
        if (T == NULL)
            exit(OVERFLOW);
        T->data = c;
        T->layoutnum = l;
        CreateBCTree(T->brother, l);
        CreateBCTree(T->child, l + 1);
    }
    return OK;
}
BCTree DestroyBiTree(BCTree &T) //�ݻ������������������ķ���
{
    if (T)
    {
        T->brother = DestroyBiTree(T->brother);
        T->child = DestroyBiTree(T->child);
        delete[] T;
        T = NULL;
        return NULL;
    }
    else
        return NULL;
}

void TraverseLayout(BCTNode *T, int i) //������i��Ԫ��
{
    if (T)
    {
        if (T->layoutnum == i) //���Ϊiʱ���
            cout << T->data << '\t';
        TraverseLayout(T->child, i); //��������������ķ���
        TraverseLayout(T->brother, i);
    }
}

int main()
{
    BCTree T;
    int i; //��i��

    cout << "�����ֵ�-�����������ֺ������У�";
    CreateBCTree(T, 1);
    cout << endl
         << "��������ڼ��㣺";
    cin >> i;
    TraverseLayout(T, i);
}
/*
    ��������һ:A BC EF   D G  
        A
       / \
      B   C
     /   / \
    D   E   F
     \
      G
    �������ݶ�:A BCD H JKL    FG   E I  
           A
          /|\
         B C D
        / / \ \
       E F   G H
        \     /|\
         I   J K L
*/