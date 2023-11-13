#include <iostream>
#include <stdio.h>
#include <conio.h>
#define OK 1
#define OVERFLOW 0
#define ERROR 0
#define MAXSIZE 256
using namespace std;

typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
int CreateBiTree(BiTree &T) //基于前序遍历的创建二叉树
{
    char c;
    c = getche();
    if (c == ' ')
        T = NULL;
    else
    {
        T = new BiTNode;
        if (T == NULL)
            exit(OVERFLOW);
        T->data = c;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return OK;
}
bool IsCompelete(BiTree T)
{
    BiTNode *p, *q[MAXSIZE];
    int front = 0, rear = 0;
    int n1 = 0; //度为1或0的结点标记

    if (T)
    {
        q[rear++] = T;
        while (front != rear)
        {
            p = q[front];
            front = (front + 1) % MAXSIZE;
            if (!p->lchild && !p->rchild) //如果为叶子，n1记为1
                n1 = 1;
            else if (!p->lchild && p->rchild) //如果没有左孩子却有右孩子，返回假
                return false;
            else if (p->lchild && !p->rchild) //如果有左孩子没有右孩子
            {
                if (n1) //如果前面已经有度为1或0的点了，返回假
                    return false;
                else //否则将左孩子入队，并把n1记为1
                {
                    n1 = 1;
                    q[rear] = p->lchild;
                    rear = (rear + 1) % MAXSIZE;
                }
            }
            else //如果两孩子都有的话
            {
                if (n1)
                    return false;
                q[rear] = p->lchild;
                rear = (rear + 1) % MAXSIZE;
                q[rear] = p->rchild;
                rear = (rear + 1) % MAXSIZE;
            }
        }
    }
    return true;
}

int main()
{
    BiTree T;
    cout << "输入二叉树先序序列：";
    CreateBiTree(T);
    if (IsCompelete(T))
        cout << endl
             << "是完全二叉树" << endl;
    else
        cout << endl
             << "不是完全二叉树" << endl;
}
