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

BiTree DestroyBiTree(BiTree &T) //���ں�������Ĵݻٶ�����
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
void LevelOrderTraverse(BiTNode *T) //�������
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
            p = qu[front];                 //ͷ������
            front = (front + 1) % MAXSIZE; //����������
            cout << p->data << '\t';
            if (p->lchild)
            {
                qu[rear] = p->lchild; //���ӽ����������
                rear = (rear + 1) % MAXSIZE;
            }
            if (p->rchild)
            {
                qu[rear] = p->rchild; //���ӽ����Һ������
                rear = (rear + 1) % MAXSIZE;
            }
        }
        cout << endl;
    }
    else
        cout << "������������" << endl;
}
void SearchToDelete(BiTree &T, char x) //�����������ɾ��
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
            p = qu[front];                 //ͷ������
            front = (front + 1) % MAXSIZE; //����������
            if (p->lchild)
            {
                if (p->lchild->data == x)
                {
                    DestroyBiTree(p->lchild);
                    p->lchild = NULL;
                }
                else
                {
                    qu[rear] = p->lchild; //���ӽ����������
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
                qu[rear] = p->rchild; //���ӽ����Һ������
                rear = (rear + 1) % MAXSIZE;
                }
            }
        }
    }
    else
        cout << "������������" << endl;
}
int main()
{
    BiTree T, p, temp;
    char x;

    cout << "���������ǰ�����У�";
    CreateBiTree(T);
    cout << endl
         << "�����Ĳ������Ϊ��";
    LevelOrderTraverse(T);
    cout << "��Ҫɾ���Ľ��Ԫ��ֵΪ��";
    cin >> x;
    SearchToDelete(T, x);
    cout << "ɾ����Ĳ������Ϊ��";
    LevelOrderTraverse(T);
}
