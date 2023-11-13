//递归算法已在实验一中实现，这边只含有非递归方法
#include <iostream>
#define STACKINITSIZE 256
#define STACKINCREMENT 128
#define OK 1
#define OVERFLOW 0
#define ERROR 0
using namespace std;

typedef struct BiTNode //二叉链表
{
    char data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct SeqStack //栈结构
{
    BiTree *pBase;
    BiTree *pTop;
    int stacksize; //栈已分配的空间
} SeqStack;
int InitStack(SeqStack &S) //初始化栈
{
    S.pBase = new BiTree[STACKINITSIZE];
    if (S.pBase == NULL)
        exit(OVERFLOW);
    S.pTop = S.pBase;
    S.stacksize = STACKINITSIZE;
    return OK;
}
int DestroyStack(SeqStack &S)
{
    if (S.pBase != NULL)
    {
        delete[] S.pBase;
        S.pBase = NULL;
    }
    S.pTop = NULL;
    S.stacksize = 0;
    return OK;
}
bool StackEmpty(SeqStack S) //栈判空
{
    if (S.pBase)
    {
        if (S.pBase == S.pTop)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return true;
}
int Push(SeqStack &S, BiTNode *e) //入栈
{
    BiTree *temp;
    if (S.pBase)
    {
        if (S.pTop - S.pBase >= S.stacksize) //栈满了动态增加空间
        {
            temp = new BiTree[S.stacksize + STACKINCREMENT];
            if (temp == NULL)
                exit(OVERFLOW);
            for (int j = 0; (S.pBase + j) < S.pTop; j++)
                *(temp + j) = *(S.pBase + j);
            delete[] S.pBase;
            S.pBase = temp;
            S.pTop = S.pBase + S.stacksize;
            S.stacksize += STACKINCREMENT;
        }
        *S.pTop = e;
        S.pTop++;
    }
    return OK;
}
int Pop(SeqStack &S, BiTree &e) //出栈
{
    if (S.pBase && S.pBase != S.pTop)
    {
        e = *(S.pTop - 1);
        S.pTop--;
        return OK;
    }
    return ERROR;
}

int CreateBiTree(BiTree &T) //基于前序遍历的创建二叉树
{
    char c;
    c = cin.get();
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
void PreOrderTraverse(BiTree T)
{
    SeqStack S;
    BiTNode *p;

    p = T;
    InitStack(S);
    while (p || !(StackEmpty(S)))
    {
        if (p)
        {
            Push(S, p);
            cout << p->data << '\t';
            p = p->lchild;
        }
        else
        {
            Pop(S, p);
            p = p->rchild;
        }
    }
    cout << endl;
    DestroyStack(S);
}
void InOrderTraverse(BiTree T)
{
    SeqStack S;
    BiTNode *p;

    p = T;
    InitStack(S);
    while (p || !(StackEmpty(S)))
    {
        if (p)
        {
            Push(S, p);
            p = p->lchild;
        }
        else
        {
            Pop(S, p);
            cout << p->data << '\t';
            p = p->rchild;
        }
    }
    cout << endl;
    DestroyStack(S);
}
void PostOrderTraverse(BiTree T)
{
    SeqStack S, st;
    BiTNode *p;

    p = T;
    InitStack(S);
    InitStack(st);
    while (p || !(StackEmpty(S)))
    {
        if (p)
        {
            Push(S, p);
            Push(st,p);
            p = p->rchild;
        }
        else
        {
            Pop(S, p);
            p = p->lchild;
        }
    }
    while (!(StackEmpty(st)))
    {
        Pop(st,p);
        cout<<p->data<<'\t';
    }
    
    cout << endl;
    DestroyStack(S);
    DestroyStack(st);
}
int main()
{
    BiTree T;
    cout << "输入二叉树的前序序列：";
    CreateBiTree(T);
    cout << "非递归的前序遍历：";
    PreOrderTraverse(T);
    cout << "非递归的中序遍历：";
    InOrderTraverse(T);
    cout << "非递归的后序遍历：";
    PostOrderTraverse(T);
}
