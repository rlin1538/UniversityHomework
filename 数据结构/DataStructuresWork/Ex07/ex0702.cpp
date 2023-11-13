//基于邻接矩阵的Dijkastra算法(单源查找最短路径)
#include <iostream>
#define OK 1
#define OVERFLOW 0
#define ERROR 0
#define INFINITY 999999 //自定义一个无穷大
#define MAX_V 20
using namespace std;

struct VertexType
{
    int code;  //顶点编号
    int value; //顶点元素值
};

struct MGraph
{
    int arcs[MAX_V][MAX_V]; //邻接矩阵
    int vexnum, arcnum;     //顶点数、边数
    VertexType vexs[MAX_V]; //顶点信息
    int GraphKind;          //图类型，本题以有向网为例
};
//初始化和销毁操作
int CreateGraph(MGraph &G) //创建有向网
{
    int v, w;   //两点编号
    int weight; //边的权重
    cout << "输入有向网顶点个数及边的个数：";
    cin >> G.vexnum >> G.arcnum;
    cout << "输入" << G.vexnum << "个顶点信息:";
    for (int i = 0; i < G.vexnum; i++) //输入顶点信息
    {
        G.vexs[i].code = i;
        cin >> G.vexs[i].value;
    }
    for (int i = 0; i < MAX_V; i++) //邻接矩阵初始化
        for (int j = 0; j < MAX_V; j++)
            G.arcs[i][j] = INFINITY; //网初始化为无穷大
    for (int i = 0; i < G.arcnum; i++)
    {
        cout << "输入边(即两点编号)及其权重：";
        cin >> v >> w >> weight;
        G.arcs[v][w] = weight;
    }
    return OK;
}

void Dijkastra(MGraph G, int cur) //Dijikastra算法,cur为出发点编号
{
    int dis[MAX_V];   //记录最短距离
    int path[MAX_V];  //记录路径
    bool flag[MAX_V]; //顶点遍历标记
    int min = INFINITY;
    int temp;

    for (int i = 0; i < G.vexnum; i++) //第一轮查找
    {
        flag[i] = false;
        dis[i] = G.arcs[cur][i];
        if (dis[i] < INFINITY)
            path[i] = cur;
        else
            path[i] = -1;
    }
    dis[cur] = 0;                          //标记自身距离为0
    flag[cur] = true;                      //标记已走过
    for (int i = 0; i < G.vexnum - 1; i++) //搜索最短路
    {
        min = INFINITY;
        for (int j = 0; j < G.vexnum; j++)
            if (flag[j] == false && dis[j] < min)
            {
                min = dis[j];
                temp = j;
            }
        flag[temp] = true;
        if (min == INFINITY)
            continue;
        for (int j = 0; j < G.vexnum; j++)
        {
            if (flag[j] == false && G.arcs[temp][j] < INFINITY)
                if (G.arcs[temp][j] + min < dis[j])
                {
                    dis[j] = G.arcs[temp][j] + min;
                    path[j] = temp;
                }
        }
    }
    cout << "dis数组为：";
    for (int i = 0; i < G.vexnum; i++)
        cout << dis[i] << '\t';
    cout << endl
         << "path数组为：";
    for (int i = 0; i < G.vexnum; i++)
        cout << path[i] << '\t';
}

int main()
{
    MGraph G;
    CreateGraph(G);
    Dijkastra(G, 0);
}