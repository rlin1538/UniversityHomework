//7.B-树的应用
#include <iostream>
#include <fstream>
#include <cmath>
#define MAX_M 3
using namespace std;

typedef struct node
{
    int keynum;           //结点包含关键字个数
    int key[MAX_M + 1];   //结点关键字数组，MAX_M号单元放空
    node *parent;         //父结点指针
    node *ptr[MAX_M + 1]; //孩子结点指针数组
} BTNode;                 //B-树结点结构体

class BTree
{
private:
    BTNode *root;

public:
    void Creat()
    {
        root = new BTNode;
        root->keynum = 0;
        root->parent = NULL;
        for (int i = 0; i < MAX_M; i++)
        {
            root->ptr[i] = NULL;
        }
    }
    void Read()
    {
        ifstream fin("B-Tree.txt");
        int temp;

        Creat();
        while (!fin.eof())
        {
            fin >> temp;
            Insert(temp);
        }
    }
    BTNode *GetRoot()
    {
        return root;
    }
    BTNode *Search(int e, int &num)
    {
        node *p;
        int k = 0;

        p = root; //从根结点开始
        while (p != NULL)
        {
            if (e == p->key[k])
            {
                //cout << e << " 查找成功！" << endl;
                num = k;
                return p;
            }
            if (e < p->key[k])
            {
                p = p->ptr[k];
                k = 0;
            }
            else
            {
                k++;
                if (k == p->keynum)
                {
                    p = p->ptr[p->keynum];
                    k = 0;
                }
            }
        }
        return NULL;
    }
    BTNode *FindPosition(int e)
    {
        node *p;
        int k = 0;

        p = root;
        while (p->ptr[0] != NULL)
        {
            if (e < p->key[k])
                p = p->ptr[k];
            else
            {
                k++;
                if (k == p->keynum)
                {
                    p = p->ptr[p->keynum];
                    k = 0;
                }
            }
        }
        return p;
    }
    void InsertKey(BTNode *cur, int e, BTNode *nex)
    {
        int i, j, mid;
        BTNode *newnode, *newroot;
        for (i = 0; i < cur->keynum; i++) //先将该关键字及下一支地址存入当前结点合适的位置
            if (e < cur->key[i])
                break;
        for (j = cur->keynum; j > i; j--)
        {
            cur->key[j] = cur->key[j - 1]; //将关键字和指针向后移
            cur->ptr[j + 1] = cur->ptr[j];
        }
        cur->key[i] = e; //放入新的关键字和指针
        cur->ptr[i + 1] = nex;
        if (cur->keynum < MAX_M - 1) //当当前分支结点的关键字数小于m-1，直接插入不分裂
        {
            cur->keynum++;
            return; //直接退出，不分裂
        }
        else //否则，分裂处理
        {
            //当cur为根结点时
            if (cur == root)
            { //新开一个根结点,并更新相关项
                newroot = new BTNode;
                newroot->keynum = 0;
                newroot->parent = NULL;
                for (j = 0; j < MAX_M; j++)
                    newroot->ptr[j] = NULL;
                cur->parent = newroot;
                newroot->ptr[0] = cur;
                root = newroot;
            }
            newnode = new BTNode;
            newnode->parent = cur->parent; //初始化新结点父亲指针
            for (j = 0; j < MAX_M; j++)
                newnode->ptr[j] = NULL; //初始化新结点孩子指针数组
            i = floor((MAX_M - 1) / 2) + 1;
            mid = i - 1;
            newnode->keynum = MAX_M - i;               //初始化新结点关键字数
            cur->keynum = MAX_M - newnode->keynum - 1; // 更新当前结点剩余关键字数
            j = 0;
            while (i < MAX_M)
            {
                newnode->key[j] = cur->key[i]; //转移cur中间关键字之后的关键字
                newnode->ptr[j] = cur->ptr[i]; //转移相应孩子指针
                if (newnode->ptr[j])
                    newnode->ptr[j]->parent = newnode;
                cur->ptr[i] = NULL;
                i++;
                j++;
            }
            newnode->ptr[j] = cur->ptr[i]; //转移最后一个指针
            if (newnode->ptr[j])
                newnode->ptr[j]->parent = newnode;
            InsertKey(cur->parent, cur->key[mid], newnode); //中间关键字及指向新结点指针插入cur的父结点中
        }
    }
    void Insert(int e)
    {
        BTNode *p;
        p = FindPosition(e);

        InsertKey(p, e, NULL);
    }
    BTNode *FindChildMin(BTNode *p, int &min)
    {
        if (p->ptr[0] == NULL) //p为最底层
        {
            min = p->key[0]; //覆盖
            return p;
        }
        else
        {
            return FindChildMin(p->ptr[0], min);
        }
    }
    BTNode *Merge(BTNode *cur, BTNode *bro, int num)
    {
        int temp;                //存父结点中下移的关键字
        int flag_l = 0;          //bro为cur左兄弟标记，1为左兄弟，0为右兄弟
        BTNode *newnode, *other; //新结点，存合并后的结点
        int i = 0, j = 0, k = 0;

        if (bro != cur->parent->ptr[num + 1]) //bro为cur左兄弟
        {
            num -= 1; //更新num为父结点下移关键字位置
            flag_l = 1;
        }
        temp = cur->parent->key[num];
        for (int i = num; i < cur->parent->keynum; i++)
        {
            cur->parent->key[i] = cur->parent->key[i + 1];
            cur->parent->ptr[i + 1] = cur->parent->ptr[i + 2];
        }
        cur->parent->keynum--;
        if (flag_l) //bro为cur左兄弟
        {
            bro->key[bro->keynum] = temp;            //放temp
            bro->ptr[bro->keynum + 1] = cur->ptr[0]; //把右边的结点头孩子指针转移
            if (cur->ptr[0])
                cur->ptr[0]->parent = bro;
            bro->keynum++;
            newnode = bro;
            other = cur;
        }
        else //否则bro为cur右兄弟
        {
            cur->key[cur->keynum] = temp; //放temp
            cur->ptr[cur->keynum + 1] = bro->ptr[0];
            if (bro->ptr[0])
                bro->ptr[0]->parent = cur;
            cur->keynum++;
            newnode = cur;
            other = bro;
        }

        for (int i = newnode->keynum; i < newnode->keynum + other->keynum; i++)
        {
            newnode->key[i] = other->key[i - newnode->keynum]; //转移另一个节点中的数据
            newnode->ptr[i + 1] = other->ptr[i - newnode->keynum + 1];
            if (newnode->ptr[i + 1] != NULL)
                newnode->ptr[i + 1]->parent = newnode; //更新新孩子指针的父结点
        }
        newnode->keynum = cur->keynum + bro->keynum;

        other = NULL;

        return newnode;
    }
    void DeleteButtonKey(BTNode *cur, int num)
    {
        int k, temp;
        BTNode *l, *r;
        for (int i = num; i < cur->keynum; i++)
        {
            cur->key[i] = cur->key[i + 1]; //删除关键字
            //删除指针?
        }
        //如果cur是根，直接删
        cur->keynum--; //关键字数-1

        if (cur->keynum >= (ceil(MAX_M / 2.0) - 1) || cur == root) //如果删去后关键字数仍不小于[m/2]-1
        {

            return; //直接删除，返回
        }
        else
        {
            while (cur->keynum < (ceil(MAX_M / 2.0) - 1))
            {
                temp = 0;
                if (cur->parent == NULL) //如果上溯到根结点
                {
                    if (cur->keynum == 0) //如果根结点空了
                    {
                        if (cur->ptr[0] != NULL) //如果根结点还有孩子
                        {
                            root = cur->ptr[0]; //更改根节点
                            root->parent = NULL;
                        }
                        else
                            root = NULL; //否则B树清空
                        delete cur;
                        break;
                    }
                }
                for (int i = 0; i <= cur->parent->keynum; i++)
                    if (cur->parent->ptr[i] == cur)
                        temp = i;
                if (temp - 1 >= 0 && cur->parent->ptr[temp - 1]->keynum > ceil(MAX_M / 2.0) - 1) //如果左兄弟的关键字数大于[m/2]-1
                {
                    l = cur->parent->ptr[temp - 1];
                    k = 0;
                    while (k < cur->parent->keynum && l->key[l->keynum - 1] > cur->parent->key[k]) //找到父结点中下移关键字位置
                        k++;
                    for (int i = cur->keynum; i > 0; i--) //下移父结点的关键字,全部右移,放在第一位
                        cur->key[i] = cur->key[i - 1];
                    cur->key[0] = cur->parent->key[k];
                    cur->parent->key[k] = l->key[l->keynum - 1]; //上移左兄弟中最大的关键字
                    l->keynum--;                                 //左兄弟少一个关键字
                    cur->keynum++;                               //cur关键字+1
                }
                else
                {
                    if (temp + 1 <= cur->parent->keynum && cur->parent->ptr[temp + 1]->keynum > ceil(MAX_M / 2.0) - 1) //如果右兄弟的关键字数大于[m/2]-1
                    {
                        r = cur->parent->ptr[temp + 1];
                        k = 0;
                        while (k < cur->parent->keynum && r->key[0] > cur->parent->key[k]) //找到父结点中下移关键字位置
                            k++;
                        k -= 1;
                        cur->key[cur->keynum] = cur->parent->key[k]; //下移父结点的关键字，放最后一位
                        cur->parent->key[k] = r->key[0];             //上移右兄弟中最小的关键字
                        r->keynum--;                                 //右兄弟少一个关键字
                        cur->keynum++;                               //cur关键字+1
                    }
                    else
                    {
                        //如果左右兄弟的关键字数都不够，则进行合并
                        if (temp + 1 <= cur->parent->keynum)
                            Merge(cur, cur->parent->ptr[temp + 1], temp); //右兄弟存在
                        else
                            Merge(cur, cur->parent->ptr[temp - 1], temp); //左兄弟存在
                        cur = cur->parent;                                //上溯
                    }
                }
            }
        }
    }
    void Delete(int e)
    {
        int num;
        BTNode *q;

        if (q = Search(e, num)) //查找，如果关键字存在
        {
            if (q->ptr[0] == NULL) //关键字位于底层结点
            {
                DeleteButtonKey(q, num); //直接删除
            }
            else //否则从q结点num+1子树中取最小关键字来覆盖，再将这个最小关键字删除
            {
                q = FindChildMin(q->ptr[num + 1], q->key[num]); //查找num+1子树中的最小关键字，覆盖当前，并更新q为所找到的底层结点
                DeleteButtonKey(q, 0);                          //删除底层结点最小关键字
            }
        }
        else //关键字不存在
            cout << "关键字不存在！" << endl;
    }
    void Print(BTNode *cur)
    {
        if (cur == NULL)
            return;

        if (cur->parent)
            cout << "parent:" << cur->parent->key[0] << '\t';
        cout << "keys:";
        for (int i = 0; i < cur->keynum; i++)
            cout << cur->key[i] << "\t";
        cout << endl;
        for (int i = 0; i <= cur->keynum; i++)
            Print(cur->ptr[i]);
    }
};

int main()
{
    BTree T;
    int e, temp, sel;

    T.Read();
    while (1)
    {
        system("cls");
        cout << "---------B-树管理--------\n";
        cout << "1.查询数据\n2.添加数据\n3.删除数据\n4.显示关系表\n请输入选择：";
        cin >> sel;
        switch (sel)
        {
        case 1:
            cout << "\n请输入你要查询的数据:";
            cin >> e;
            if (T.Search(e, temp))
                cout << '\n'
                     << e << "查找成功！\n";
            else
                cout << '\n'
                     << e << "查找失败！\n";
            system("pause");
            break;
        case 2:
            cout << "\n请输入你要添加的数据:";
            cin >> e;
            if (T.Search(e, temp))
            {
                cout << '\n'
                     << e << "已存在！\n当前关系表为：\n";
                T.Print(T.GetRoot());
            }
            else
            {
                T.Insert(e);
                cout << '\n'
                     << e << "添加成功\n当前关系表为：\n";
                T.Print(T.GetRoot());
            }
            system("pause");
            break;
        case 3:
            cout << "\n请输入你要删除的数据:";
            cin >> e;
            if (!T.Search(e, temp))
            {
                cout << '\n'
                     << e << "不存在！\n当前关系表为：\n";
                T.Print(T.GetRoot());
            }
            else
            {
                T.Delete(e);
                cout << '\n'
                     << e << "删除成功\n当前关系表为：\n";
                T.Print(T.GetRoot());
            }
            system("pause");
            break;
        case 4:
            cout << "\n当前关系表为：\n";
            T.Print(T.GetRoot());
            system("pause");
            break;
        case 0:
            exit(0);
        }
    }
}