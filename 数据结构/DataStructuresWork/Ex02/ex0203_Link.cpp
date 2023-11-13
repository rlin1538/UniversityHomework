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
    void CreatList(int n)
    {
        LNode *s;
        LNode *p;
        
        p = L;
        for (int i = 0; i < n; i++)
        {
            s = new LNode;
            s->data=i+1;
            s->next = p->next;
            p->next = s;
            p = p->next;
        }
    }
    void DestroyList()
    {
        LNode *p, *q;
        p = L->next;
        while (p)
        {
            q = p->next;
            delete[] p;
            p = q;
        }
        L = NULL; //链表头指针为空，摧毁链表
    }
    void ClearList()
    {
        LNode *p, *q;
        p = L->next;
        while (p) //逐个删除节点
        {
            q = p->next;
            delete[] p;
            p = q;
        }
        L->next = NULL; //头指针指向空，链表清空
    }
    //访问型操作
    bool ListEmpty()
    {
        if (L != NULL)
            if (L->next == NULL)
                return true;
            else
                return false;
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
        else
            cout << "GetElem failed!" << endl;
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
                cout << "NotFound";
                return 0;
            }
            return i + 1;
        }
        else
            cout << "LocateElem failed" << endl;
        return 0;
    }
    void PriorElem(int cur_e, int &pre_e)
    {
        int pos;
        if (L)
        {
            pos = LocateElem(cur_e); //定位cur_e的位置
            if (pos > 1)
            {
                GetElem(pos - 1, pre_e); //返回pos前一个节点数据
                cout << "前驱元素是：" << pre_e << endl;
            }
            else
            {
                cout << "NotFound PriorElem" << endl;
            }
        }
    }
    void NextElem(int cur_e, int &next_e)
    {
        int pos;
        if (L)
        {
            pos = LocateElem(cur_e); //定位cur_e的位置
            if (pos > 0 && pos < ListLength())
            {
                GetElem(pos + 1, next_e);
                cout << "后继元素是：" << next_e << endl;
            }
            else
            {
                cout << "NotFound NextElem" << endl;
            }
        }
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
    //加工型操作
    void SetElem(int i, int &e)
    {
        LNode *p;
        int j = 1;
        int temp;
        if (L && (1 <= i && i <= ListLength()))
        {
            p = L->next;
            while (j < i)
            {
                p = p->next;
                j++;
            }
            temp = p->data;
            p->data = e;
            e = temp;
        }
        else
            cout << "SetElem Failed->" << endl;
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
    void DeleteElem(int i, int &e)
    {
        LNode *p, *q;
        int j = 1;
        if (L != NULL)
        {
            p = L->next;
            q = L;
            while (j < i)
            {
                q = p;
                p = p->next;
                j++;
            }
            q->next = p->next;
            e = p->data;
            delete[] p;
        }
    }
};

int main()
{
    int n,m;
    LinkList List;
    int temp=0;
    int e;
    cin>>n>>m;
    List.InitList();
    List.CreatList(n);
    while (List.ListLength())
    {
        temp = (temp+m) % List.ListLength();
        if (temp == 0) temp=List.ListLength();
        List.DeleteElem(temp,e);
        temp--;
        cout<<e<<"\t";
    }
}