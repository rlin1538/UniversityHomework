#include <iostream>
#define INFINITY 99999 //�Զ���һ�������
#define MAX_V 20       //��󶥵����
using namespace std;
//����С������������洢���ڽӾ���T��
int Prim(int G[MAX_V][MAX_V], int n, int T[MAX_V][MAX_V])
{
    int flag[MAX_V] = {0};
    int dis[MAX_V];
    int path[MAX_V];
    int min, temp, ans = 0;

    flag[0] = 1;
    for (int i = 0; i < n; i++) //��һ���㿪ʼ����dis
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
    //������С������
}
int main()
{
    int G[MAX_V][MAX_V];   //�ڽӾ���
    int T[MAX_V][MAX_V]={0};
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) //�ڽӾ����ʼ��
        for (int j = 0; j < n; j++)
            cin >> G[i][j];
    Prim(G,n,T);
}