#include <iostream>
using namespace std;
void print(int G[3][3])
{
    for (int j = 0; j < 3; j++)
    {    
        for (int k = 0; k < 3; k++)
            cout << G[j][k]<<' ';
        cout <<endl;
    }
    cout<<endl;
}
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
    //print(G);system("pause");
    if (score(G, chess) == 1 || score(G, chess) == -1) //平局
        return 0;

    int maxscore = -99999;
    int minscore = 99999;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (G[i][j] == 0)
            {
                G[i][j] = chess;
                if (judgewin(G, chess))
                {
                    G[i][j] = 0;
                    temp = score(G, chess);
                    if (temp > 0)
                        return temp > maxscore ? temp : maxscore;
                    else
                        return temp < minscore ? temp : minscore;
                }
                if (chess == 1)
                {
                    temp = continueplay(G, chess % 2 + 1);
                    if (temp > maxscore)
                        maxscore = temp;
                }
                else
                {
                    temp = continueplay(G, chess % 2 + 1);
                    if (temp < minscore)
                        minscore = temp;
                }
                G[i][j] = 0;
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