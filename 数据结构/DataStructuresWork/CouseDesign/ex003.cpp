//3.家谱管理系统
#pragma warning(disable : 4996)
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>
#define CHILD 5 //最大孩子数
using namespace std;

ofstream out; //导出文件
struct date   //日期结构
{
    int year;  //年
    int mouth; //月
    int day;   //日
};

struct Member //成员数据结构
{
    char *name;    //姓名
    date birth;    //生日
    bool merry;    //婚否
    char *address; //地址
    bool alive;    //健在否
    date death;    //忌日
};

typedef struct BiTNode //树结点结构
{
    Member data;                  //成员数据
    int generation;               //代数
    BiTNode *parent;              //父亲指针
    int childnum;                 //孩子数
    struct BiTNode *child[CHILD]; //孩子指针
} BiTNode, *BiTree;

void InitBiNode(BiTNode *a) //初始化成员结点
{
    for (int i = 0; i < CHILD; i++)
        a->child[i] = NULL;
    a->data.name = new char[20];
    a->data.address = new char[30];
}

class FamilyTree //家谱树类
{
    BiTree root; //树根结点指针
public:
    void Creat()
    {
        BiTNode *q;
        int y, m, d, temp;
        string s;

        q = new BiTNode[1];
        InitBiNode(q);

        root = q; //设置根结点
        q->parent = NULL;
        q->generation = 1;
        q->childnum = 0;

        cout << "创建第一个成员：" << endl;

        cout << "输入姓名：";
        cin >> s;
        strcpy(q->data.name, s.c_str());
        cout << "是否健在（0为否，1为是）：";
        while (1)
        {
            cin >> temp;
            if (temp == 0)
                q->data.alive = false;
            else if (temp == 1)
                q->data.alive = true;
            else
            {
                cout << "输入有误，重新输入：";
                continue;
            }
            break;
        }
        cout << "输入出生年月日（以空格为分隔）：";
        while (1)
        {
            cin >> y >> m >> d;
            if (m < 0 || m > 12 || d < 0 || d > 31)
            {
                cout << "输入有误，重新输入：";
                continue;
            }
            else
            {
                q->data.birth.year = y;
                q->data.birth.mouth = m;
                q->data.birth.day = d;
            }
            break;
        }
        if (q->data.alive == false)
        {
            cout << "输入去世年月日（以空格为分隔）：";
            while (1)
            {
                cin >> y >> m >> d;
                if (m < 0 || m > 12 || d < 0 || d > 31 || y < q->data.birth.year)
                {
                    cout << "输入有误，重新输入：";
                    continue;
                }
                else
                {
                    q->data.birth.year = y;
                    q->data.birth.mouth = m;
                    q->data.birth.day = d;
                }
                break;
            }
        }
        cout << "是否已婚（0为否，1为是）：";
        while (1)
        {
            cin >> temp;
            if (temp == 0)
                q->data.merry = false;
            else if (temp == 1)
                q->data.merry = true;
            else
            {
                cout << "输入有误，重新输入：";
                continue;
            }
            break;
        }
        cout << "输入地址：";
        cin >> s;
        strcpy(q->data.address, s.c_str());
    }
    void Import(char *file) //导入家谱
    {
        //数据格式：姓名,已故,YYYY.MM.DD-YYYY.MM.DD,已婚,地址
        BiTNode *father[20]; //记录当前各代父亲
        BiTNode *p;          //新结点
        int i, k, num;       //计数用
        int rad;             //日期转换基数
        int ymd;             //年月日记录,0年1月2日
        char *a;             //文件一行
        char *temp;          //临时字符串
        char *c;             //存储中文
        ifstream fin(file);

        c = new char[4];
        a = new char[200];
        temp = new char[30];

        while (!fin.eof())
        {
            fin.getline(a, 200);
            p = new BiTNode[1];
            InitBiNode(p);
            i = 0;
            while (a[i] == '\t') //吃掉制表符
                i++;
            if (i == 0) //如果是第一代
            {
                //root = new BiTNode;
                root = p; //设置根结点
                p->parent = NULL;
                father[0] = p;
                p->generation = 1;
                p->childnum = 0;
            }
            else //否则不是第一代
            {
                father[i] = p;
                p->parent = father[i - 1];                           //确定父亲
                father[i - 1]->child[father[i - 1]->childnum++] = p; //确定孩子
                p->generation = p->parent->generation + 1;           //确定代数
                p->childnum = 0;
            }

            //姓名
            strcpy(temp, "");
            while (a[i] != ',')
            {
                c[0] = a[i];
                c[1] = a[i + 1];
                c[2] = '\0';
                strcat(temp, c); //读入一个中文汉字
                i += 2;
            }
            p->data.name = new char[sizeof(char) * (strlen(temp) + 1)];
            strcpy(p->data.name, temp); //读入姓名
            i++;                        //下一个字符

            //健在否
            strcpy(temp, "");
            while (a[i] != ',')
            {
                c[0] = a[i];
                c[1] = a[i + 1];
                //c[2] = a[i + 2];
                c[2] = '\0';
                strcat(temp, c); //读入一个汉字
                i += 2;
            }
            if (strcmp(temp, "已故") == 0)
                p->data.alive = false;
            else
                p->data.alive = true;
            i++; //下一个字符

            //出生日期
            k = 0;
            ymd = 0;
            strcpy(temp, "");
            while (a[i] != '-')
            {
                if (a[i] == '.')
                {
                    rad = 1; //基数
                    num = 0;
                    for (int j = strlen(temp) - 1; j >= 0; j--)
                    {
                        num = num + rad * (temp[j] - '0');
                        rad *= 10;
                    }
                    if (ymd == 0)
                        p->data.birth.year = num; //出生年
                    if (ymd == 1)
                        p->data.birth.mouth = num; //出生月
                    strcpy(temp, "");
                    k = 0;
                    ymd++;
                    i++;
                }
                temp[k++] = a[i]; //读入一个数字
                temp[k] = '\0';
                i++;
            }
            rad = 1; //基数
            num = 0;
            for (int j = strlen(temp) - 1; j >= 0; j--)
            {
                num = num + rad * (temp[j] - '0');
                rad *= 10;
            }
            p->data.birth.day = num; //出生日
            i++;                     //下一个字符

            //死亡日期
            if (p->data.alive == false) //如果已故
            {
                k = 0;
                ymd = 0;
                strcpy(temp, "");
                while (a[i] != ',')
                {
                    if (a[i] == '.')
                    {
                        rad = 1; //基数
                        num = 0;
                        for (int j = strlen(temp) - 1; j >= 0; j--)
                        {
                            num = num + rad * (temp[j] - '0');
                            rad *= 10;
                        }
                        if (ymd == 0)
                            p->data.death.year = num; //死亡年
                        if (ymd == 1)
                            p->data.death.mouth = num; //死亡月
                        strcpy(temp, "");
                        k = 0;
                        ymd++;
                        i++;
                    }
                    temp[k++] = a[i]; //读入一个数字
                    temp[k] = '\0';
                    i++;
                }
                rad = 1; //基数
                num = 0;
                for (int j = strlen(temp) - 1; j >= 0; j--)
                {
                    num = num + rad * (temp[j] - '0');
                    rad *= 10;
                }
                p->data.death.day = num; //死亡日
            }
            i++;

            //婚否
            strcpy(temp, "");
            while (a[i] != ',')
            {
                c[0] = a[i];
                c[1] = a[i + 1];
                c[2] = '\0';
                strcat(temp, c); //读入一个汉字
                i += 2;
            }
            if (strcmp(temp, "未婚") == 0)
                p->data.merry = false;
            else
                p->data.merry = true;
            i++; //下一个字符

            //地址
            strcpy(temp, "");
            while (i < strlen(a))
            {
                c[0] = a[i];
                c[1] = a[i + 1];
                c[2] = '\0';
                strcat(temp, c); //读入一个中文汉字
                i += 2;
            }
            p->data.address = new char[sizeof(char) * (strlen(temp) + 1)];
            strcpy(p->data.address, temp); //读入地址

            //for (int i = 0; i < p->generation - 1; i++)
            //    cout << '\t';

            //printf("%s,%d,%d.%d.%d-\n", p->data.name, p->data.alive, p->data.birth.year, p->data.birth.mouth, p->data.birth.day);
        }
        //读入结束
        fin.close();
    }
    void Export(BiTNode *p) //导出家谱
    {
        int len;
        if (p == NULL)
            return;
        for (int i = 0; i < p->generation - 1; i++)
            out << '\t';
        out << p->data.name << ',';
        if (p->data.alive)
            out << "健在," << p->data.birth.year << '.' << p->data.birth.mouth << '.' << p->data.birth.day << '-';
        else
            out << "已故," << p->data.birth.year << '.' << p->data.birth.mouth << '.' << p->data.birth.day << '-' << p->data.death.year << '.' << p->data.death.mouth << '.' << p->data.death.day;
        if (p->data.merry)
            out << ",已婚," << p->data.address;
        else
            out << ",未婚," << p->data.address;
        out << endl;
        for (int i = 0; i < p->childnum; i++)
            Export(p->child[i]);
    }
    void PrintInfo(BiTNode *p)
    {
        printf("%s\t", p->data.name);
        if (p->data.alive)
            printf("健在\t%d.%d.%d-\t\t", p->data.birth.year, p->data.birth.mouth, p->data.birth.day);
        else
            printf("已故\t%d.%d.%d-%d.%d.%d\t", p->data.birth.year, p->data.birth.mouth, p->data.birth.day, p->data.death.year, p->data.death.mouth, p->data.death.day);
        if (p->data.merry)
            printf("已婚\t%s\n", p->data.address);
        else
            printf("未婚\t%s\n", p->data.address);
    }
    void Print(BiTNode *p) //显示家谱
    {
        if (p == NULL)
            return;
        for (int i = 0; i < p->generation - 1; i++)
            cout << '\t';
        printf("%s\n", p->data.name);
        for (int i = 0; i < p->childnum; i++)
            Print(p->child[i]);
    }
    BiTNode *GetRoot()
    {
        return root;
    }
    void DisplayNGenera(BiTNode *p, int n) //显示第n代所有成员
    {
        if (p == NULL)
            return;
        if (p->generation == n)
            PrintInfo(p);
        for (int i = 0; i < p->childnum; i++)
            DisplayNGenera(p->child[i], n);
    }
    void SearchByName(char *a) //按照姓名查询
    {
        BiTNode *p;
        p = Locate(root, a);

        if (p == NULL)
        {
            cout << "未找到该成员。" << endl;
            return;
        }
        cout << "本人：" << endl;
        PrintInfo(p);
        if (p->parent)
        {
            cout << "父亲：" << endl;
            PrintInfo(p->parent);
        }
        for (int i = 0; i < p->childnum; i++)
        {
            cout << "第" << i + 1 << "个孩子" << endl;
            PrintInfo(p->child[i]);
        }
    }
    void SearchByBirth(BiTNode *p, int y, int m) //按照出生年月查询成员
    {
        if (p == NULL)
            return;
        if (p->data.birth.year == y && p->data.birth.mouth == m)
            PrintInfo(p);
        for (int i = 0; i < p->childnum; i++)
            SearchByBirth(p->child[i], y, m);
    }
    void SearchByBirth(BiTNode *p, int y) //按照出生年份查询成员
    {
        if (p == NULL)
            return;
        if (p->data.birth.year == y)
            PrintInfo(p);
        for (int i = 0; i < p->childnum; i++)
            SearchByBirth(p->child[i], y);
    }
    void Relation(BiTNode *a, BiTNode *b) //确定a、b关系
    {
        //a是b的XXX。
        if (a->parent) //如果a不是根结点，即a有父亲,且a辈分小于等于b时
        {
            if (a->parent == b->parent)
            {
                printf("%s是%s的兄弟\n", a->data.name, b->data.name);
                return;
            }
            if (a->parent == b)
            {
                printf("%s是%s的儿子\n", a->data.name, b->data.name);
                return;
            }
            if (a->parent->parent == b)
            {
                printf("%s是%s的孙子\n", a->data.name, b->data.name);
                return;
            }
            if (a->parent->parent && a->parent->parent->parent == b)
            {
                printf("%s是%s的曾孙子\n", a->data.name, b->data.name);
                return;
            }
        }
        if (b->parent) //如果b不是根结点，即b有父亲,且a辈分大于b时
        {
            if (b->parent == a)
            {
                printf("%s是%s的父亲\n", a->data.name, b->data.name);
                return;
            }
            if (b->parent->parent == a)
            {
                printf("%s是%s的祖父\n", a->data.name, b->data.name);
                return;
            }
            if (b->parent->parent && b->parent->parent->parent == a)
            {
                printf("%s是%s的曾祖父\n", a->data.name, b->data.name);
                return;
            }
        }
        printf("%s与%s为非直系关系或关系超出四代\n", a->data.name, b->data.name);
    }
    BiTNode *Locate(BiTNode *p, char *a) //根据姓名定位结点地址
    {
        BiTNode *q = NULL;

        if (p == NULL)
            return NULL;
        if (strcmp(p->data.name, a) == 0)
            return p;
        for (int i = 0; i < p->childnum; i++)
        {
            q = Locate(p->child[i], a);
            if (q != NULL)
                return q;
        }
        return NULL;
    }
    int AddChild(char *a) //为a添加孩子
    {
        BiTNode *p, *q;
        string s;
        int temp, y, m, d;

        p = Locate(root, a);
        if (p == NULL)
        {
            cout << "未找到该人。" << endl;
            return 0;
        }
        q = new BiTNode;
        InitBiNode(q);
        q->parent = p;
        q->generation = p->generation + 1;
        q->childnum = 0; //初始化新新结点q

        p->child[p->childnum] = q;
        p->childnum++; //更新p结点

        cout << "输入姓名：";
        cin >> s;
        strcpy(q->data.name, s.c_str());
        cout << "是否健在（0为否，1为是）：";
        while (1)
        {
            cin >> temp;
            if (temp == 0)
                q->data.alive = false;
            else if (temp == 1)
                q->data.alive = true;
            else
            {
                cout << "输入有误，重新输入：";
                continue;
            }
            break;
        }
        cout << "输入出生年月日（以空格为分隔）：";
        while (1)
        {
            cin >> y >> m >> d;
            if (m < 0 || m > 12 || d < 0 || d > 31)
            {
                cout << "输入有误，重新输入：";
                continue;
            }
            else
            {
                q->data.birth.year = y;
                q->data.birth.mouth = m;
                q->data.birth.day = d;
            }
            break;
        }
        if (q->data.alive == false)
        {
            cout << "输入去世年月日（以空格为分隔）：";
            while (1)
            {
                cin >> y >> m >> d;
                if (m < 0 || m > 12 || d < 0 || d > 31 || y < q->data.birth.year)
                {
                    cout << "输入有误，重新输入：";
                    continue;
                }
                else
                {
                    q->data.birth.year = y;
                    q->data.birth.mouth = m;
                    q->data.birth.day = d;
                }
                break;
            }
        }
        cout << "是否已婚（0为否，1为是）：";
        while (1)
        {
            cin >> temp;
            if (temp == 0)
                q->data.merry = false;
            else if (temp == 1)
                q->data.merry = true;
            else
            {
                cout << "输入有误，重新输入：";
                continue;
            }
            break;
        }
        cout << "输入地址：";
        cin >> s;
        strcpy(q->data.address, s.c_str());
        return 1;
    }
    void Delete(char *a) //删除成员
    {
        BiTNode *p;
        int i;

        p = Locate(root, a);
        if (p == NULL)
        {
            cout << "未找到该成员。" << endl;
            return;
        }
        if (p->parent)
        {
            for (i = 0; i < p->parent->childnum; i++)
                if (p->parent->child[i] == p)
                    break;
            for (i; i < p->parent->childnum - 1; i++)
                p->parent->child[i] = p->parent->child[i + 1]; //删掉p父结点指向p的孩子指针
            p->parent->childnum--;
        }
        Relase(p);
    }
    int Modify(char *a) //修改信息
    {
        BiTNode *q;
        int choose;
        string s;
        int temp, y, m, d;

        q = Locate(root, a);
        while (1)
        {
            system("cls");
            cout << "当前信息：";
            PrintInfo(q);
            cout << "\n1.姓名\n2.健在否\n3.出生日期\n4.去世日期\n5.婚否\n6.地址\n0.退出\n输入要修改的选项：";
            cin >> choose;
            switch (choose)
            {
            case 1:
                cout << "输入姓名：";
                cin >> s;
                strcpy(q->data.name, s.c_str());
                system("pause");
                break;
            case 2:
                cout << "是否健在（0为否，1为是）：";
                while (1)
                {
                    cin >> temp;
                    if (temp == 0)
                        q->data.alive = false;
                    else if (temp == 1)
                        q->data.alive = true;
                    else
                    {
                        cout << "输入有误，重新输入：";
                        continue;
                    }
                    break;
                }
                system("pause");
                break;
            case 3:
                cout << "输入出生年月日（以空格为分隔）：";
                while (1)
                {
                    cin >> y >> m >> d;
                    if (m < 0 || m > 12 || d < 0 || d > 31)
                    {
                        cout << "输入有误，重新输入：";
                        continue;
                    }
                    else
                    {
                        q->data.birth.year = y;
                        q->data.birth.mouth = m;
                        q->data.birth.day = d;
                    }
                    break;
                }
                system("pause");
                break;
            case 4:
                if (q->data.alive == false)
                {
                    cout << "输入去世年月日（以空格为分隔）：";
                    while (1)
                    {
                        cin >> y >> m >> d;
                        if (m < 0 || m > 12 || d < 0 || d > 31 || y < q->data.birth.year)
                        {
                            cout << "输入有误，重新输入：";
                            continue;
                        }
                        else
                        {
                            q->data.birth.year = y;
                            q->data.birth.mouth = m;
                            q->data.birth.day = d;
                        }
                        break;
                    }
                }
                else
                {
                    cout << "无法设置该选项。" << endl;
                }
                system("pause");
                break;
            case 5:
                cout << "是否已婚（0为否，1为是）：";
                while (1)
                {
                    cin >> temp;
                    if (temp == 0)
                        q->data.merry = false;
                    else if (temp == 1)
                        q->data.merry = true;
                    else
                    {
                        cout << "输入有误，重新输入：";
                        continue;
                    }
                    break;
                }
                system("pause");
                break;
            case 6:
                cout << "输入地址：";
                cin >> s;
                strcpy(q->data.address, s.c_str());
                system("pause");
                break;
            case 0:
                break;
            }
            if (choose == 0)
                break;
        }
        return 1;
    }
    void Relase(BiTNode *p)
    {
        if (p == NULL)
            return;
        for (int i = 0; i < p->childnum; i++)
            Relase(p->child[i]);

        delete p;
    }
    void SetEmpty()
    {
        root = NULL;
    }
};

int menu_sel() //测试菜单
{
    char *m[15] = {(char *)"1.创建新家谱",
                   (char *)"2.导入家谱",
                   (char *)"3.导出家谱",
                   (char *)"4.显示家谱",
                   (char *)"5.显示第N代成员",
                   (char *)"6.按姓名查询",
                   (char *)"7.按出生年/年月查询成员",
                   (char *)"8.确定成员与成员的关系",
                   (char *)"9.为成员添加孩子",
                   (char *)"10.删除成员",
                   (char *)"11.修改成员信息",
                   (char *)"12.删除家谱",
                   (char *)"0.退出"};
    int i, choice;
    do
    {
        system("cls");
        cout << "-------家谱管理系统主菜单-------" << endl;
        for (i = 0; i < 13; i++)
            cout << m[i] << endl;
        cout << "请输入选择：";
        cin >> choice;
    } while (choice < 0 || choice > 12);
    return choice;
}

int main()
{
    FamilyTree T;
    string s;
    int sel, choose, y, m;
    BiTNode *a, *b;

    T.Import((char *)"FamilyTree.txt"); //导入初始家谱文件

    while (1)
    {
        if (T.GetRoot() == NULL)
        {
            cout << "当前家谱未创建，请导入或创建！\n";
            system("pause");
        }

        switch (sel = menu_sel())
        {
        case 1:
            system("cls");
            cout << "---------创建新家谱---------\n";
            T.Relase(T.GetRoot());
            cout << "初始化完毕\n";
            T.Creat();
            cout << "创建结束\n";
            system("pause");
            break;
        case 2:
            system("cls");
            cout << "---------导入家谱---------\n";
            cout << "输入导入文件名：";
            cin >> s;
            T.Import((char *)s.c_str());
            cout << "导入结束" << endl;
            system("pause");
            break;
        case 3:
            system("cls");
            cout << "---------导出家谱---------\n";
            cout << "输入导出文件名：";
            cin >> s;
            out.open(s.c_str());
            T.Export(T.GetRoot());
            cout << "导出结束" << endl;
            system("pause");
            break;
        case 4:
            system("cls");
            cout << "---------显示家谱---------\n";
            T.Print(T.GetRoot());
            system("pause");
            break;
        case 5:
            system("cls");
            cout << "---------显示第N代成员---------\n";
            cout << "输入你想输出的N：";
            cin >> choose;
            cout << "第" << choose << "代成员有：\n";
            T.DisplayNGenera(T.GetRoot(), choose);
            cout << "以上\n";
            system("pause");
            break;
        case 6:
            system("cls");
            cout << "---------按姓名查询---------\n";
            cout << "输入姓名：";
            cin >> s;
            T.SearchByName((char *)s.c_str());
            system("pause");
            break;
        case 7:
            system("cls");
            cout << "---------按出生年/年月查询---------\n";
            cout << "输入年份：";
            cin >> y;
            cout << "输入月份(模糊请输入0)：";
            while (1)
            {
                cin >> m;
                if (m < 0 || m > 12)
                    cout << "输入有误,请重输：" << endl;
                else
                    break;
            }
            if (m == 0)
                T.SearchByBirth(T.GetRoot(), y);
            else
                T.SearchByBirth(T.GetRoot(), y, m);
            cout << "以上" << endl;
            system("pause");
            break;
        case 8:
            system("cls");
            cout << "--------确定成员与成员的关系----------\n";
            cout << "输入成员1姓名：";
            while (1)
            {
                cin >> s;
                a = T.Locate(T.GetRoot(), (char *)s.c_str());
                if (a == NULL)
                    cout << "输入有误，请重输：";
                else
                    break;
            }
            cout << "输入成员2姓名：";
            while (1)
            {
                cin >> s;
                b = T.Locate(T.GetRoot(), (char *)s.c_str());
                if (b == NULL || b == a)
                    cout << "输入有误，请重输：";
                else
                    break;
            }
            T.Relation(a, b);
            system("pause");
            break;
        case 9:
            system("cls");
            cout << "---------为成员添加孩子---------\n";
            cout << "输入该成员姓名：";
            cin >> s;
            T.AddChild((char *)s.c_str());
            system("pause");
            break;
        case 10:
            system("cls");
            cout << "---------删除成员---------\n";
            cout << "输入成员姓名：";
            while (1)
            {
                cin >> s;
                a = T.Locate(T.GetRoot(), (char *)s.c_str());
                if (a == NULL)
                    cout << "输入有误，请重输：";
                else
                    break;
            }
            cout << "你确定要删除" << a->data.name << "及其所有后代?\n1确定，0取消：";
            cin >> choose;
            if (choose == 1)
            {
                T.Delete((char *)s.c_str());
                cout << "删除完成\n";
            }
            system("pause");
            break;
        case 11:
            system("cls");
            cout << "---------修改信息---------\n";
            cout << "输入成员姓名：";
            while (1)
            {
                cin >> s;
                a = T.Locate(T.GetRoot(), (char *)s.c_str());
                if (a == NULL)
                    cout << "输入有误，请重输：";
                else
                    break;
            }
            T.Modify((char *)s.c_str());
            system("pause");
            break;
        case 12:
            system("cls");
            cout << "-----------------删除家谱-------------------\n";
            cout << "你确定要删除该家谱?\n1确定，0取消：";
            cin >> choose;
            if (choose == 1)
            {
                T.Relase(T.GetRoot());
                T.SetEmpty();
                cout << "删除完成\n";
            }
            system("pause");
            break;

        case 0:
            break;
        }
        if (sel == 0)
            break;
    }
}