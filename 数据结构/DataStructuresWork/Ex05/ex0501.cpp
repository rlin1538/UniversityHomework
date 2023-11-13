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

//��ʼ�������ٺ��������
BiTree DestroyBiTree(BiTree &T) //���ں�������Ĵݻٶ�����
{
    if (T)
    {
        T->lchild = DestroyBiTree(T->lchild);
        T->rchild = DestroyBiTree(T->rchild);
        delete[] T;
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
//�����Ͳ���
bool BiTreeEmpty(BiTNode *T) //�жϿ���
{
    if (T == NULL)
    {
        return true;
    }
    return false;
}
int BiTreeDepth(BiTree T) //��ȡ�������
{
    int l, r;
    if (T == NULL)
        return 0;
    else
    {
        l = BiTreeDepth(T->lchild);
        r = BiTreeDepth(T->rchild);
        return (l > r) ? (l + 1) : (r + 1);
    }
}
char Root(BiTNode *T) //���ظ��������
{
    if (T)
        return T->data;
    cout << "����" << endl;
}
BiTNode *FindNode(BiTree T, char x) //��������Ϊx�Ľ���ַ
{
    BiTNode *p = NULL;
    if (T == NULL)
        return NULL;
    else if (T->data == x)
        return T;
    else
    {
        p = FindNode(T->lchild, x);
        if (p == NULL)
            return FindNode(T->rchild, x);
        else
        {
            return p;
        }
    }
}
int Value(BiTNode *T, BiTNode *cur_p, char &e) //��ȡ��ǰ����ֵ
{
    if (T)
    {
        e = cur_p->data;
        return OK;
    }
    else
        return ERROR;
}
int Parent(BiTNode *T, BiTNode *cur_p, BiTree &parent) //��ȡ��ǰ����˫�׽��
{
    BiTNode *p;
    if (T)
    {
        if (T == cur_p)
        {
            parent = NULL;
            return ERROR;
        }
        else
        {
            if (T->lchild)
            {
                if (T->lchild == cur_p)
                {
                    parent = T;
                    return OK;
                }
                Parent(T->lchild, cur_p, parent);
            }
            if (T->rchild)
            {
                if (T->rchild == cur_p)
                {
                    parent = T;
                    return OK;
                }
                Parent(T->rchild, cur_p, parent);
            }
        }
    }
    else
        return ERROR;
}
int LeftChild(BiTNode *T, BiTNode *cur_p, BiTree &leftChild) //��������ָ��
{
    if (T)
    {
        if (cur_p->lchild)
        {
            leftChild = cur_p->lchild;
            return OK;
        }
        else
        {
            leftChild = NULL;
            return ERROR;
        }
    }
    else
    {
        leftChild = NULL;
        return ERROR;
    }
}
int RightChild(BiTNode *T, BiTNode *cur_p, BiTree &rightChild) //�����Һ���ָ��
{
    if (T)
    {
        if (cur_p->rchild)
        {
            rightChild = cur_p->rchild;
            return OK;
        }
        else
        {
            rightChild = NULL;
            return ERROR;
        }
    }
    else
    {
        rightChild = NULL;
        return ERROR;
    }
}
int LeftBrother(BiTNode *T, BiTNode *cur_p, BiTree &leftbrother) //�������ֵ�ָ��
{
    BiTree parent, leftchild;
    if (T)
    {
        Parent(T, cur_p, parent);
        if (LeftChild(T, parent, leftchild))
        {
            leftbrother = leftchild;
            return OK;
        }
        else
        {
            leftchild = NULL;
            return ERROR;
        }
    }
    leftchild = NULL;
    return ERROR;
}
int RightBrother(BiTNode *T, BiTNode *cur_p, BiTree &rightbrother) //�������ֵ�ָ��
{
    BiTree parent, rightchild;
    if (T)
    {
        Parent(T, cur_p, parent);
        if (RightChild(T, parent, rightchild))
        {
            rightbrother = rightchild;
            return OK;
        }
        else
        {
            rightchild = NULL;
            return ERROR;
        }
    }
    rightchild = NULL;
    return ERROR;
}
void PreOrderTraverse(BiTNode *T) //�������
{
    if (T)
    {
        cout << T->data << '\t';
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}
void InOrderTraverse(BiTNode *T) //�������
{
    if (T)
    {
        InOrderTraverse(T->lchild);
        cout << T->data << '\t';
        InOrderTraverse(T->rchild);
    }
}
void PostOrderTraverse(BiTNode *T) //�������
{
    if (T)
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout << T->data << '\t';
    }
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
//�ӹ��Ͳ���
int Assign(BiTree &T, BiTNode *cur_p, char value) //��T��p�����ݸ���
{
    if (T)
    {
        cur_p->data = value;
        return OK;
    }
    return ERROR;
}
int InsertChild(BiTree &T, BiTNode *cur_p, int LR, BiTNode *c) //����c���뵽p֮��
{
    BiTNode *child;
    if (T && (c->rchild == NULL))
    {
        if (LR == 0)
        {
            LeftChild(T, cur_p, child);
            cur_p->lchild = c;
            c->rchild = child;
            return OK;
        }
        else
        {
            if (LR == 1)
            {
                RightChild(T, cur_p, child);
                cur_p->rchild = c;
                c->rchild = child;
                return OK;
            }
        }
    }
    return ERROR;
}
int Delete(BiTree &T, BiTNode *cur_p, int LR) //ɾ��p����/�Һ���
{
    if (T)
    {
        if (LR == 0)
        {
            DestroyBiTree(cur_p->lchild);
            cur_p->lchild = NULL;
            return OK;
        }
        else
        {
            if (LR == 1)
            {
                DestroyBiTree(cur_p->rchild);
                cur_p->rchild = NULL;
                return OK;
            }
        }
    }
    return ERROR;
}

int menu_sel() //���Բ˵�
{
    char *m[20] = {(char *)"1.����������",
                   (char *)"2.ɾ��������",
                   (char *)"3.�ж϶�����Ϊ��",
                   (char *)"4.��ȡ���������",
                   (char *)"5.��ȡ���������������",
                   (char *)"6.��ȡĳ�ڵ������",
                   (char *)"7.��ȡĳ���˫�׵�����",
                   (char *)"8.��ȡĳ������ӵ�����",
                   (char *)"9.��ȡĳ����Һ��ӵ�����",
                   (char *)"10.��ȡĳ������ֵܵ�����",
                   (char *)"11.��ȡĳ������ֵܵ�����",
                   (char *)"12.�������",
                   (char *)"13.�������",
                   (char *)"14.�������",
                   (char *)"15.�������",
                   (char *)"16.����T��ĳ�������",
                   (char *)"17.������c����ĳ���֮��",
                   (char *)"18.ɾ��ĳ���ĺ���",
                   (char *)"0.�˳�"};
    int i, choice;
    do
    {
        system("cls");
        cout << "-------���˵�-------" << endl;
        for (i = 0; i < 19; i++)
            cout << m[i] << endl;
        cout << "������ѡ��";
        cin >> choice;
    } while (choice < 0 || choice > 18);
    return choice;
}

int main()
{
    int sel, lr;
    char temp, e;
    BiTNode *p;
    BiTNode q;
    BiTree T, newT;
    for (;;)
    {
        switch (sel = menu_sel())
        {
        case 1:
            cout << "������������������У�";
            if (CreateBiTree(T))
                cout <<endl<< "�����ɹ�" << endl;
            else
                cout << endl<< "����ʧ��" << endl;
            system("pause");
            break;
        case 2:
            T = DestroyBiTree(T);
            cout << "��ɾ��" << endl;
            system("pause");
            break;
        case 3:
            if (BiTreeEmpty(T))
                cout << "����" << endl;
            else
                cout << "�ǿ���" << endl;
            system("pause");
            break;
        case 4:
            cout << "�������Ϊ��" << BiTreeDepth(T) << endl;
            system("pause");
            break;
        case 5:
            cout << "���������Ϊ��" << Root(T) << endl;
            system("pause");
            break;
        case 6:
            cout << "����ĳ������ݣ�";
            cin >> temp;
            e = ' ';
            Value(T, FindNode(T, temp), e);
            cout << "�ýڵ�����Ϊ��" << e << endl;
            system("pause");
            break;
        case 7:
            cout << "����ĳ������ݣ�";
            cin >> temp;
            p = NULL;
            if (Parent(T, FindNode(T, temp), p))
                cout << "�ý��˫�������ǣ�" << p->data << endl;
            else
                cout << "����,�Ҳ���˫��" << endl;
            system("pause");
            break;
        case 8:
            cout << "����ĳ������ݣ�";
            cin >> temp;
            p = NULL;
            if (LeftChild(T, FindNode(T, temp), p))
                cout << "�ý�����������ǣ�" << p->data << endl;
            else
                cout << "����" << endl;
            system("pause");
            break;
        case 9:
            cout << "����ĳ������ݣ�";
            cin >> temp;
            p = NULL;
            if (RightChild(T, FindNode(T, temp), p))
                cout << "�ý���Һ��������ǣ�" << p->data << endl;
            else
                cout << "����" << endl;
            system("pause");
            break;
        case 10:
            cout << "����ĳ������ݣ�";
            cin >> temp;
            p = NULL;
            if (LeftBrother(T, FindNode(T, temp), p))
                cout << "�ý�����ֵ������ǣ�" << p->data << endl;
            else
                cout << "����" << endl;
            system("pause");
            break;
        case 11:
            cout << "����ĳ������ݣ�";
            cin >> temp;
            p = NULL;
            if (RightBrother(T, FindNode(T, temp), p))
                cout << "�ý�����ֵ������ǣ�" << p->data << endl;
            else
                cout << "����" << endl;
            system("pause");
            break;
        case 12:
            cout << "�������Ϊ��";
            PreOrderTraverse(T);
            system("pause");
            break;
        case 13:
            cout << "�������Ϊ��";
            InOrderTraverse(T);
            system("pause");
            break;
        case 14:
            cout << "�������Ϊ��";
            PostOrderTraverse(T);
            system("pause");
            break;
        case 15:
            cout << "�������Ϊ��";
            LevelOrderTraverse(T);
            system("pause");
            break;
        case 16:
            cout << "��Ҫ���ĵ����ݣ�";
            cin >> temp;
            if (FindNode(T, temp))
            {
                cout << "����ĳɣ�";
                cin >> e;
                if (Assign(T, FindNode(T, temp), e))
                    cout << "�޸ĳɹ�" << endl;
                else
                    cout << "�޸�ʧ��" << endl;
            }
            else
                cout << "�Ҳ������" << endl;
            system("pause");
            break;
        case 17:
            cout << "����һ������(��������Һ���)" << endl;
            CreateBiTree(newT);
            cout <<endl<< "����T�Ľ��Ϊ��";
            cin >> temp;
            cout << "����Ϊ���ӻ����Һ���(0Ϊ��1Ϊ��):";
            cin >> lr;
            if (InsertChild(T, FindNode(T, temp), lr, newT))
                cout << "����ɹ�" << endl;
            else
                cout << "����ʧ��" << endl;
            system("pause");
            break;
        case 18:
            cout << "��Ҫɾ���ĸ����ĺ��ӣ�" << endl;
            cin >> temp;
            if (p = FindNode(T, temp))
            {
                cout << "Ҫɾ��������(0Ϊ��1Ϊ��)��" << endl;
                cin >> lr;
                if (lr == 0 || lr == 1)
                {
                    Delete(T, p, lr);
                    cout << "ɾ���ɹ�" << endl;
                }
                else
                    cout << "�������" << endl;
            }
            else
                cout << "�Ҳ������" << endl;
            system("pause");
            break;
        case 0:
            break;
        }
        if (sel == 0)
            break;
    }
}
