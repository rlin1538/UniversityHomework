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

void LevelOrder(BiTNode *T) //����������ҿ��
{
    BiTNode *p;
    BiTNode *qu[MAXSIZE];
    int l[MAXSIZE] = {0}; //������ÿ�����Ĳ��
    int temp;             //��ʱ����
    int wide;             //���
    int count = 0;        //���������
    int front = 0, rear = 0;
    if (T)
    {
        qu[0] = T;
        l[0] = 1; //��һ��Ԫ��Ϊ��һ��
        count++;
        rear++;
        while (front != rear)
        {
            p = qu[front];                 //ͷ������
            temp = l[front];               //��¼���ӽ��Ĳ��
            front = (front + 1) % MAXSIZE; //����������
            //cout << p->data << '\t';
            if (p->lchild)
            {
                qu[rear] = p->lchild; //���ӽ����������
                count++;
                l[rear] = temp + 1; //�ӽڵ�Ĳ��Ϊ���ڵ�+1
                rear = (rear + 1) % MAXSIZE;
            }
            if (p->rchild)
            {
                qu[rear] = p->rchild; //���ӽ����Һ������
                count++;
                l[rear] = temp + 1; //�ӽڵ�Ĳ��Ϊ���ڵ�+1
                rear = (rear + 1) % MAXSIZE;
            }
        }
    }
    else
    {
        cout << "������������" << endl;
        return;
    }
    wide = 1; //����
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
         << count << "�����" << endl
         << "���Ϊ��" << wide << endl;
}

int main()
{
    BiTree T;

    cout << "���������ǰ�����У�";
    CreateBiTree(T);
    LevelOrder(T);
}