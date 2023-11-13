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
    //初始化、销毁、清空操作
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

    void SelSort()
    {
        LNode *p, *q, *min;
        int temp;
        for (p = L->next; p->next != NULL; p = p->next)
        {
            min = p;
            for (q = p->next; q; q = q->next)
            {
                if (q->data < min->data)
                    min = q;
            }
            temp = p->data;
            p->data = min->data;
            min->data = temp;
        }
    }
};

int main()
{
    LinkList L;
    L.InitList();
    L.CreatList();
    L.SelSort();
    cout << "排序后为：";
    L.ListTraverse();
}