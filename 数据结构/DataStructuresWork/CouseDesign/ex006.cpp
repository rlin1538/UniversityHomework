//6.公交线路提示
#pragma warning(disable : 4996)
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#define OK 1
#define OVERFLOW 0
#define ERROR 0
using namespace std;

struct Station //站点结构体
{
    char name[30];      //站点名称
    int pass[50]; //经过的公交车编号数组
    int passnum;        //经过公交车线路数
};

struct Bus //公交结构体
{
    int num;        //公交车编号
    int route[100]; //经过的站点编号
    int stanum;     //经过站点数;
};

struct Path
{
    int bus_num; //当前站点在哪条公交线
    int pre;     //前一站点编号
};

typedef struct LNode //队列结点
{
    int data;
    struct LNode *next;
} LNode, *QueuePtr;

class LinkQueue
{
    QueuePtr front;
    QueuePtr rear;

public:
    //初始化操作
    int InitQueue()
    {
        front = new LNode;
        if (front == NULL)
            exit(OVERFLOW);
        front->next = NULL;
        rear = front;
        return OK;
    }
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
    //入队
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
    //出队
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
int *visited;
Path *path;

void InitVisited()
{
    visited = new int[10000];
    path = new Path[10000];
    for (int i = 0; i < 10000; i++)
    {
        visited[i] = 0;
        path[i].bus_num = path[i].pre = -1;
    }
}
class Map //地图类
{
    Station *sta;
    int allstanum; //总站点数
    Bus bus[1000];
    int allbusnum; //总公交数
public:
    void InitMap() //初始化
    {
        sta = new Station[10000];
        for (int i = 0; i < 10000; i++)
            sta[i].passnum = 0;
        for (int i = 0; i < 1000; i++)
            bus[i].stanum = 0;
        allstanum = allbusnum = 0;
    }
    void ReadMap()
    {
        int i, pos;
        ifstream fin("南京公交线路.txt");
        char s[1000];
        char c[3];
        char temp[50];

        while (!fin.eof())
        {
            fin >> bus[allbusnum].num;
            fin.getline(s, 1000);
            if (strlen(s) < 3)
                return;
            i = 5;
            while (i < strlen(s)) //为该公交添加经过站点
            {
                strcpy(temp, "");
                while (i < strlen(s) && s[i] != ',') //读站点名
                {
                    c[0] = s[i];
                    c[1] = s[i + 1];
                    c[2] = '\0';
                    strcat(temp, c);
                    i += 2;
                }
                if ((pos = LocateStation(temp)) != -1) //如果站点已存在
                {
                    sta[pos].pass[sta[pos].passnum++] = bus[allbusnum].num; //记录站点经过当前公交
                }
                else //如果不存在，新建站点
                {
                    strcpy(sta[allstanum].name, temp);                                  //拷贝名字
                    sta[allstanum].pass[sta[allstanum].passnum++] = bus[allbusnum].num; //记录站点经过当前公交
                    pos = allstanum;
                    allstanum++; //站点数+1
                }
                if (i <= strlen(s))
                {
                    bus[allbusnum].route[bus[allbusnum].stanum++] = pos;
                    i++;
                }
            }

            allbusnum++; //完成一条公交线路添加
        }
    }
    int LocateStation(char a[30]) //定位XX站在sta中位置
    {
        for (int i = 0; i < allstanum; i++)
        {
            if (strcmp(a, sta[i].name) == 0)
                return i;
        }
        return -1;
    }
    void PrintMap()
    {
        for (int i = 0; i < allbusnum; i++)
        {
            cout << bus[i].num << "路  ";
            for (int j = 0; j < bus[i].stanum; j++)
            {
                cout << sta[bus[i].route[j]].name << ",";
            }
            cout << endl;
        }
    }
    void SearchMinStation(Station start, Station dest) //搜索最少站点路线
    {
        int pre, later; //当前站点在某条线路中前一站和后一站编号
        int bus_num;    //某公交编号
        int count = 1;  //经过站点统计
        int temp;
        LinkQueue Q;
        int p;
        Q.InitQueue();
        InitVisited();

        Q.EnQueue(LocateStation(start.name)); //起点入队
        visited[LocateStation(start.name)] = 1;
        while (!Q.QueueEmpty())
        {
            Q.DeQueue(temp);
            if (strcmp(sta[temp].name, dest.name) == 0)
            {
                //找到终点
                printf("%s(起点,%d路)-->", sta[temp].name, path[temp].bus_num);
                p = path[temp].pre;
                while (p != LocateStation(start.name))
                {
                    count++;
                    printf("%s(%d路)-->", sta[p].name, path[p].bus_num);
                    p = path[p].pre;
                }
                printf("%s(终点)\n", sta[p].name);
                cout << "共" << count + 1 << "站\n";
                return;
            }
            for (int i = 0; i < sta[temp].passnum; i++) //将出队站所涉及所有公交车中其前后两个站点入队
            {
                bus_num = sta[temp].pass[i];
                FindPreLater(bus_num, sta[temp].name, pre, later); //找到bus中a站点前后站点编号
                if (visited[pre] == 0 && pre != -1)                //如果未被访问且存在。入队
                {
                    Q.EnQueue(pre);
                    visited[pre] = visited[temp] + 1;
                    path[pre].pre = temp;
                    path[pre].bus_num = bus_num;
                }
                if (visited[later] == 0 && later != -1)
                {
                    Q.EnQueue(later);
                    visited[later] = visited[temp] + 1;
                    path[later].pre = temp;
                    path[later].bus_num = bus_num;
                }
            }
        }
    }
    void FindPreLater(int busnum, char na[30], int &pre, int &later)
    {
        for (int i = 0; i < allbusnum; i++)
            if (bus[i].num == busnum)
                for (int j = 0; j < bus[i].stanum; j++)
                    if (strcmp(na, sta[bus[i].route[j]].name) == 0)
                    {
                        if (j - 1 >= 0)
                            pre = bus[i].route[j - 1];
                        else
                            pre = -1; //如果该站点是该条线路头一站，则没有前驱
                        if (j + 1 < bus[i].stanum)
                            later = bus[i].route[j + 1];
                        else
                            later = -1; //最后一站，则没有后继
                        return;
                    }
    }
    int FindBusNum(int num)
    {
        for (int i = 0; i < allbusnum; i++)
            if (bus[i].num == num)
                return i;
    }
    void SearchMinTransfer(Station start, Station dest) //搜索最少转站路线
    {
        int bus_num;   //某公交编号
        int count = 0; //经过站点统计
        int temp;
        LinkQueue Q;
        int p;
        Q.InitQueue();
        InitVisited();

        Q.EnQueue(LocateStation(start.name)); //起点入队
        visited[LocateStation(start.name)] = 1;
        while (!Q.QueueEmpty())
        {
            Q.DeQueue(temp);
            if (strcmp(sta[temp].name, dest.name) == 0)
            {
                //找到终点
                printf("%s(起点,%d路)-->", sta[temp].name, path[temp].bus_num);
                p = path[temp].pre;
                while (p != LocateStation(start.name))
                {
                    count++;
                    printf("%s(换乘%d路)-->", sta[p].name, path[p].bus_num);
                    p = path[p].pre;
                }
                printf("%s(终点)\n", sta[p].name);
                cout << "共换乘" << count << "次\n";
                //
                return;
            }
            for (int i = 0; i < sta[temp].passnum; i++) //将出队站所涉及所有公交车中所有站点入队
            {
                bus_num = FindBusNum(sta[temp].pass[i]);
                //将当前线路bus_num的所有站点入队
                for (int j = 0; j < bus[bus_num].stanum; j++)
                {
                    if (visited[bus[bus_num].route[j]] == 0) //未访问过时入队
                    {
                        Q.EnQueue(bus[bus_num].route[j]);
                        visited[bus[bus_num].route[j]] = visited[temp] + 1;
                        path[bus[bus_num].route[j]].pre = temp;
                        path[bus[bus_num].route[j]].bus_num = bus[bus_num].num;
                    }
                }
            }
        }
    }
    Station FindStation(char na[30])
    {
        return sta[LocateStation(na)];
    }
};

int main()
{
    Map M;
    Station a, b;
    string s;
    int sel = 1;

    M.InitMap();
    M.ReadMap();

    while (sel)
    {
        system("cls");
        cout << "-------------南京公交线路提示系统(输入0可退出)--------------\n";
        cout << "输入起点站：";
        while (1)
        {
            cin >> s;
            if (strcmp("0",s.c_str())==0)
                exit(0);
            if (M.LocateStation((char *)s.c_str()) == -1)
                cout << "输入有误请重输:";
            else
                break;
        }
        a = M.FindStation((char *)s.c_str());
        cout << "输入终点站：";
        while (1)
        {
            cin >> s;
            if (strcmp("0",s.c_str())==0)
                exit(0);
            if (M.LocateStation((char *)s.c_str()) == -1||strcmp(s.c_str(),a.name)==0)
                cout << "输入有误请重输:";
            else
                break;
        }
        b = M.FindStation((char *)s.c_str());
        cout<<"最少站点路线：\n";
        M.SearchMinStation(b,a);
        cout<<"\n最少转车路线：\n";
        M.SearchMinTransfer(b, a);
        system("pause");
    }
}
