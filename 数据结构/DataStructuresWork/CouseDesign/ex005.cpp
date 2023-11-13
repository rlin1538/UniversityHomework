//5.地铁修建
#include <iostream>
#define INF 999999
using namespace std;

int dis[1000];
bool flag[1000];
int ans = 0;
int n, m;
int G[100][100]; //本地编译器有问题暂时为100*100
int x, y;

void Prim()
{
    int min = INF;
    int temp;

    flag[0] = true;
    for (int i = 0; i < n; i++) //第一个点开始更新dis
        dis[i] = G[0][i];
    for (int i = 0; i < n - 1; i++)
    {
        min = INF;
        for (int j = 0; j < n; j++)
        {
            if (flag[j] == false && dis[j] < min)
            {
                min = dis[j];
                temp = j;
            }
        }
        if (min > ans)
            ans = min;
        flag[temp] = true;
        for (int j = 0; j < n; j++)
        {
            if (flag[j] == false && G[temp][j] < INF)
                if (G[temp][j] < dis[j])
                    dis[j] = G[temp][j];
        }
        if (temp == n - 1)
            cout << ans;
    }
}

int main()
{

    cin >> n >> m;
    for (int i = 0; i < n; i++) //初始化邻接矩阵
    {
        dis[i] = INF;
        flag[i] = false;
        for (int j = 0; j < n; j++)
            G[i][j] = INF;
    }

    for (int i = 0; i < m; i++) //输入边
    {
        cin >> x >> y;
        cin >> G[x - 1][y - 1];
        G[y - 1][x - 1] = G[x - 1][y - 1];
    }

    Prim();
}
/*
样例输入
6 6
1 2 4
2 3 4
3 6 7
1 4 2
4 5 5
5 6 6
样例输出
6
*/