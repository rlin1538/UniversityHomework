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
    //��ʼ�������ٺ���ղ���
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
            front = NULL; //����ͷָ��Ϊ�գ��ݻٶ���
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
    //�����Ͳ���
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
    //�ӹ��Ͳ���
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

int menu_sel() //���Բ˵�
{
    char *m[10] = {(char *)"1.��ʼ������",
                   (char *)"2.ɾ������",
                   (char *)"3.��ն���",
                   (char *)"4.�ж϶���Ϊ��",
                   (char *)"5.���г���",
                   (char *)"6.��ȡ��ͷԪ��",
                   (char *)"7.��������",
                   (char *)"8.��β���",
                   (char *)"9.��ͷ����",
                   (char *)"0.�˳�"};
    int i, choice;
    do
    {
        system("cls");
        cout << "-------���˵�-------" << endl;
        for (i = 0; i < 10; i++)
            cout << m[i] << endl;
        cout << "������ѡ��";
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
                cout << "����Ϊ��" << endl;
            else
                cout << "���в�Ϊ��" << endl;
            system("pause");
            break;
        case 5:
            cout << Q.QueueLength() << endl;
            system("pause");
            break;
        case 6:
            if (Q.GetHead(e))
                cout << "��ͷԪ���ǣ�" << e << endl;
            else
                cout << "����,����Ϊ�ջ򲻴���" << endl;
            system("pause");
            break;
        case 7:
            Q.QueueTraverse();
            system("pause");
            break;
        case 8:
            cout << "�������Ԫ�أ�";
            cin >> e;
            Q.EnQueue(e);
            system("pause");
            break;
        case 9:
            if (Q.DeQueue(e))
                cout << "����ֵ�ǣ�" << e << endl;
            else
            {
                cout << "��������Ϊ�ջ򲻴���" << endl;
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