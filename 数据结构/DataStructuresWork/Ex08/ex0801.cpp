#include <iostream>
using namespace std;

struct BSTNode
{
    int key; //关键字
    //InfoType data;    //其它数据域
    BSTNode *left, *right; //左右孩子
};
//搜索key值的结点
BSTNode *BSTSearch(BSTNode *T, int key)
{
    if (T == NULL)
        return NULL;
    else if (T->key == key)
        return T;
    else if (T->key < key)
        return BSTSearch(T->right, key);
    else
        return BSTSearch(T->left, key);
}
//插入值
BSTNode *BSTInsert(BSTNode *T, int key)
{
    if (T == NULL)
    {
        T = new BSTNode;
        T->key = key;
        T->left = T->right = NULL;
        return T;
    }
    if (T->key == key)
    {
        cout << endl
             << key << "已存在" << endl;
        return T;
    }
    if (T->key > key)
        T->left = BSTInsert(T->left, key);
    else
        T->right = BSTInsert(T->right, key);
    return T;
}
//建立二叉排序树
BSTNode *CreatBST(int n)
{
    BSTNode *T = NULL;
    int key;
    for (int i = 1; i <= n; i++)
    {
        cin >> key;
        T = BSTInsert(T, key);
    }
    return T;
}
//删除结点
BSTNode *BSTDelete(BSTNode *T, int key)
{
    BSTNode *p = T, *pa = NULL; //p为待删除点，pa为p的父结点
    BSTNode *f, *q;             //q指向p左支中的最大值，f为q父结点
    //查找待删除点
    while (p)
    {
        if (p->key == key)
            break;
        if (p->key < key)
        {
            pa = p;
            p = p->right;
        }
        else
        {
            pa = p;
            p = p->left;
        }
    }
    if (p == NULL)
    {
        return NULL;
        cout << "查找不成功" << endl;
    }

    //删除p
    //如果p为叶结点
    if (p->left == NULL && p->right == NULL)
    {
        if (pa) //如果p不是根结点
        {
            if (pa->key < key) //判断p是pa的左孩子还是右孩子
                pa->right = NULL;
            else
                pa->right = NULL;
            delete p;
            return T;
        }
        else //如果p是根结点
        {
            delete p;
            return NULL;
        }
    }
    //如果p只有右孩子
    if (p->left == NULL && p->right)
    {
        if (pa)
        {
            if (pa->key < key) //判断p是pa的左孩子还是右孩子
                pa->right = p->right;
            else
                pa->left = p->right;
            delete p;
            return T;
        }
        else //如果p是根结点，那直接将p右孩子升级为根结点
        {
            T = p->right;
            delete p;
            return T;
        }
    }
    //如果p只有左孩子
    if (p->left && p->right == NULL)
    {
        if (pa)
        {
            if (pa->key < key) //判断p是pa的左孩子还是右孩子
                pa->right = p->left;
            else
                pa->left = p->left;
            delete p;
            return T;
        }
        else //如果p是根结点，那直接将p右孩子升级为根结点
        {
            T = p->left;
            delete p;
            return T;
        }
    }
    //如果p有左、右孩子
    else
    {
        //先从左支找最大值
        f = p;
        q = p->left;
        while (q->right)
        {
            f = q;
            q = q->right;
        }
        p->key = q->key;
        if (f->key < q->key)
            f->right = q->left;
        else
            f->left = q->left;
        delete q;
        return T;
    }
}

int menu_sel() //测试菜单
{
    char *m[5] = {(char *)"1.创建二叉排序树",
                  (char *)"2.插入元素",
                  (char *)"3.删除元素",
                  (char *)"4.查找元素",
                  (char *)"0.退出"};
    int i, choice;
    do
    {
        system("cls");
        cout << "-------主菜单-------" << endl;
        for (i = 0; i < 5; i++)
            cout << m[i] << endl;
        cout << "请输入选择：";
        cin >> choice;
    } while (choice < 0 || choice > 4);
    return choice;
}

int main()
{
    BSTNode *T = NULL;
    int n, sel, key;

    for (;;)
    {
        switch (sel = menu_sel())
        {
        case 1:
            cout << "输入元素个数：";
            cin >> n;
            cout << "输入元素：";
            T = CreatBST(n);
            system("pause");
            cout << "创建结束" << endl;
            break;
        case 2:
            cout << "输入要插入的元素：";
            cin >> key;
            T = BSTInsert(T, key);
            cout << "插入结束" << endl;
            system("pause");
            break;
        case 3:
            cout << "输入要删除的元素：";
            cin >> key;
            if (BSTDelete(T, key))
                cout << "删除成功" << endl;
            system("pause");
            break;
        case 4:
            cout << "输入查找元素：";
            cin >> key;
            if (BSTSearch(T, key))
                cout << "查找成功" << endl;
            else
                cout << "查找失败" << endl;
            system("pause");
            break;
        case 0:
            system("pause");
            break;
        }
        if (sel == 0)
            break;
    }
}