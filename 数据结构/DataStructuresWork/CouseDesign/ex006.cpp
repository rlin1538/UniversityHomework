//6.������·��ʾ
#pragma warning(disable : 4996)
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#define OK 1
#define OVERFLOW 0
#define ERROR 0
using namespace std;

struct Station //վ��ṹ��
{
    char name[30];      //վ������
    int pass[50]; //�����Ĺ������������
    int passnum;        //������������·��
};

struct Bus //�����ṹ��
{
    int num;        //���������
    int route[100]; //������վ����
    int stanum;     //����վ����;
};

struct Path
{
    int bus_num; //��ǰվ��������������
    int pre;     //ǰһվ����
};

typedef struct LNode //���н��
{
    int data;
    struct LNode *next;
} LNode, *QueuePtr;

class LinkQueue
{
    QueuePtr front;
    QueuePtr rear;

public:
    //��ʼ������
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
    //���
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
    //����
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
class Map //��ͼ��
{
    Station *sta;
    int allstanum; //��վ����
    Bus bus[1000];
    int allbusnum; //�ܹ�����
public:
    void InitMap() //��ʼ��
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
        ifstream fin("�Ͼ�������·.txt");
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
            while (i < strlen(s)) //Ϊ�ù�����Ӿ���վ��
            {
                strcpy(temp, "");
                while (i < strlen(s) && s[i] != ',') //��վ����
                {
                    c[0] = s[i];
                    c[1] = s[i + 1];
                    c[2] = '\0';
                    strcat(temp, c);
                    i += 2;
                }
                if ((pos = LocateStation(temp)) != -1) //���վ���Ѵ���
                {
                    sta[pos].pass[sta[pos].passnum++] = bus[allbusnum].num; //��¼վ�㾭����ǰ����
                }
                else //��������ڣ��½�վ��
                {
                    strcpy(sta[allstanum].name, temp);                                  //��������
                    sta[allstanum].pass[sta[allstanum].passnum++] = bus[allbusnum].num; //��¼վ�㾭����ǰ����
                    pos = allstanum;
                    allstanum++; //վ����+1
                }
                if (i <= strlen(s))
                {
                    bus[allbusnum].route[bus[allbusnum].stanum++] = pos;
                    i++;
                }
            }

            allbusnum++; //���һ��������·���
        }
    }
    int LocateStation(char a[30]) //��λXXվ��sta��λ��
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
            cout << bus[i].num << "·  ";
            for (int j = 0; j < bus[i].stanum; j++)
            {
                cout << sta[bus[i].route[j]].name << ",";
            }
            cout << endl;
        }
    }
    void SearchMinStation(Station start, Station dest) //��������վ��·��
    {
        int pre, later; //��ǰվ����ĳ����·��ǰһվ�ͺ�һվ���
        int bus_num;    //ĳ�������
        int count = 1;  //����վ��ͳ��
        int temp;
        LinkQueue Q;
        int p;
        Q.InitQueue();
        InitVisited();

        Q.EnQueue(LocateStation(start.name)); //������
        visited[LocateStation(start.name)] = 1;
        while (!Q.QueueEmpty())
        {
            Q.DeQueue(temp);
            if (strcmp(sta[temp].name, dest.name) == 0)
            {
                //�ҵ��յ�
                printf("%s(���,%d·)-->", sta[temp].name, path[temp].bus_num);
                p = path[temp].pre;
                while (p != LocateStation(start.name))
                {
                    count++;
                    printf("%s(%d·)-->", sta[p].name, path[p].bus_num);
                    p = path[p].pre;
                }
                printf("%s(�յ�)\n", sta[p].name);
                cout << "��" << count + 1 << "վ\n";
                return;
            }
            for (int i = 0; i < sta[temp].passnum; i++) //������վ���漰���й���������ǰ������վ�����
            {
                bus_num = sta[temp].pass[i];
                FindPreLater(bus_num, sta[temp].name, pre, later); //�ҵ�bus��aվ��ǰ��վ����
                if (visited[pre] == 0 && pre != -1)                //���δ�������Ҵ��ڡ����
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
                            pre = -1; //�����վ���Ǹ�����·ͷһվ����û��ǰ��
                        if (j + 1 < bus[i].stanum)
                            later = bus[i].route[j + 1];
                        else
                            later = -1; //���һվ����û�к��
                        return;
                    }
    }
    int FindBusNum(int num)
    {
        for (int i = 0; i < allbusnum; i++)
            if (bus[i].num == num)
                return i;
    }
    void SearchMinTransfer(Station start, Station dest) //��������תվ·��
    {
        int bus_num;   //ĳ�������
        int count = 0; //����վ��ͳ��
        int temp;
        LinkQueue Q;
        int p;
        Q.InitQueue();
        InitVisited();

        Q.EnQueue(LocateStation(start.name)); //������
        visited[LocateStation(start.name)] = 1;
        while (!Q.QueueEmpty())
        {
            Q.DeQueue(temp);
            if (strcmp(sta[temp].name, dest.name) == 0)
            {
                //�ҵ��յ�
                printf("%s(���,%d·)-->", sta[temp].name, path[temp].bus_num);
                p = path[temp].pre;
                while (p != LocateStation(start.name))
                {
                    count++;
                    printf("%s(����%d·)-->", sta[p].name, path[p].bus_num);
                    p = path[p].pre;
                }
                printf("%s(�յ�)\n", sta[p].name);
                cout << "������" << count << "��\n";
                //
                return;
            }
            for (int i = 0; i < sta[temp].passnum; i++) //������վ���漰���й�����������վ�����
            {
                bus_num = FindBusNum(sta[temp].pass[i]);
                //����ǰ��·bus_num������վ�����
                for (int j = 0; j < bus[bus_num].stanum; j++)
                {
                    if (visited[bus[bus_num].route[j]] == 0) //δ���ʹ�ʱ���
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
        cout << "-------------�Ͼ�������·��ʾϵͳ(����0���˳�)--------------\n";
        cout << "�������վ��";
        while (1)
        {
            cin >> s;
            if (strcmp("0",s.c_str())==0)
                exit(0);
            if (M.LocateStation((char *)s.c_str()) == -1)
                cout << "��������������:";
            else
                break;
        }
        a = M.FindStation((char *)s.c_str());
        cout << "�����յ�վ��";
        while (1)
        {
            cin >> s;
            if (strcmp("0",s.c_str())==0)
                exit(0);
            if (M.LocateStation((char *)s.c_str()) == -1||strcmp(s.c_str(),a.name)==0)
                cout << "��������������:";
            else
                break;
        }
        b = M.FindStation((char *)s.c_str());
        cout<<"����վ��·�ߣ�\n";
        M.SearchMinStation(b,a);
        cout<<"\n����ת��·�ߣ�\n";
        M.SearchMinTransfer(b, a);
        system("pause");
    }
}
