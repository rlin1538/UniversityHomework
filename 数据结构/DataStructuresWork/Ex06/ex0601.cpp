#include <iostream>
#define OK 1
#define OVERFLOW 0
#define ERROR 0
#define INFINITY 999999 //自定义一个无穷大
#define MAX_V 20
using namespace std;

int sum = 0;           //遍历计数
int flag[MAX_V] = {0}; //顶点遍历标记

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
    int GraphKind;          //图类型，0无向图，1有向图，2为无向网，3有向网
};
//初始化和销毁操作
int CreateGraph(MGraph &G) //创建图
{
    int v, w;   //两点编号
    int weight; //边的权重
    cout << "输入图类型(0无向图，1有向图，2为无向网，3有向网)：";
    cin >> G.GraphKind;
    cout << "输入图顶点个数及边的个数：";
    cin >> G.vexnum >> G.arcnum;
    cout << "输入" << G.vexnum << "个顶点的元素值:";
    for (int i = 0; i < G.vexnum; i++) //输入顶点信息
    {
        G.vexs[i].code = i;
        cin >> G.vexs[i].value;
    }
    for (int i = 0; i < MAX_V; i++) //邻接矩阵初始化
        for (int j = 0; j < MAX_V; j++)
            if (G.GraphKind == 1 || G.GraphKind == 0) //有向图和无向图初始化为0
                G.arcs[i][j] = 0;
            else
                G.arcs[i][j] = INFINITY; //网初始化为无穷大
    if (G.GraphKind == 0 || G.GraphKind == 1)
    {
        for (int i = 0; i < G.arcnum; i++)
        {
            cout << "输入边(即两点编号)：";
            cin >> v >> w;
            G.arcs[v][w] = 1;
            if (G.GraphKind == 0)
                G.arcs[w][v] = 1;
        }
    }
    else
    {
        for (int i = 0; i < G.arcnum; i++)
        {
            cout << "输入边(即两点编号)及其权重：";
            cin >> v >> w >> weight;
            G.arcs[v][w] = weight;
            if (G.GraphKind == 2)
                G.arcs[w][v] = weight;
        }
    }
    return OK;
}
int DestroyGraph(MGraph &G) //删除图
{
    for (int i = 0; i < G.vexnum; i++) //邻接矩阵清空
        for (int j = 0; j < G.vexnum; j++)
            if (G.GraphKind == 1 || G.GraphKind == 0) //有向图和无向图为0
                G.arcs[i][j] = 0;
            else
                G.arcs[i][j] = INFINITY; //网初始化为无穷大
    G.arcnum = G.vexnum = 0;             //顶点和边清零
    return OK;
}
//访问型操作
int GetVex(MGraph G, int V_num) //获取第V_num个顶点的元素值
{
    if (G.vexnum)
    {
        return G.vexs[V_num].value;
        return OK;
    }
    return ERROR;
}
int FirstAdjVex(MGraph G, int V_num) //获取第V_num个顶点的第一个邻接点
{
    if (G.vexnum)
    {
        for (int i = 0; i < G.vexnum; i++)
        {
            if (G.arcs[V_num][i] && G.arcs[V_num][i] != INFINITY)
                return i;
        }
    }
    return -1;
}
int NextAdjVex(MGraph G, int v_num, int w_num) //获取第V_num个顶点在w_num之后的一个邻接点
{
    if (G.vexnum && (G.arcs[v_num][w_num] && G.arcs[v_num][w_num] != INFINITY)) //图存在且v与w的确相邻
    {
        if (w_num == G.vexnum - 1)
            return -1; //w是v的最后一个点，返回空
        for (int i = w_num + 1; i < G.vexnum; i++)
        {
            if (G.arcs[v_num][i] && G.arcs[v_num][i] != INFINITY)
                return i;
        }
    }
    return -1;
}
void DFSTraverse(MGraph G, int cur) //深度优先遍历
{
    cout << G.vexs[cur].value << '\t'; //访问输出
    flag[cur] = 1;
    sum++;
    if (sum == G.vexnum)
        return;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (flag[i] == 0 && G.arcs[cur][i] && G.arcs[cur][i] != INFINITY)
        {
            DFSTraverse(G, i);
        }
    }
}
void BFSTraverse(MGraph G, int cur) //广度优先遍历
{
    int q[MAX_V];    //队列
    int front, rear; //队头队尾指针
    int p;           //

    for (int i = 0; i < G.vexnum; i++) //标记数组清零
        flag[i] = 0;

    front = rear = 0;
    q[rear] = cur; //cur顶点入队
    flag[cur] = 1;
    rear = (rear + 1) % MAX_V;
    while (front < rear)
    {
        p = q[front];
        cout << G.vexs[p].value << '\t'; //访问输出
        front = (front + 1) % MAX_V;     //队头出队
        for (int i = 0; i < G.vexnum; i++)
        {
            if (flag[i] == 0 && G.arcs[p][i] && G.arcs[p][i] != INFINITY)
            {
                q[rear] = i;
                rear = (rear + 1) % MAX_V;
                flag[i] = 1;
            }
        }
    }
}
//加工型操作
int InsertVex(MGraph &G, int v_value) //插入顶点
{
    if (G.vexnum)
    {
        G.vexs[G.vexnum].code = G.vexnum;
        G.vexs[G.vexnum].value = v_value;
        G.vexnum++;
        return OK;
    }
    return ERROR;
}
int InsertArc(MGraph &G, int v_num, int w_num) //插入边
{
    int weight = 1;

    if (G.vexnum)
    {
        G.arcnum++;
        if (G.GraphKind == 2 || G.GraphKind == 3) //若为网则需输入权值
        {
            cout << "输入该边权重：";
            cin >> weight;
            G.arcs[v_num][w_num] = weight;
        }
        else //否则为无向图或有向图
        {
            G.arcs[v_num][w_num] = weight;
        }
        if (G.GraphKind == 0 || G.GraphKind == 2) //若为无向图则需对称赋值
            G.arcs[w_num][v_num] = 1;
        return OK;
    }
    return ERROR;
}
int DeleteVex(MGraph &G, int v_num) //删除顶点
{
    int count = 0;
    if (G.vexnum)
    {
        for (int i = 0; i < G.vexnum; i++)
        {
            if (G.arcs[v_num][i] && G.arcs[v_num][i] != INFINITY) //计边数
                count++;
            if ((G.GraphKind == 1 || G.GraphKind == 3) && G.arcs[i][v_num] && G.arcs[i][v_num] != INFINITY) //计有向图额外边数
                count++;
        }
        for (int i = v_num + 1; i < G.vexnum; i++)
        {
            G.vexs[i - 1].value = G.vexs[i].value; //顶点编号更新
            for (int j = 0; j < G.vexnum; j++)     //删除列
                G.arcs[i - 1][j] = G.arcs[i][j];
        }
        for (int j = v_num + 1; j < G.vexnum; j++)
        {
            for (int i = 0; i < G.vexnum - 1; i++) //删除行
                G.arcs[i][j - 1] = G.arcs[i][j];
        }
        G.arcnum -= count;
        G.vexnum--; //顶点数-1
        return OK;
    }
    return ERROR;
}
int DeleteArc(MGraph &G, int v_num, int w_num) //删除边
{
    if (G.vexnum)
    {
        if (G.GraphKind == 0 || G.GraphKind == 1)
        {
            G.arcs[v_num][w_num] = 0;
            if (G.GraphKind == 0)
                G.arcs[w_num][v_num] = 0;
        }
        else
        {
            G.arcs[v_num][w_num] = INFINITY;
            if (G.GraphKind == 2)
                G.arcs[w_num][v_num] = INFINITY;
        }
        G.arcnum--;
        return OK;
    }
    return ERROR;
}

int menu_sel() //测试菜单
{
    char *m[12] = {(char *)"1.创建图",
                   (char *)"2.删除图",
                   (char *)"3.获取顶点元素",
                   (char *)"4.查找顶点v首个邻接点",
                   (char *)"5.查找顶点v相对w的首个邻接点",
                   (char *)"6.深度优先遍历",
                   (char *)"7.广度优先遍历",
                   (char *)"8.插入顶点",
                   (char *)"9.插入边",
                   (char *)"10.删除顶点",
                   (char *)"11.删除边",
                   (char *)"0.退出"};
    int i, choice;
    do
    {
        system("cls");
        cout << "-------主菜单-------" << endl;
        for (i = 0; i < 12; i++)
            cout << m[i] << endl;
        cout << "请输入选择：";
        cin >> choice;
    } while (choice < 0 || choice > 11);
    return choice;
}

int main()
{
    MGraph G;
    int sel, temp;
    int v, w;

    for (;;)
    {
        switch (sel = menu_sel())
        {
        case 1:
            CreateGraph(G);
            system("pause");
            break;
        case 2:
            DestroyGraph(G);
            system("pause");
            break;
        case 3:
            cout << "输入元素编号:";
            cin >> v;
            cout << "元素值为：" << GetVex(G, v) << endl;
            system("pause");
            break;
        case 4:
            cout << "输入元素编号:";
            cin >> v;
            temp = FirstAdjVex(G, v);
            if (temp >= 0)
                cout << "首个邻接点编号为：" << temp << endl;
            else
                cout << "邻接点为空" << endl;
            system("pause");
            break;
        case 5:
            cout << "输入元素v、w编号:";
            cin >> v >> w;
            temp = NextAdjVex(G, v, w);
            if (temp >= 0)
                cout << "相对首个邻接点编号为：" << temp << endl;
            else
                cout << "无" << endl;
            system("pause");
            break;
        case 6:
            cout << "深度优先遍历为：";
            for (int i = 0; i < G.vexnum; i++) //标记数组清零
                flag[i] = 0;
            sum = 0; //清零
            DFSTraverse(G, 0);
            cout << endl;
            system("pause");
            break;
        case 7:
            cout << "广度优先遍历：";
            BFSTraverse(G, 0);
            cout << endl;
            system("pause");
            break;
        case 8:
            cout << "输入新顶点元素值：";
            cin >> v;
            if (InsertVex(G, v))
                cout << "插入成功" << endl;
            else
                cout << "插入失败" << endl;
            //cout << G.vexnum << '\t' << G.arcnum << endl;
            system("pause");
            break;
        case 9:
            cout << "输入顶点v、w编号:";
            cin >> v >> w;
            if (InsertArc(G, v, w))
                cout << "插入成功" << endl;
            else
                cout << "插入失败" << endl;
            //cout << G.vexnum << '\t' << G.arcnum << endl;
            system("pause");
            break;
        case 10:
            cout << "输入删除的顶点编号:";
            cin >> v;
            if (DeleteVex(G, v))
                cout << "删除成功" << endl;
            else
                cout << "删除失败" << endl;
            //cout << G.vexnum << '\t' << G.arcnum << endl;
            system("pause");
            break;
        case 11:
            cout << "输入删除的边:";
            cin >> v >> w;
            if (DeleteArc(G, v, w))
                cout << "删除成功" << endl;
            else
                cout << "删除失败" << endl;
            //cout << G.vexnum << '\t' << G.arcnum << endl;
            system("pause");
            break;
        case 0:
            break;
        }
        if (sel == 0)
            break;
    }
}