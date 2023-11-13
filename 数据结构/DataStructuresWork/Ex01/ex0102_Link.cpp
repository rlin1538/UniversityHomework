#include <iostream>
using namespace std;

struct LNode //定义一个节点结构体
{
    int data;
    struct LNode *next;
};

class LinkList //抽象一个单链表类
{
    LNode *L; //头指针
public:
    void InitList()
    {
        L = new LNode;
        L->data = 0;
        L->next = NULL;
    }
    void CreatList()
    {
        int n;
        LNode *s;
        LNode *p;
        cout << "输入元素个数：";
        cin >> n;

        p = L;
        for (int i = 0; i < n; i++)
        {
            s = new LNode;
            cout << "输入第" << i + 1 << "个元素：";
            cin >> s->data;
            s->next = p->next;
            p->next = s;
            p = p->next;
        }
    }

    int ListLength()
    {
        LNode *p;
        int count = 0;
        if (L)
        {
            p = L->next;
            while (p != NULL)
            {
                count++;
                p = p->next;
            }
        }
        else
            cout << "List isn't exists->" << endl;
        return count;
    }
    void ListTraverse()
    {
        LNode *p;
        if (L)
        {
            p = L->next;
            while (p) //遍历所有有效的节点
            {
                cout << p->data << '\t';
                p = p->next;
            }
            cout << endl;
        }
        else
            cout << "List isn't exists" << endl;
    }

    void InvertList() //倒置函数
    {
        LNode *p, *q;
        int i = ListLength() - 1;
        p = L->next;

        L->next = NULL; //摘下头结点

        while (i--) //循环将余下节点依次插入头节点之后
        {
            q = p->next;
            p->next = L->next;
            L->next = p;
            p = q;
        }
        p->next = L->next; //将最后一个节点插入头节点之后
        L->next = p;
    }
};

int main()
{
    LinkList List;
    List.InitList();
    cout << "创建一个线性表：" << endl;
    List.CreatList();
    cout << "倒置前线性表为：" << endl;
    List.ListTraverse();
    List.InvertList();
    cout << "倒置后线性表为：" << endl;
    List.ListTraverse();
}