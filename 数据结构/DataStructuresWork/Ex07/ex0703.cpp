#include <iostream>
using namespace std;

bool judgewin(int G[3][3], int chess) //�жϵ�ǰ�����Ƿ�chessʤ��
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
int score(int G[3][3], int chess) //ͳ�Ƶ÷�
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
int continueplay(int G[3][3], int chess) //��������,chessΪ���巽
{
    //���ѵ�˼�룬�ҵ�ÿ���˵÷����ֵ
    int temp;
    if (score(G, chess) == 1 || score(G, chess) == -1) //ƽ�֣�ֱ�ӷ���
        return 0;

    int maxscore = -99999;  //A������
    int minscore = 99999;   //B�����֣�������С��

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++) //���������еĵ�
        {
            if (G[i][j] == 0)   //�������������
            {
                G[i][j] = chess;    //����
                if (judgewin(G, chess)) //���chess����ʤ
                {
                    temp = score(G, chess); //��¼�÷�
                    G[i][j] = 0;        //����
                    if (temp > 0)       //�ж���˭�÷�
                        return temp > maxscore ? temp : maxscore;   //�������ĵ÷�
                    else
                        return temp < minscore ? temp : minscore;
                }
                if (chess == 1) //�����ǰ��A����
                {
                    temp = continueplay(G, chess % 2 + 1);  //Ѱ��A�ĵ÷����ֵ
                    if (temp > maxscore)
                        maxscore = temp;
                }
                else    //����ΪB����
                {
                    temp = continueplay(G, chess % 2 + 1);  //Ѱ��B�ĵ÷����ֵ(������С)
                    if (temp < minscore)
                        minscore = temp;
                }
                G[i][j] = 0;    //����
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