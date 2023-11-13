#include <iostream>
#include <string>
#include <fstream>
#define OK 1
#define MAX_V 20
#define vexNum 5  //顶点数
#define arcNum 10 //边数
using namespace std;
#define MAX_V 20 //最大顶点数
/*
typedef struct
{
    int code;  //顶点编号
    char name; //顶点名字
} vertexType;

typedef struct
{
    int arcs[MAX_V][MAX_V]; //邻接矩阵
    int weight[vexNum][vexNum];
    vertexType vexs[MAX_V]; //顶点信息
} mGraph;

//创建无向图
void create_graph(mGraph &G)
{
    int i, j;
    for (i = 0; i < vexNum; i++)
    {
        G.vexs[i].code = i; //顶点编号初始化
    }
    G.vexs[0].name = 'A';
    G.vexs[1].name = 'B';
    G.vexs[2].name = 'C';
    G.vexs[3].name = 'D';
    G.vexs[4].name = 'E'; //自定义各点的编号
    G.weight[0][1] = 5;
    G.weight[1][0] = 5;
    G.weight[0][2] = 12;
    G.weight[2][0] = 12;
    G.weight[0][3] = 5;
    G.weight[3][0] = 5;
    G.weight[0][4] = 5;
    G.weight[4][0] = 5;
    G.weight[1][2] = 9;
    G.weight[2][1] = 9;
    G.weight[1][3] = 7;
    G.weight[3][1] = 7;
    G.weight[1][4] = 8;
    G.weight[4][1] = 8;
    G.weight[2][3] = 9;
    G.weight[3][2] = 9;
    G.weight[2][4] = 16;
    G.weight[4][2] = 16;
    G.weight[3][4] = 8;
    G.weight[4][3] = 8;
    for (int i = 0; i < vexNum; i++)
    {
        G.weight[i][i] = 666;
    } ////初始化各边权值（以ppt中的为例）
    for (i = 0; i < vexNum; i++)
        for (j = 0; j < vexNum; j++)
            G.arcs[i][j] = 0; //无向图邻接矩阵初始化
    for (i = 0; i < arcNum; i++)
    {
        for (j = 0; j < arcNum; j++)
        {
            if (i == j)
                G.arcs[i][j] = 0; //将不存在边的邻接矩阵对应值设为0
            else
                G.arcs[i][j] = 1; //将存在边的邻接矩阵对应值设为1
        }
    }
}*/

int main()
{
    ofstream out("FamilyTree.txt");
    string s="王磊,已故,1870.5.2-1900.11.3\n 王旭浩,已故,1890.11.3-1940.7.8\n  王鸣,已故,1921.3.22-1967.4.4\n   王文方,已故,1950.7.9-1952.7.18\n   王文远,已故,1952.12.12-1999.4.3\n    王信,健在,1974.11.12-\n     王博仁,健在,1995.9.14-\n      王圣君,健在,2020.1.2-\n  王翰涛,已故,1923.11.10-1980.9.3\n   王柏,已故,1950.10.14-\n    王文博,已故,1974.6.7-     王汉源,已故,1997.11.9-\n     王汉智,已故,1998.6.5-\n  王乙玄,已故,1908.4.1-1933.2.4\n   王江潮,已故,1927.10.18-1999.9.9\n    王博远,健在,1949.10.1-\n     王栋,健在,1980.9.15-\n     王为民,健在,1984.4.13-\n    王博帆,已故,1951.7.8-2019.4.3\n     王鼎晖,健在,1977.5.8-\n    王博智,健在,1952..30-\n     王超,健在,1982.9.9-\n   王镇,已故,1930.9.5-1967.12.13\n    王泰恒,健在,1951.11.9-\n     王丰源,健在,1977.2.18-\n 王棋天,已故,1892.1.4-1944.8.9\n  王景飞,已故,1910.11.11-1945.8.12\n  王景逸,已故,1915.4.2-1970.12.31\n   王浩,已故,1940.8.7-2005.3.9\n    王亮德,健在,1963.10.18-\n     王谷,健在,1983.3.18-\n     王壬泰,健在,1990.3.3-\n      王营,健在,2018.3.18-\n   王功,健在,1950.7.4-\n    王安,已故,1977.8.11-2000.3.4\n     王子轩,健在,2007.8.11-\n  王源,已故,1922.8.2-1980.2.6\n   王宏宇,已故,1944.9.7-1954..12.11\n   王子晨,已故,1942.1.8-1972.5.8\n    王时易,已故,1967.2.4-1973.9.9\n 王晋辰,已故,1900.7.7-1955.2.3";
    int x;
    char y;
    cin>>x>>y;
    cout<<x<<' '<<y;
    //cout<<char(156);
    /*//string s="你电话";
    char *s;
    s=new char[20];
    for (int i = 0; i < 20; i+=2)
    {
        cin>>s[i]>>s[i+1];
    }
    
    cout<<s;*/

    /*mGraph G;
    create_graph(G);
    int visit[5] = {0};
    visit[0] = 1;
    cout << "从A出发的用最邻近法求得的近似解为：" << G.vexs[0].name;
    int t = 0, q = 0, sum = 0;
    int temp = 666;
    for (q; q < vexNum - 1; q++)
    {int i = t;
        t = 0;
        for (int j = 0; j < vexNum; j++)
        {
            if (!visit[j] && G.weight[i][j] < temp)
            {
                temp = G.weight[i][j];
                visit[j] = 1;
                if (t)
                    visit[t] = 0;
                else
                    ;
                t = j;
            }
            else
                continue;
        }
        sum += temp;
        cout << G.vexs[t].name<<"("<<temp<<")";
        //q = 0;
        temp = 666;
        if (q == 3)
            sum += G.weight[t][0];
    }
    cout << endl;
    cout << "此近似解的权值之和为：" << sum << endl;*/
    return 0;
}