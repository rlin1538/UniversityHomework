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

void LevelOrder(BiTNode *T) //层序遍历查找宽度
{
    BiTNode *p;
    BiTNode *qu[MAXSIZE];
    int l[MAXSIZE] = {0}; //队列中每个结点的层号
    int temp;             //临时变量
    int wide;             //宽度
    int count = 0;        //计数结点数
    int front = 0, rear = 0;
    if (T)
    {
        qu[0] = T;
        l[0] = 1; //第一个元素为第一层
        count++;
        rear++;
        while (front != rear)
        {
            p = qu[front];                 //头结点出队
            temp = l[front];               //记录出队结点的层号
            front = (front + 1) % MAXSIZE; //避免队列溢出
            //cout << p->data << '\t';
            if (p->lchild)
            {
                qu[rear] = p->lchild; //出队结点的左孩子入队
                count++;
                l[rear] = temp + 1; //子节点的层号为父节点+1
                rear = (rear + 1) % MAXSIZE;
            }
            if (p->rchild)
            {
                qu[rear] = p->rchild; //出队结点的右孩子入队
                count++;
                l[rear] = temp + 1; //子节点的层号为父节点+1
                rear = (rear + 1) % MAXSIZE;
            }
        }
    }
    else
    {
        cout << "二叉树不存在" << endl;
        return;
    }
    wide = 1; //求宽度
    temp = 1;
    for (int i = 1; i < count; i++)
    {
        if (l[i] != l[i - 1])
        {
            if (temp > wide)
                wide = temp;
            temp = 1;
        }
        else
            temp++;
    }
    if (temp > wide)
        wide = temp;
    cout << endl
         << count << "个结点" << endl
         << "宽度为：" << wide << endl;
}

int main()
{
    BiTree T;

    cout << "输入二叉树前序序列：";
    CreateBiTree(T);
    LevelOrder(T);
}