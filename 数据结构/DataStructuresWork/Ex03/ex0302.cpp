#include <iostream>
#define STACKINITSIZE 256
#define STACKINCREMENT 128
#define OK 1
#define OVERFLOW 0
#define ERROR 0
using namespace std;

typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode, *QueuePtr;

class LinkQueue
{
    QueuePtr front;
    QueuePtr rear;

public:
    //初始化、销毁和清空操作
    int InitQueue()
    {
        front = new LNode;
        if (front == NULL)
            exit(OVERFLOW);
        front->next = NULL;
        rear = front;
        return OK;
    }
    int DestroyQueue()
    {
        LNode *p, *q;
        if (front)
        {
            p = front->next;
            while (p)
            {
                q = p->next;
                delete[] p;
                p = q;
            }
            front = NULL; //队列头指针为空，摧毁队列
        }
        return OK;
    }
    int ClearQueue()
    {
        LNode *p, *q;
        if (front)
        {
            p = front->next;
            while (p)
            {
                q = p->next;
                delete[] p;
                p = q;
            }
            front->next = NULL;
            rear = front;
        }
        return OK;
    }
    //访问型操作
    bool QueueEmpty()
    {
        if (front)
        {
            if (front == rear)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        return true;
    }
    int QueueLength()
    {
        LNode *p;
        int i = 0;
        if (front)
        {
            p = front->next;
            while (p)
            {
                i++;
                p = p->next;
            }
            return i;
        }
        return ERROR;
    }
    int GetHead(int &e)
    {
        if (front && (front != rear))
        {
            e = (front->next)->data;
            return OK;
        }
        return ERROR;
    }
    void QueueTraverse()
    {
        LNode *p;
        p = front->next;
        if (front && (front != rear))
        {
            while (p)
            {
                cout << p->data << '\t';
                p = p->next;
            }
            cout << endl;
        }
    }
    //加工型操作
    int EnQueue(int e)
    {
        LNode *s;
        if (front)
        {
            s = new LNode;
            if (s == NULL)
                exit(OVERFLOW);
            s->data = e;
            rear->next = s;
            rear = s;
            rear->next = NULL;
        }
    }
    int DeQueue(int &e)
    {
        LNode *p;
        if (front && (front != rear))
        {
            p = front->next;
            e = p->data;
            front->next = p->next;
            if (rear == p)
                rear = front;
            delete p;
            return OK;
        }
        return ERROR;
    }
};

int menu_sel() //测试菜单
{
    char *m[10] = {(char *)"1.初始化队列",
                   (char *)"2.删除队列",
                   (char *)"3.清空队列",
                   (char *)"4.判断队列为空",
                   (char *)"5.队列长度",
                   (char *)"6.获取队头元素",
                   (char *)"7.遍历队列",
                   (char *)"8.队尾入队",
                   (char *)"9.队头出队",
                   (char *)"0.退出"};
    int i, choice;
    do
    {
        system("cls");
        cout << "-------主菜单-------" << endl;
        for (i = 0; i < 10; i++)
            cout << m[i] << endl;
        cout << "请输入选择：";
        cin >> choice;
    } while (choice < 0 || choice > 9);
    return choice;
}

int main()
{
    int e;
    int sel;
    LinkQueue Q;
    for (;;)
    {
        switch (sel = menu_sel())
        {
        case 1:
            Q.InitQueue();
            system("pause");
            break;
        case 2:
            Q.DestroyQueue();
            system("pause");
            break;
        case 3:
            Q.ClearQueue();
            system("pause");
            break;
        case 4:
            if (Q.QueueEmpty())
                cout << "队列为空" << endl;
            else
                cout << "队列不为空" << endl;
            system("pause");
            break;
        case 5:
            cout << Q.QueueLength() << endl;
            system("pause");
            break;
        case 6:
            if (Q.GetHead(e))
                cout << "队头元素是：" << e << endl;
            else
                cout << "出错,队列为空或不存在" << endl;
            system("pause");
            break;
        case 7:
            Q.QueueTraverse();
            system("pause");
            break;
        case 8:
            cout << "输入入队元素：";
            cin >> e;
            Q.EnQueue(e);
            system("pause");
            break;
        case 9:
            if (Q.DeQueue(e))
                cout << "出队值是：" << e << endl;
            else
            {
                cout << "出错，队列为空或不存在" << endl;
            }
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