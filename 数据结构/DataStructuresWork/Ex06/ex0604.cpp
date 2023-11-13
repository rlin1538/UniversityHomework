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
    char data;                //元素值
    int layoutnum;            //层号
    BCTNode *brother, *child; //兄弟指针、孩子指针
} BCTNode, *BCTree;

int CreateBCTree(BCTree &T, int l) //创建兄弟-孩子树，类似于先序遍历的方法
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
BCTree DestroyBiTree(BCTree &T) //摧毁树，类似与后序遍历的方法
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

void TraverseLayout(BCTNode *T, int i) //遍历第i层元素
{
    if (T)
    {
        if (T->layoutnum == i) //层号为i时输出
            cout << T->data << '\t';
        TraverseLayout(T->child, i); //采用类先序遍历的方法
        TraverseLayout(T->brother, i);
    }
}

int main()
{
    BCTree T;
    int i; //第i层

    cout << "输入兄弟-孩子树的先兄后子序列：";
    CreateBCTree(T, 1);
    cout << endl
         << "你想输出第几层：";
    cin >> i;
    TraverseLayout(T, i);
}
/*
    测试数据一:A BC EF   D G  
        A
       / \
      B   C
     /   / \
    D   E   F
     \
      G
    测试数据二:A BCD H JKL    FG   E I  
           A
          /|\
         B C D
        / / \ \
       E F   G H
        \     /|\
         I   J K L
*/