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
    void Sort()
    {
        LNode* t, * p, * q = L;

        p = L->next->next;
        while (p)
        {
            q = L;
            t = p->next;
            while (q->next && p->data > q->next->data)
                q = q->next;
            p->next = q->next;
            q->next = p;
            p = t;
        }
    }
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

int menu_sel() //测试菜单
{
    char *m[15] = {(char *)"1.初始化线性表",
                   (char *)"2.创建线性表",
                   (char *)"3.删除线性表",
                   (char *)"4.清空线性表",
                   (char *)"5.判断线性表为空",
                   (char *)"6.线性表长度",
                   (char *)"7.获取线性表元素",
                   (char *)"8.定位元素位置",
                   (char *)"9.寻找前驱元素",
                   (char *)"10.寻找后继元素",
                   (char *)"11.遍历线性表",
                   (char *)"12.替换元素",
                   (char *)"13.插入元素",
                   (char *)"14.删除元素",
                   (char *)"0.退出"}; //在VS2017之后的编译器不允许用常量字符串初始化char数组，故加上(char*)强制转换
    int i, choice;
    do
    {
        system("cls");
        cout << "-------主菜单-------" << endl;
        for (i = 0; i < 15; i++)
            cout << m[i] << endl;
        cout << "请输入选择：";
        cin >> choice;
    } while (choice < 0 || choice > 14);
    return choice;
}

int main()
{
    LinkList List;
    int i;
    int e;
    int sel;
    int cur_e, next_e;
    for (;;)
    {
        switch (sel = menu_sel())
        {
        case 1:
            List.InitList();
            system("pause");
            break;
        case 2:
            List.CreatList();List.Sort();
            system("pause");
            break;
        case 3:
            List.DestroyList();
            system("pause");
            break;
        case 4:
            List.ClearList();
            system("pause");
            break;
        case 5:
            if (List.ListEmpty())
                cout << "线性表为空" << endl;
            else
                cout << "线性表不为空" << endl;
            system("pause");
            break;
        case 6:
            cout << List.ListLength() << endl;
            system("pause");
            break;
        case 7:
            cout << "输入i：";
            cin >> i;
            List.GetElem(i, e);
            cout << "元素是：" << e << endl;
            system("pause");
            break;
        case 8:
            cout << "输入e：";
            cin >> e;
            cout << "元素位置是：" << List.LocateElem(e) << endl;
            system("pause");
            break;
        case 9:
            cout << "输入元素cur_e:";
            cin >> cur_e;
            List.PriorElem(cur_e, e);
            system("pause");
            break;
        case 10:
            cout << "输入元素next_e:";
            cin >> next_e;
            List.NextElem(next_e, e);
            system("pause");
            break;
        case 11:
            List.ListTraverse();
            system("pause");
            break;
        case 12:
            cout << "输入替换位置：";
            cin >> i;
            cout << "输入替换元素：";
            cin >> e;
            List.SetElem(i, e);
            cout << "旧值是：" << e << endl;
            system("pause");
            break;
        case 13:
            cout << "输入插入位置：";
            cin >> i;
            cout << "输入插入元素：";
            cin >> e;
            List.InsertElem(i, e);
            system("pause");
            break;
        case 14:
            cout << "输入删除位置：";
            cin >> i;
            List.DeleteElem(i, e);
            cout << "原值是：" << e << endl;
            system("pause");
            break;
        case 0:
            break;
        }
        if (sel == 0)
            break;
    }
}