//最小生成树法解TSP问题
#include <iostream>
#include <fstream>
#define START 0        //起始点
#define INFINITY 99999 //自定义一个无穷大
#define MAX_V 20       //最大顶点个数
using namespace std;

int DFS[MAX_V], minDFS[MAX_V];
int visit[MAX_V] = {0}; //标记已走过的数组
int num = 1;            //DFS顺序

//求最小生成树并将其存储到邻接矩阵T中，并加边
void Prim(int G[MAX_V][MAX_V], int n, int T[MAX_V][MAX_V])
{
    int flag[MAX_V] = {0}; //标记已访问的数组
    int dis[MAX_V];        //记录最短距离数组
    int path[MAX_V];       //记录路径数组
    int min, temp, ans = 0;

    flag[0] = 1;                //将第一个顶点标记访问
    for (int i = 0; i < n; i++) //第一个点开始更新dis
    {
        dis[i] = G[0][i];
        if (dis[i] < INFINITY) //初始化路径数组path
            path[i] = 0;
        else
            path[i] = -1;
    }
    for (int i = 0; i < n - 1; i++) //循环n-1次找出最小生成树
    {
        min = INFINITY;
        for (int j = 0; j < n; j++)
        {
            if (flag[j] == 0 && dis[j] < min) //查找最短边
            {
                min = dis[j];
                temp = j; //记录最短边temp
            }
        }
        flag[temp] = 1; //标记走过
        for (int j = 0; j < n; j++)
        {
            if (flag[j] == 0 && G[temp][j] < INFINITY) //更新dis数组
                if (G[temp][j] < dis[j])
                {
                    dis[j] = G[temp][j];
                    path[j] = temp;
                }
        }
    }

    for (int i = 0; i < n; i++) //生成最小生成树，并加边
        for (int j = 0; j < n; j++)
            if (path[j] == i)
            {
                T[i][j] = G[i][j];
                T[j][i] = G[j][i]; //加边
            }
}
//生成DFS数组和minDFS数组用以判断桥
int Tarjan(int G[MAX_V][MAX_V], int cur, int n)
{
    int temp;            //临时变量
    if (visit[cur] == 1) //边界
        return minDFS[cur];
    num++;
    DFS[cur] = num;    //标上第cur个顶点的DFS
    minDFS[cur] = num; //标上第cur个顶点的初始minDFS
    visit[cur] = 1;    //标记已访问
    for (int i = 0; i < n; i++)
    {
        if (G[cur][i] < INFINITY)
        {
            temp = Tarjan(G, i, n); //深搜
            if (temp < minDFS[cur]) //回溯更新minDFS
                minDFS[cur] = temp;
        }
    }
    return minDFS[cur]; //返回minDFS
}
//判断第i个顶点到第j个顶点是否为桥
bool JudgeBridge(int i, int j)
{
    if (minDFS[j] > DFS[i])
        return true;
    else
        return false;
}
//求欧拉回路，将回路顶点访问顺序存入E数组，start为出发点
void Fleury(int T[MAX_V][MAX_V], int n, int E[2 * MAX_V], int start)
{
    int cur = start;     //当前点
    int G[MAX_V][MAX_V]; //复制一遍T
    int k = 0;           //欧拉回路访问顶点计数
    int bridge;          //记录查到的桥

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            G[i][j] = T[i][j];            //复制T矩阵
    E[k++] = start;                       //将始点记录进欧拉回路
    for (int i = 0; i < (n - 1) * 2; i++) //共走（n-1）*2条边
    {
        num = 0;
        for (int l = 0; l < n; l++) //初始化各数组
        {
            visit[l] = 0;
            DFS[l] = INFINITY;
            minDFS[l] = INFINITY;
        }
        Tarjan(G, cur, n);          //用Tarjan算法查一遍桥
        for (int j = 0; j < n; j++) //查找可走的边
        {
            if (G[cur][j] < INFINITY)
                if (JudgeBridge(cur, j) == false) //判断是否为桥
                {
                    G[cur][j] = INFINITY; //不是桥的话直接走
                    E[k++] = j;
                    cur = j;
                    break; //进入下一条边
                }
                else
                    bridge = j; //记录这个桥
            if (j == n - 1)     //如果只剩桥可走
            {
                G[cur][bridge] = INFINITY; //走桥
                E[k++] = bridge;
                cur = bridge;
            }
        }
    }
}
//查找最短路，start为出发城市
int *TSP(int M[MAX_V][MAX_V], int n, int start)
{
    int T[MAX_V][MAX_V];
    int E[2 * MAX_V];      //欧拉回路
    int *H;                //哈密顿回路
    int flag[MAX_V] = {0}; //标记已走过
    int last;
    int k = 0;
    int ans = 0;

    H = new int[n + 1];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            T[i][j] = INFINITY; //初始化最小生成树T数组
    Prim(M, n, T);              //生成最小生成树
    Fleury(T, n, E, start);     //寻找欧拉回路,以第一个输入的点为出发点

    //沿着欧拉回路抄近路查找哈密顿回路
    flag[E[0]] = 1;
    H[k++] = E[0];
    last = E[0]; //记录始点到E数组
    for (int i = 1; i < 2 * n - 1; i++)
    {
        if (flag[E[i]] == 0) //如果未访问过执行，如果已访问过就跳过
        {
            flag[E[i]] = 1;
            H[k++] = E[i];
            ans += M[last][E[i]];
            last = E[i];
        }
    }
    H[n] = H[0];
    ans += M[last][H[0]];
    //输出
    cout << "最短路长：" << ans << endl;
    return H;
}

int main()
{
    int M[MAX_V][MAX_V]; //邻接矩阵
    int n;               //城市个数
    int *H;
    fstream G;

    G.open("matrix.txt");
    G >> n;
    for (int i = 0; i < n; i++) //邻接矩阵初始化
        for (int j = 0; j < n; j++)
        {
            G >> M[i][j];
        }
    cout << "当前邻接矩阵为：" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << M[i][j] << '\t';
        cout << endl;
    }

    H = new int[n + 1];
    H = TSP(M, n, START);
    cout << "路径为：";
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
