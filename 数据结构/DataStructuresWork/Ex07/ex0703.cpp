#include <iostream>
using namespace std;

bool judgewin(int G[3][3], int chess) //判断当前局面是否chess胜利
{
    for (int i = 0; i < 3; i++)
    {
        if (G[i][0] == chess && G[i][1] == chess && G[i][2] == chess)
            return true;
        if (G[0][i] == chess && G[1][i] == chess && G[2][i] == chess)
            return true;
    }
    if (G[0][0] == chess && G[1][1] == chess && G[2][2] == chess)
        return true;
    if (G[0][2] == chess && G[1][1] == chess && G[2][0] == chess)
        return true;
    return false;
}
int score(int G[3][3], int chess) //统计得分
{
    int a = 1;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (G[i][j] == 0)
                a++;
    if (chess == 1)
        return a;
    else
        return 0 - a;
}
int continueplay(int G[3][3], int chess) //继续下棋,chess为下棋方
{
    //深搜的思想，找到每个人得分最大值
    int temp;
    if (score(G, chess) == 1 || score(G, chess) == -1) //平局，直接返回
        return 0;

    int maxscore = -99999;  //A的最大分
    int minscore = 99999;   //B的最大分（负数最小）

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++) //遍历棋盘中的点
        {
            if (G[i][j] == 0)   //如果这个点可以下
            {
                G[i][j] = chess;    //下子
                if (judgewin(G, chess)) //如果chess方获胜
                {
                    temp = score(G, chess); //记录得分
                    G[i][j] = 0;        //回溯
                    if (temp > 0)       //判断是谁得分
                        return temp > maxscore ? temp : maxscore;   //返回最大的得分
                    else
                        return temp < minscore ? temp : minscore;
                }
                if (chess == 1) //如果当前是A下子
                {
                    temp = continueplay(G, chess % 2 + 1);  //寻找A的得分最大值
                    if (temp > maxscore)
                        maxscore = temp;
                }
                else    //否则为B下子
                {
                    temp = continueplay(G, chess % 2 + 1);  //寻找B的得分最大值(负数最小)
                    if (temp < minscore)
                        minscore = temp;
                }
                G[i][j] = 0;    //回溯
            }
        }
    }
    if (chess == 1)
        return maxscore;
    else
        return minscore;
}

int main()
{
    int n;
    int G[3][3];

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                cin >> G[j][k];
        if (judgewin(G,1))
        {
            cout<<score(G,1)<<endl;
            continue;
        }
        if (judgewin(G,2))
        {
            cout<<score(G,2)<<endl;
            continue;
        }
        cout << continueplay(G, 1)<<endl;
    }
}