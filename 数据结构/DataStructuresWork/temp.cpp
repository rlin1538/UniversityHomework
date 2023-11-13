#include <iostream>
#define INFINITY 99999 //自定义一个无穷大
#define MAX_V 20       //最大顶点个数
using namespace std;
//求最小生成树并将其存储到邻接矩阵T中
int Prim(int G[MAX_V][MAX_V], int n, int T[MAX_V][MAX_V])
{
    int flag[MAX_V] = {0};
    int dis[MAX_V];
    int path[MAX_V];
    int min, temp, ans = 0;

    flag[0] = 1;
    for (int i = 0; i < n; i++) //第一个点开始更新dis
    {
        dis[i] = G[0][i];
        if (dis[i] < INFINITY)
            path[i] = 0;
        else
            path[i] = -1;
    }
    for (int i = 0; i < n - 1; i++)
    {
        min = INFINITY;
        for (int j = 0; j < n; j++)
        {
            if (flag[j] == 0 && dis[j] < min)
            {
                min = dis[j];
                temp = j;
            }
        }
        //ans += min;
        flag[temp] = 1;
        for (int j = 0; j < n; j++)
        {
            if (flag[j] == 0 && G[temp][j] < INFINITY)
                if (G[temp][j] < dis[j])
                {
                    dis[j] = G[temp][j];
                    path[j] = temp;
                }
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (path[j] == i)
            {
                T[i][j] = G[i][j];
                T[j][i] = G[j][i];
            }
    for (int i = 0; i < n; i++)
		{for (int j = 0; j < n; j++)
		cout<<T[i][j]<<'\t';
		cout<<endl;
		}
    //测试最小生成树
}
int main()
{
    int G[MAX_V][MAX_V];   //邻接矩阵
    int T[MAX_V][MAX_V]={0};
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) //邻接矩阵初始化
        for (int j = 0; j < n; j++)
            cin >> G[i][j];
    Prim(G,n,T);
}