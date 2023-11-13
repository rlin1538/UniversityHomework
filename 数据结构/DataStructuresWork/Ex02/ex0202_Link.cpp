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
    void GetElem(int i, int &e)
    {
        LNode *p;
        int j = 1;
        if (L && (i > 0 && i <= ListLength())) //判断L存在且i符合定义域
        {
            p = L->next;
            while (j < i)
            {
                p = p->next;
                j++;
            }
            e = p->data;
        }
    }
    int LocateElem(int e)
    {
        int i = 0; //计数
        LNode *p;
        if (L)
        {
            p = L->next;
            while (p && (p->data != e)) //当e不是链表中数据继续循环
            {
                ++i;
                p = p->next;
            }
            if (i >= ListLength())
            {
                //cout << "NotFound";
                return 0;
            }
            return i + 1;
        }

        //cout << "LocateElem failed" << endl;
        return 0;
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
    void InsertElem(int i, int e)
    {
        LNode *s;
        LNode *p;

        int j = 1;
        if (L && (i >= 0 && i <= ListLength()))
        {
            s = new LNode;
            s->data = e; //创建新节点

            p = L;
            while (j < i) //定位i
            {
                p = p->next;
                j++;
            }
            s->next = p->next;
            p->next = s;
        }
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

void Combine(LinkList &A, LinkList &B)
{
    int e;
    for (int i = 1; i <= B.ListLength(); i++)
    {
        B.GetElem(i, e);
        if (A.LocateElem(e))
            continue;
        A.InsertElem(1, e);
    }
    A.SelSort();
}

int main()
{
    LinkList A, B;
    A.InitList();
    B.InitList();
    A.CreatList();
    B.CreatList();
    cout << "合并后：";
    Combine(A, B);
    A.ListTraverse();
}