//��С����������TSP����
#include <iostream>
#include <fstream>
#define START 0        //��ʼ��
#define INFINITY 99999 //�Զ���һ�������
#define MAX_V 20       //��󶥵����
using namespace std;

int DFS[MAX_V], minDFS[MAX_V];
int visit[MAX_V] = {0}; //������߹�������
int num = 1;            //DFS˳��

//����С������������洢���ڽӾ���T�У����ӱ�
void Prim(int G[MAX_V][MAX_V], int n, int T[MAX_V][MAX_V])
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

    for (int i = 0; i < n; i++) //������С�����������ӱ�
        for (int j = 0; j < n; j++)
            if (path[j] == i)
            {
                T[i][j] = G[i][j];
                T[j][i] = G[j][i]; //�ӱ�
            }
}
//����DFS�����minDFS���������ж���
int Tarjan(int G[MAX_V][MAX_V], int cur, int n)
{
    int temp;            //��ʱ����
    if (visit[cur] == 1) //�߽�
        return minDFS[cur];
    num++;
    DFS[cur] = num;    //���ϵ�cur�������DFS
    minDFS[cur] = num; //���ϵ�cur������ĳ�ʼminDFS
    visit[cur] = 1;    //����ѷ���
    for (int i = 0; i < n; i++)
    {
        if (G[cur][i] < INFINITY)
        {
            temp = Tarjan(G, i, n); //����
            if (temp < minDFS[cur]) //���ݸ���minDFS
                minDFS[cur] = temp;
        }
    }
    return minDFS[cur]; //����minDFS
}
//�жϵ�i�����㵽��j�������Ƿ�Ϊ��
bool JudgeBridge(int i, int j)
{
    if (minDFS[j] > DFS[i])
        return true;
    else
        return false;
}
//��ŷ����·������·�������˳�����E���飬startΪ������
void Fleury(int T[MAX_V][MAX_V], int n, int E[2 * MAX_V], int start)
{
    int cur = start;     //��ǰ��
    int G[MAX_V][MAX_V]; //����һ��T
    int k = 0;           //ŷ����·���ʶ������
    int bridge;          //��¼�鵽����

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            G[i][j] = T[i][j];            //����T����
    E[k++] = start;                       //��ʼ���¼��ŷ����·
    for (int i = 0; i < (n - 1) * 2; i++) //���ߣ�n-1��*2����
    {
        num = 0;
        for (int l = 0; l < n; l++) //��ʼ��������
        {
            visit[l] = 0;
            DFS[l] = INFINITY;
            minDFS[l] = INFINITY;
        }
        Tarjan(G, cur, n);          //��Tarjan�㷨��һ����
        for (int j = 0; j < n; j++) //���ҿ��ߵı�
        {
            if (G[cur][j] < INFINITY)
                if (JudgeBridge(cur, j) == false) //�ж��Ƿ�Ϊ��
                {
                    G[cur][j] = INFINITY; //�����ŵĻ�ֱ����
                    E[k++] = j;
                    cur = j;
                    break; //������һ����
                }
                else
                    bridge = j; //��¼�����
            if (j == n - 1)     //���ֻʣ�ſ���
            {
                G[cur][bridge] = INFINITY; //����
                E[k++] = bridge;
                cur = bridge;
            }
        }
    }
}
//�������·��startΪ��������
int *TSP(int M[MAX_V][MAX_V], int n, int start)
{
    int T[MAX_V][MAX_V];
    int E[2 * MAX_V];      //ŷ����·
    int *H;                //���ܶٻ�·
    int flag[MAX_V] = {0}; //������߹�
    int last;
    int k = 0;
    int ans = 0;

    H = new int[n + 1];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            T[i][j] = INFINITY; //��ʼ����С������T����
    Prim(M, n, T);              //������С������
    Fleury(T, n, E, start);     //Ѱ��ŷ����·,�Ե�һ������ĵ�Ϊ������

    //����ŷ����·����·���ҹ��ܶٻ�·
    flag[E[0]] = 1;
    H[k++] = E[0];
    last = E[0]; //��¼ʼ�㵽E����
    for (int i = 1; i < 2 * n - 1; i++)
    {
        if (flag[E[i]] == 0) //���δ���ʹ�ִ�У�����ѷ��ʹ�������
        {
            flag[E[i]] = 1;
            H[k++] = E[i];
            ans += M[last][E[i]];
            last = E[i];
        }
    }
    H[n] = H[0];
    ans += M[last][H[0]];
    //���
    cout << "���·����" << ans << endl;
    return H;
}

int main()
{
    int M[MAX_V][MAX_V]; //�ڽӾ���
    int n;               //���и���
    int *H;
    fstream G;

    G.open("matrix.txt");
    G >> n;
    for (int i = 0; i < n; i++) //�ڽӾ����ʼ��
        for (int j = 0; j < n; j++)
        {
            G >> M[i][j];
        }
    cout << "��ǰ�ڽӾ���Ϊ��" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << M[i][j] << '\t';
        cout << endl;
    }

    H = new int[n + 1];
    H = TSP(M, n, START);
    cout << "·��Ϊ��";
    for (int i = 0; i < n; i++)
        cout << H[i] << "-->";
    cout << H[n] << endl;
}

/*
5
99999 5 12 5 5
5 99999 9 7 8
12 9 99999 9 16
5 7 9 99999 8
5 8 16 8 99999
*/
