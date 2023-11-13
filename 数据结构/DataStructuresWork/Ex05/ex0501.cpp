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

//初始化、销毁和情况操作
BiTree DestroyBiTree(BiTree &T) //基于后序遍历的摧毁二叉树
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
//访问型操作
bool BiTreeEmpty(BiTNode *T) //判断空树
{
    if (T == NULL)
    {
        return true;
    }
    return false;
}
int BiTreeDepth(BiTree T) //获取树的深度
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
char Root(BiTNode *T) //返回根结点数据
{
    if (T)
        return T->data;
    cout << "错误" << endl;
}
BiTNode *FindNode(BiTree T, char x) //查找数据为x的结点地址
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
int Value(BiTNode *T, BiTNode *cur_p, char &e) //获取当前结点的值
{
    if (T)
    {
        e = cur_p->data;
        return OK;
    }
    else
        return ERROR;
}
int Parent(BiTNode *T, BiTNode *cur_p, BiTree &parent) //获取当前结点的双亲结点
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
int LeftChild(BiTNode *T, BiTNode *cur_p, BiTree &leftChild) //返回左孩子指针
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
int RightChild(BiTNode *T, BiTNode *cur_p, BiTree &rightChild) //返回右孩子指针
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
int LeftBrother(BiTNode *T, BiTNode *cur_p, BiTree &leftbrother) //返回左兄弟指针
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
int RightBrother(BiTNode *T, BiTNode *cur_p, BiTree &rightbrother) //返回右兄弟指针
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
void PreOrderTraverse(BiTNode *T) //先序遍历
{
    if (T)
    {
        cout << T->data << '\t';
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}
void InOrderTraverse(BiTNode *T) //中序遍历
{
    if (T)
    {
        InOrderTraverse(T->lchild);
        cout << T->data << '\t';
        InOrderTraverse(T->rchild);
    }
}
void PostOrderTraverse(BiTNode *T) //后序遍历
{
    if (T)
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout << T->data << '\t';
    }
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
//加工型操作
int Assign(BiTree &T, BiTNode *cur_p, char value) //将T中p的数据更改
{
    if (T)
    {
        cur_p->data = value;
        return OK;
    }
    return ERROR;
}
int InsertChild(BiTree &T, BiTNode *cur_p, int LR, BiTNode *c) //将树c插入到p之后
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
int Delete(BiTree &T, BiTNode *cur_p, int LR) //删除p的左/右孩子
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

int menu_sel() //测试菜单
{
    char *m[20] = {(char *)"1.创建二叉树",
                   (char *)"2.删除二叉树",
                   (char *)"3.判断二叉树为空",
                   (char *)"4.获取二叉树深度",
                   (char *)"5.获取二叉树根结点数据",
                   (char *)"6.获取某节点的数据",
                   (char *)"7.获取某结点双亲的数据",
                   (char *)"8.获取某结点左孩子的数据",
                   (char *)"9.获取某结点右孩子的数据",
                   (char *)"10.获取某结点左兄弟的数据",
                   (char *)"11.获取某结点右兄弟的数据",
                   (char *)"12.先序遍历",
                   (char *)"13.中序遍历",
                   (char *)"14.后序遍历",
                   (char *)"15.层序遍历",
                   (char *)"16.更改T中某结点数据",
                   (char *)"17.将新树c插入某结点之后",
                   (char *)"18.删除某结点的孩子",
                   (char *)"0.退出"};
    int i, choice;
    do
    {
        system("cls");
        cout << "-------主菜单-------" << endl;
        for (i = 0; i < 19; i++)
            cout << m[i] << endl;
        cout << "请输入选择：";
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
            cout << "输入二叉树的先序序列：";
            if (CreateBiTree(T))
                cout <<endl<< "创建成功" << endl;
            else
                cout << endl<< "创建失败" << endl;
            system("pause");
            break;
        case 2:
            T = DestroyBiTree(T);
            cout << "已删除" << endl;
            system("pause");
            break;
        case 3:
            if (BiTreeEmpty(T))
                cout << "空树" << endl;
            else
                cout << "非空树" << endl;
            system("pause");
            break;
        case 4:
            cout << "树的深度为：" << BiTreeDepth(T) << endl;
            system("pause");
            break;
        case 5:
            cout << "根结点数据为：" << Root(T) << endl;
            system("pause");
            break;
        case 6:
            cout << "输入某结点数据：";
            cin >> temp;
            e = ' ';
            Value(T, FindNode(T, temp), e);
            cout << "该节点数据为：" << e << endl;
            system("pause");
            break;
        case 7:
            cout << "输入某结点数据：";
            cin >> temp;
            p = NULL;
            if (Parent(T, FindNode(T, temp), p))
                cout << "该结点双亲数据是：" << p->data << endl;
            else
                cout << "错误,找不到双亲" << endl;
            system("pause");
            break;
        case 8:
            cout << "输入某结点数据：";
            cin >> temp;
            p = NULL;
            if (LeftChild(T, FindNode(T, temp), p))
                cout << "该结点左孩子数据是：" << p->data << endl;
            else
                cout << "错误" << endl;
            system("pause");
            break;
        case 9:
            cout << "输入某结点数据：";
            cin >> temp;
            p = NULL;
            if (RightChild(T, FindNode(T, temp), p))
                cout << "该结点右孩子数据是：" << p->data << endl;
            else
                cout << "错误" << endl;
            system("pause");
            break;
        case 10:
            cout << "输入某结点数据：";
            cin >> temp;
            p = NULL;
            if (LeftBrother(T, FindNode(T, temp), p))
                cout << "该结点左兄弟数据是：" << p->data << endl;
            else
                cout << "错误" << endl;
            system("pause");
            break;
        case 11:
            cout << "输入某结点数据：";
            cin >> temp;
            p = NULL;
            if (RightBrother(T, FindNode(T, temp), p))
                cout << "该结点右兄弟数据是：" << p->data << endl;
            else
                cout << "错误" << endl;
            system("pause");
            break;
        case 12:
            cout << "先序遍历为：";
            PreOrderTraverse(T);
            system("pause");
            break;
        case 13:
            cout << "中序遍历为：";
            InOrderTraverse(T);
            system("pause");
            break;
        case 14:
            cout << "后序遍历为：";
            PostOrderTraverse(T);
            system("pause");
            break;
        case 15:
            cout << "层序遍历为：";
            LevelOrderTraverse(T);
            system("pause");
            break;
        case 16:
            cout << "你要更改的数据：";
            cin >> temp;
            if (FindNode(T, temp))
            {
                cout << "你想改成：";
                cin >> e;
                if (Assign(T, FindNode(T, temp), e))
                    cout << "修改成功" << endl;
                else
                    cout << "修改失败" << endl;
            }
            else
                cout << "找不到结点" << endl;
            system("pause");
            break;
        case 17:
            cout << "创建一棵新树(根结点无右孩子)" << endl;
            CreateBiTree(newT);
            cout <<endl<< "插入T的结点为：";
            cin >> temp;
            cout << "插入为左孩子还是右孩子(0为左1为右):";
            cin >> lr;
            if (InsertChild(T, FindNode(T, temp), lr, newT))
                cout << "插入成功" << endl;
            else
                cout << "插入失败" << endl;
            system("pause");
            break;
        case 18:
            cout << "你要删除哪个结点的孩子：" << endl;
            cin >> temp;
            if (p = FindNode(T, temp))
            {
                cout << "要删除左还是右(0为左1为右)：" << endl;
                cin >> lr;
                if (lr == 0 || lr == 1)
                {
                    Delete(T, p, lr);
                    cout << "删除成功" << endl;
                }
                else
                    cout << "输入错误" << endl;
            }
            else
                cout << "找不到结点" << endl;
            system("pause");
            break;
        case 0:
            break;
        }
        if (sel == 0)
            break;
    }
}
