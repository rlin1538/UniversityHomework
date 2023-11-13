#include <iostream>
#define LISTINITSIZE 256
#define LISTINCREMENT 128
using namespace std;

struct SequList
{
    int *pData;
    int nLen, nElem;
} List;
//初始化、销毁、清空操作
void InitList(SequList &L)
{
    L.pData = new int[LISTINITSIZE];
    if (L.pData == NULL)
    {
        cout << "InitList failed!" << endl;
        return;
    }
    L.nElem = 0;
    L.nLen = LISTINITSIZE;
}
void CreatList(SequList &L)
{
    int n;
    cout << "输入元素个数：";
    cin >> n;
    L.nElem = n;

    for (int i = 0; i < n; i++)
    {
        cout << "输入第" << i + 1 << "个元素：";
        cin >> *(L.pData + i);
    }
}
void DestroyList(SequList &L)
{
    if (L.pData)
    {
        delete[] L.pData;
        L.pData = NULL;
        L.nLen = 0;
        L.nElem = 0;
    }
}
void ClearList(SequList &L)
{
    if (L.pData)
    {
        L.nElem = 0;
    }
}
//访问型操作
bool ListEmpty(SequList L)
{
    if (L.pData)
    {
        if (L.nElem == 0)
            return true;
        else
            return false;
    }
    return true;
}
int ListLength(SequList L)
{
    if (L.pData)
    {
        return L.nElem;
    }
    return 0;
}
void GetElem(SequList L, int i, int &e)
{
    if (L.pData && (1 <= i && i <= ListLength(L)))
    {
        e = L.pData[i - 1];
    }
    else
        cout << "GetElem failed!" << endl;
}
int LocateElem(SequList L, int e)
{
    int i = 0; //计数
    if (L.pData)
    {
        while (i < L.nElem)
        {
            if (L.pData[i] == e)
                return ++i;
            else
                i++;
        }
    }
    else
        return 0;
    return 0;
}
void PriorElem(SequList L, int cur_e, int &pre_e)
{
    if (L.pData)
    {
        for (int i = 1; i < L.nElem; i++)
        {
            if (L.pData[i] == cur_e)
            {
                pre_e = L.pData[i - 1];
                return;
            }
        }
        cout << "PriorElem failed.";
    }
}
void NextElem(SequList L, int cur_e, int &next_e)
{
    if (L.pData)
    {
        for (int i = 0; i < L.nElem - 1; i++)
        {
            if (L.pData[i] == cur_e)
            {
                next_e = L.pData[i + 1];
                return;
            }
        }
        cout << "Operation failed.";
    }
}
void ListTraverse(SequList L)
{
    if (L.pData)
    {
        for (int i = 0; i < L.nElem; i++)
            cout << L.pData[i] << '\t';
        cout << endl;
    }
}
//加工型操作
void SetElem(SequList &L, int i, int &e)
{
    int temp;
    if (L.pData != NULL && (i >= 1 && i <= ListLength(L)))
    {
        temp = L.pData[i - 1];
        L.pData[i - 1] = e;
        e = temp;
    }
}
void InsertElem(SequList &L, int i, int e)
{
    int *temp;
    if (L.pData)
    {
        if (i < 1 || i > L.nElem+1)
            return;
        if (L.nLen >= L.nElem) //表满了扩大空间
        {
            temp = new int[L.nLen + 10];
            for (int i = 0; i < L.nLen; i++)
                *(temp + i) = L.pData[i];
            L.pData = temp;
            L.nLen += LISTINCREMENT;
        }
        for (int j = L.nElem; j >= i; j--)
        {
            L.pData[j] = L.pData[j - 1];
        }
        L.pData[i - 1] = e;
        L.nElem++;
    }
}
void DeleteElem(SequList &L, int i, int &e)
{
    if (L.pData)
    {
        if (i < 1 || i > L.nElem)
            return;
        e = L.pData[i - 1];
        for (i; i < L.nElem; i++)
        {
            L.pData[i - 1] = L.pData[i];
        }
        L.nElem--;
    }
}

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
    int i;
    int e;
    int sel;
    int cur_e, next_e;
    for (;;)
    {
        switch (sel = menu_sel())
        {
        case 1:
            InitList(List);
            system("pause");
            break;
        case 2:
            CreatList(List);
            system("pause");
            break;
        case 3:
            DestroyList(List);
            system("pause");
            break;
        case 4:
            ClearList(List);
            system("pause");
            break;
        case 5:
            if (ListEmpty(List))
                cout << "线性表为空" << endl;
            else
                cout << "线性表不为空" << endl;
            system("pause");
            break;
        case 6:
            cout << ListLength(List) << endl;
            system("pause");
            break;
        case 7:
            cout << "输入i：";
            cin >> i;
            GetElem(List, i, e);
            cout << "元素是：" << e << endl;
            system("pause");
            break;
        case 8:
            cout << "输入e：";
            cin >> e;
            cout << "元素位置是：" << LocateElem(List, e) << endl;
            system("pause");
            break;
        case 9:
            cout << "输入元素cur_e:";
            cin >> cur_e;
            PriorElem(List, cur_e, e);
            cout << "前驱元素是：" << e;
            system("pause");
            break;
        case 10:
            cout << "输入元素next_e:";
            cin >> next_e;
            NextElem(List, next_e, e);
            cout << "后继元素是：" << e;
            system("pause");
            break;
        case 11:
            ListTraverse(List);
            system("pause");
            break;
        case 12:
            cout << "输入替换位置：";
            cin >> i;
            cout << "输入替换元素：";
            cin >> e;
            SetElem(List, i, e);
            cout << "旧值是：" << e << endl;
            system("pause");
            break;
        case 13:
            cout << "输入插入位置：";
            cin >> i;
            cout << "输入插入元素：";
            cin >> e;
            InsertElem(List, i, e);
            system("pause");
            break;
        case 14:
            cout << "输入删除位置：";
            cin >> i;
            DeleteElem(List, i, e);
            cout << "原值是：" << e << endl;
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