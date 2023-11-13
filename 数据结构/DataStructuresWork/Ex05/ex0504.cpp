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
int CreateBiTree(BiTree &T) //����ǰ������Ĵ���������
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
    int n1 = 0; //��Ϊ1��0�Ľ����

    if (T)
    {
        q[rear++] = T;
        while (front != rear)
        {
            p = q[front];
            front = (front + 1) % MAXSIZE;
            if (!p->lchild && !p->rchild) //���ΪҶ�ӣ�n1��Ϊ1
                n1 = 1;
            else if (!p->lchild && p->rchild) //���û������ȴ���Һ��ӣ����ؼ�
                return false;
            else if (p->lchild && !p->rchild) //���������û���Һ���
            {
                if (n1) //���ǰ���Ѿ��ж�Ϊ1��0�ĵ��ˣ����ؼ�
                    return false;
                else //����������ӣ�����n1��Ϊ1
                {
                    n1 = 1;
                    q[rear] = p->lchild;
                    rear = (rear + 1) % MAXSIZE;
                }
            }
            else //��������Ӷ��еĻ�
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
    cout << "����������������У�";
    CreateBiTree(T);
    if (IsCompelete(T))
        cout << endl
             << "����ȫ������" << endl;
    else
        cout << endl
             << "������ȫ������" << endl;
}
