//最邻近法解TSP问题
#include <iostream>
#include <fstream>
#define START 0        //起始点
#define INFINITY 99999 //自定义一个无穷大
#define MAX_V 20       //最大顶点个数
using namespace std;

int *TSP(int G[MAX_V][MAX_V], int n)
{
    int sum = 1;           //遍历计数
    int ans = 0;           //最短路长
    int flag[MAX_V] = {0}; //顶点遍历标记
    int *path;             //记录路径
    int cur;               //当前处于的点
    int temp;              //临时变量
    int min;               //当前相邻最短边

    path = new int[n + 1];
    flag[START] = 1;
    cur = START;
    path[0] = START; //从第一个顶点出发
    while (sum < n)  //循环n-1次，找出回路
    {
        min = INFINITY;
        for (int i = 0; i < n; i++)
            if (flag[i] == 0 && G[cur][i] < min) //找出距离当前顶点最近的
            {
                temp = i; //记录最近的边temp
                min = G[cur][i];
            }
        ans += min;         //累加最短边
        path[sum++] = temp; //记录路径
        flag[temp] = 1;     //标记已走过
        cur = temp;         //将当前点更新
    }
    path[sum] = START; //回到起点
    ans += G[cur][START];
    cout << "最短路长为：" << ans << endl;

    return path;
}

int main()
{
    int G[MAX_V][MAX_V];
    int *H;
    int n; //顶点个数
    fstream M;

    M.open("matrix.txt"); //从文件读取数据
    M >> n;
    for (int i = 0; i < n; i++) //邻接矩阵初始化
        for (int j = 0; j < n; j++)
            M >> G[i][j];
    cout << "当前邻接矩阵为：" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << G[i][j] << '\t';
        cout << endl;
    }

    H = new int[n + 1];
    H = TSP(G, n);
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