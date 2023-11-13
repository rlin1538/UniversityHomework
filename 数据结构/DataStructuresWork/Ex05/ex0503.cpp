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

BiTree DestroyBiTree(BiTree &T) //基于后序遍历的摧毁二叉树
{
    if (T)
    {
        T->lchild = DestroyBiTree(T->lchild);
        T->rchild = DestroyBiTree(T->rchild);
        delete T;
        T = NULL;
        return NULL;
    }
    else
        return NULL;
}
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
void LevelOrderTraverse(BiTNode *T) //层序遍历
{
    BiTNode *p;
    BiTNode *qu[MAXSIZE];
    int front = 0, rear = 0;
    if (T)
    {
        qu[0] = T;
        rear++;
        while (front != rear)
        {
            p = qu[front];                 //头结点出队
            front = (front + 1) % MAXSIZE; //避免队列溢出
            cout << p->data << '\t';
            if (p->lchild)
            {
                qu[rear] = p->lchild; //出队结点的左孩子入队
                rear = (rear + 1) % MAXSIZE;
            }
            if (p->rchild)
            {
                qu[rear] = p->rchild; //出队结点的右孩子入队
                rear = (rear + 1) % MAXSIZE;
            }
        }
        cout << endl;
    }
    else
        cout << "二叉树不存在" << endl;
}
void SearchToDelete(BiTree &T, char x) //层序遍历搜索删除
{
    BiTNode *p;
    BiTNode *qu[MAXSIZE];
    int front = 0, rear = 0;
    if (T)
    {
        if (T->data == x)
        {
            DestroyBiTree(T);
            T = NULL;
            return;
        }
        qu[0] = T;
        rear++;
        while (front != rear)
        {
            p = qu[front];                 //头结点出队
            front = (front + 1) % MAXSIZE; //避免队列溢出
            if (p->lchild)
            {
                if (p->lchild->data == x)
                {
                    DestroyBiTree(p->lchild);
                    p->lchild = NULL;
                }
                else
                {
                    qu[rear] = p->lchild; //出队结点的左孩子入队
                    rear = (rear + 1) % MAXSIZE;
                }
            }
            if (p->rchild)
            {
                if (p->rchild->data == x)
                {
                    DestroyBiTree(p->rchild);
                    p->rchild = NULL;
                }
                else
                {
                qu[rear] = p->rchild; //出队结点的右孩子入队
                rear = (rear + 1) % MAXSIZE;
                }
            }
        }
    }
    else
        cout << "二叉树不存在" << endl;
}
int main()
{
    BiTree T, p, temp;
    char x;

    cout << "输入二叉树前序序列：";
    CreateBiTree(T);
    cout << endl
         << "该树的层序遍历为：";
    LevelOrderTraverse(T);
    cout << "你要删除的结点元素值为：";
    cin >> x;
    SearchToDelete(T, x);
    cout << "删除后的层序遍历为：";
    LevelOrderTraverse(T);
}
