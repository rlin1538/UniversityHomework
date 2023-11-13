#include <iostream>
#define STACKINITSIZE 256
#define STACKINCREMENT 128
#define OK 1
#define OVERFLOW 0
#define ERROR 0
using namespace std;

typedef struct SeqStack
{
    int *pBase;
    int *pTop;
    int stacksize; //ջ�ѷ���Ŀռ�
} SeqStack;
//��ʼ�������ټ���ղ���
int InitStack(SeqStack &S)
{
    S.pBase = new int[STACKINITSIZE];
    if (S.pBase == NULL)
        exit(OVERFLOW);
    S.pTop = S.pBase;
    S.stacksize = STACKINITSIZE;
    return OK;
}
int DestroyStack(SeqStack &S)
{
    if (S.pBase != NULL)
    {
        delete[] S.pBase;
        S.pBase = NULL;
    }
    S.pTop = NULL;
    S.stacksize = 0;
    return OK;
}
int ClearStack(SeqStack &S)
{
    S.pTop = S.pBase;
    return OK;
}
//�����Ͳ���
bool StackEmpty(SeqStack S)
{
    if (S.pBase)
    {
        if (S.pBase == S.pTop)
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
int StackLength(SeqStack S)
{
    if (S.pBase)
    {
        return S.pTop - S.pBase;
    }
    return 0;
}
int GetTop(SeqStack S, int &e)
{
    if (S.pBase && (S.pBase != S.pTop))
    {
        e = *(S.pTop - 1);
        return OK;
    }
    return ERROR;
}
void StackTraverse(SeqStack S)
{
    int i = 0;
    if (S.pBase)
    {
        while ((S.pBase + i) < S.pTop)
        {
            cout << *(S.pBase + i) << '\t';
            i++;
        }
        cout << endl;
    }
}
//�ӹ��Ͳ���
int Push(SeqStack &S, int e)
{
    int *temp;
    if (S.pBase)
    {
        if (S.pTop - S.pBase >= S.stacksize) //ջ���˶�̬���ӿռ�
        {
            temp = new int[S.stacksize + STACKINCREMENT];
            if (temp == NULL)
                exit(OVERFLOW);
            for (int j = 0; (S.pBase + j) < S.pTop; j++)
                *(temp + j) = *(S.pBase + j);
            delete[] S.pBase;
            S.pBase = temp;
            S.pTop = S.pBase + S.stacksize;
            S.stacksize += STACKINCREMENT;
        }
        *S.pTop = e;
        S.pTop++;
    }
    return OK;
}
int Pop(SeqStack &S, int &e)
{
    if (S.pBase && S.pBase != S.pTop)
    {
        e = *(S.pTop - 1);
        S.pTop--;
        return OK;
    }
    return ERROR;
}

int menu_sel() //���Բ˵�
{
    char *m[10] = {(char *)"1.��ʼ��ջ",
                   (char *)"2.ɾ��ջ",
                   (char *)"3.���ջ",
                   (char *)"4.�ж�ջΪ��",
                   (char *)"5.ջ����",
                   (char *)"6.��ȡջ��Ԫ��",
                   (char *)"7.����ջ",
                   (char *)"8.��ջ",
                   (char *)"9.��ջ",
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
    SeqStack S;
    for (;;)
    {
        switch (sel = menu_sel())
        {
        case 1:
            InitStack(S);
            system("pause");
            break;
        case 2:
            DestroyStack(S);
            system("pause");
            break;
        case 3:
            ClearStack(S);
            system("pause");
            break;
        case 4:
            if (StackEmpty(S))
                cout << "ջΪ��" << endl;
            else
                cout << "ջ��Ϊ��" << endl;
            system("pause");
            break;
        case 5:
            cout << StackLength(S) << endl;
            system("pause");
            break;
        case 6:
            if (GetTop(S, e))
                cout << "ջ��Ԫ���ǣ�" << e << endl;
            else
                cout << "����,ջΪ�ջ򲻴���" << endl;
            system("pause");
            break;
        case 7:
            StackTraverse(S);
            system("pause");
            break;
        case 8:
            cout << "������ջԪ�أ�";
            cin >> e;
            Push(S, e);
            system("pause");
            break;
        case 9:
            Pop(S, e);
            cout << "��ջֵ�ǣ�" << e << endl;
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