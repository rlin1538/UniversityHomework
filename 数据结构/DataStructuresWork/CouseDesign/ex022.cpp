//22.��3����С������
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#define START 0        //��ʼ��
#define INFINITY 99999 //�Զ���һ�������
#define MAX_V 20       //��󶥵����
#define MAX_E 100      //��������
using namespace std;

struct edge //��
{
    int i;
    int j;
    float w;
};

edge edg[MAX_E];
int visit[MAX_V] = {0}; //������߹�������
string G_name[MAX_V];   //������Ϣ
int f[MAX_V];
int n, m;

//����С������������洢���ڽӾ���T��
void Prim(float G[MAX_V][MAX_V]) //, int T[MAX_V][MAX_V]
{
    int flag[MAX_V] = {0}; //����ѷ��ʵ�����
    int dis[MAX_V];        //��¼��̾�������
    int path[MAX_V];       //��¼·������
    int min, temp, ans = 0;

    flag[0] = 1;                //����һ�������Ƿ���
    for (int i = 0; i < n; i++) //��һ���㿪ʼ����dis
    {
        dis[i] = G[0][i];
        if (dis[i] < INFINITY) //��ʼ��·������path
            path[i] = 0;
        else
            path[i] = -1;
    }
    for (int i = 0; i < n - 1; i++) //ѭ��n-1���ҳ���С������
    {
        min = INFINITY;
        for (int j = 0; j < n; j++)
        {
            if (flag[j] == 0 && dis[j] < min) //������̱�
            {
                min = dis[j];
                temp = j; //��¼��̱�temp
            }
        }
        flag[temp] = 1; //����߹�
        ans += min;
        for (int j = 0; j < n; j++)
        {
            if (flag[j] == 0 && G[temp][j] < INFINITY) //����dis����
                if (G[temp][j] < dis[j])
                {
                    dis[j] = G[temp][j];
                    path[j] = temp;
                }
        }
    }

    /*for (int i = 0; i < n; i++) //������С������
        for (int j = 0; j < n; j++)
            if (path[j] == i)
            {
                T[i][j] = G[i][j];
                T[j][i] = G[j][i]; //�ӱ�
            }*/
    cout << "Prim�㷨��С������Ȩ�غͣ�" << ans << endl;
}

int getfather(int a) //���鼯�Ҹ���
{
    if (f[a] == a)
        return a;
    else
    {
        f[a] = getfather(f[a]);
        return f[a];
    }
}

bool merge(int a, int b) //���鼯�ϲ����Ӽ�
{
    int f1, f2;
    f1 = getfather(a);
    f2 = getfather(b);

    if (f1 != f2) //�������û�й�ͬ����
    {
        f[f2] = f1;  //�ϲ�
        return true; //����true��ʾ���Ժϲ�
    }
    return false; //�����й�ͬ���ȣ�����false
}
bool cmp(edge a, edge b)
{
    return a.w < b.w;
}
void Kruskal()
{
    int count = 0; //�߼���
    int ans = 0;
    edge *path;
    path = new edge[n - 1];

    sort(edg, edg + m, cmp);    //�Ա߼�����
    for (int i = 0; i < n; i++) //�鲢����ʼ��
        f[i] = i;

    for (int i = 0; i < m; i++)
    {
        if (merge(edg[i].i, edg[i].j)) //���Ժϲ�
        {
            path[count] = edg[i];
            count++;
            ans += edg[i].w;
        }
        if (count == n - 1)
            break;
    }
    cout << "Kruskal�㷨��С������Ȩ�غͣ�" << ans << endl;
    cout << "\n����С���������ñ�Ϊ��" << endl;
    for (int i = 0; i < n - 1; i++)
        cout << G_name[path[i].i] << "<--->" << G_name[path[i].j] << "\tȨ��" << path[i].w << endl;
}

void Read(float G[MAX_V][MAX_V])
{
    ifstream fin("matrix.txt");

    fin >> n;
    for (int i = 0; i < n; i++)
        fin >> G_name[i];
    for (int i = 0; i < n; i++) //�ڽӾ����ʼ��
        for (int j = 0; j < n; j++)
            G[i][j] = INFINITY;
    m = 0;
    while (!fin.eof())
    {
        fin >> edg[m].i >> edg[m].j >> edg[m].w;
        G[edg[m].i][edg[m].j] = edg[m].w;
        G[edg[m].j][edg[m].i] = edg[m].w;
        m++;
    }
    cout << "��ǰ�ڽӾ���Ϊ��" << endl;
    for (int i = 0; i < n; i++)
        cout << G_name[i] << "\t";
    cout << "\n\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << G[i][j] << '\t';
        cout << endl;
    }
    cout << endl;
}

int main()
{
    float G[MAX_V][MAX_V]; //�ڽӾ���

    Read(G);
    Prim(G);
    Kruskal();

    return 0;
}

/*
5
A B C D E
0 1 5
0 2 12
0 3 5
0 4 5
1 2 9
1 3 7
1 4 8
2 3 9
2 4 16
3 4 8
*/
/*
5
99999 5 12 5 5
5 99999 9 7 8
12 9 99999 9 16
5 7 9 99999 8
5 8 16 8 99999
*/
