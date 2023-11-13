//基于邻接表的深度优先遍历和广度优先遍历
#include <iostream>
#define MAX_V 20
using namespace std;

bool flag[MAX_V]; //遍历时的标记数组

struct ArcNode //边结点
{
    int adjvex;       //顶点编号
    int weight;       //边权值（网用）
    ArcNode *nextarc; //下一条边的地址
};
struct VexNode
{
    int data;          //顶点信息
    ArcNode *firstarc; //指向第一个边结点
};
struct AlGpraph
{
    VexNode AdjList[MAX_V]; //邻接表
    int vexnum, arcnum;     //顶点数与边数
    int vexs[MAX_V];        //顶点信息
    //GraphKind type    //图类型，本题以无向图为例
};
//创建无向图(以无向图为例)
void CreatGraph(AlGpraph &G)
{
    ArcNode *p;
    int i, j;

    cout << "输入无向图顶点数和边数：";
    cin >> G.vexnum >> G.arcnum;
    cout << "输入顶点信息：";
    for (i = 0; i < G.vexnum; i++)
    {
        cin >> G.vexs[i]; //输入顶点信息
        G.AdjList[i].data = G.vexs[i];
        G.AdjList[i].firstarc = NULL; //初始化邻接表
    }
    for (int k = 0; k < G.arcnum; k++)
    {
        cout << "输入第" << k + 1 << "条边(顶点编号)：";
        cin >> i >> j;
        p = new ArcNode; //创建新边
        p->adjvex = j;   //边终点为j
        p->nextarc = G.AdjList[i].firstarc;
        G.AdjList[i].firstarc = p; //将边接到邻接表相应顶到的链表中
        p = new ArcNode;           //无向图创建对称边
        p->adjvex = i;
        p->nextarc = G.AdjList[j].firstarc;
        G.AdjList[j].firstarc = p;
    }
}

void DFS(AlGpraph G, int cur)
{
    ArcNode *p;
    flag[cur] = true;
    cout << G.vexs[cur] << '\t'; //访问输出
    p = G.AdjList[cur].firstarc; //p指向cur顶点的第一条边
    while (p)
    {
        if (flag[p->adjvex] == false) //该边终点未访问
            DFS(G, p->adjvex);        //递归访问
        p = p->nextarc;               //下一条边
    }
}
//深度优先遍历
void DFS_visit(AlGpraph G)
{
    for (int i = 0; i < G.vexnum; i++)
        flag[i] = false; //标记数组初始化为false表示未访问
    for (int i = 0; i < G.vexnum; i++)
    {
        if (flag[i] == false)
            DFS(G, i);
    }
    cout << endl;
}

void BFS(AlGpraph G, int cur)
{
    ArcNode *p;
    int l;                   //存放出队顶点
    int q[MAX_V];            //队列
    int front = 0, rear = 0; //队头队尾指针

    q[rear++] = cur; //当前顶点入队
    flag[cur] = true;
    while (rear != front)
    {
        l = q[front]; //队头出队
        front = (front + 1) % MAX_V;
        cout << G.vexs[l] << '\t';
        p = G.AdjList[l].firstarc; //将指针指向l的邻接点
        while (p)
        {
            if (flag[p->adjvex] == false)
            {
                q[rear] = p->adjvex; //未访问的点入队
                rear = (rear + 1) % MAX_V;
                flag[p->adjvex] = true;
            }
            p = p->nextarc;
        }
    }
}
//广度优先遍历
void BFS_visit(AlGpraph G)
{
    for (int i = 0; i < G.vexnum; i++)
        flag[i] = false; //标记数组初始化为false表示未访问
    for (int i = 0; i < G.vexnum; i++)
    {
        if (flag[i] == false)
            BFS(G, i);
    }
    cout << endl;
}
int main()
{
    AlGpraph G;

    CreatGraph(G);
    cout << "深度优先遍历：";
    DFS_visit(G);
    cout << "广度优先遍历：";
    BFS_visit(G);

    return 0;
}
