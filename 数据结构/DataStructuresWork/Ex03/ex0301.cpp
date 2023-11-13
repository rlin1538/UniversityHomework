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
    int stacksize; //栈已分配的空间
} SeqStack;
//初始化、销毁及清空操作
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
//访问型操作
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
//加工型操作
int Push(SeqStack &S, int e)
{
    int *temp;
    if (S.pBase)
    {
        if (S.pTop - S.pBase >= S.stacksize) //栈满了动态增加空间
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

int menu_sel() //测试菜单
{
    char *m[10] = {(char *)"1.初始化栈",
                   (char *)"2.删除栈",
                   (char *)"3.清空栈",
                   (char *)"4.判断栈为空",
                   (char *)"5.栈长度",
                   (char *)"6.获取栈顶元素",
                   (char *)"7.遍历栈",
                   (char *)"8.入栈",
                   (char *)"9.出栈",
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
                cout << "栈为空" << endl;
            else
                cout << "栈不为空" << endl;
            system("pause");
            break;
        case 5:
            cout << StackLength(S) << endl;
            system("pause");
            break;
        case 6:
            if (GetTop(S, e))
                cout << "栈顶元素是：" << e << endl;
            else
                cout << "出错,栈为空或不存在" << endl;
            system("pause");
            break;
        case 7:
            StackTraverse(S);
            system("pause");
            break;
        case 8:
            cout << "输入入栈元素：";
            cin >> e;
            Push(S, e);
            system("pause");
            break;
        case 9:
            Pop(S, e);
            cout << "出栈值是：" << e << endl;
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