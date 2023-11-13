//22.【3】最小二叉树
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#define START 0        //起始点
#define INFINITY 99999 //自定义一个无穷大
#define MAX_V 20       //最大顶点个数
#define MAX_E 100      //最大边数量
using namespace std;

struct edge //边
{
    int i;
    int j;
    float w;
};

edge edg[MAX_E];
int visit[MAX_V] = {0}; //标记已走过的数组
string G_name[MAX_V];   //顶点信息
int f[MAX_V];
int n, m;

//求最小生成树并将其存储到邻接矩阵T中
void Prim(float G[MAX_V][MAX_V]) //, int T[MAX_V][MAX_V]
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
        ans += min;
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

    /*for (int i = 0; i < n; i++) //生成最小生成树
        for (int j = 0; j < n; j++)
            if (path[j] == i)
            {
                T[i][j] = G[i][j];
                T[j][i] = G[j][i]; //加边
            }*/
    cout << "Prim算法最小生成树权重和：" << ans << endl;
}

int getfather(int a) //并查集找父亲
{
    if (f[a] == a)
        return a;
    else
    {
        f[a] = getfather(f[a]);
        return f[a];
    }
}

bool merge(int a, int b) //并查集合并两子集
{
    int f1, f2;
    f1 = getfather(a);
    f2 = getfather(b);

    if (f1 != f2) //如果两者没有共同祖先
    {
        f[f2] = f1;  //合并
        return true; //返回true表示可以合并
    }
    return false; //否则有共同祖先，返回false
}
bool cmp(edge a, edge b)
{
    return a.w < b.w;
}
void Kruskal()
{
    int count = 0; //边计数
    int ans = 0;
    edge *path;
    path = new edge[n - 1];

    sort(edg, edg + m, cmp);    //对边集排序
    for (int i = 0; i < n; i++) //查并集初始化
        f[i] = i;

    for (int i = 0; i < m; i++)
    {
        if (merge(edg[i].i, edg[i].j)) //可以合并
        {
            path[count] = edg[i];
            count++;
            ans += edg[i].w;
        }
        if (count == n - 1)
            break;
    }
    cout << "Kruskal算法最小生成树权重和：" << ans << endl;
    cout << "\n该最小生成树所用边为：" << endl;
    for (int i = 0; i < n - 1; i++)
        cout << G_name[path[i].i] << "<--->" << G_name[path[i].j] << "\t权重" << path[i].w << endl;
}

void Read(float G[MAX_V][MAX_V])
{
    ifstream fin("matrix.txt");

    fin >> n;
    for (int i = 0; i < n; i++)
        fin >> G_name[i];
    for (int i = 0; i < n; i++) //邻接矩阵初始化
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
    cout << "当前邻接矩阵为：" << endl;
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
    float G[MAX_V][MAX_V]; //邻接矩阵

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
