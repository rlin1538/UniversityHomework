#include <iostream>
using namespace std;

bool judge(int M[15][10], int A[4][4], int k, int d) //判断板块A在第k列下降d行后是否能放置
{
    for (int i = d; i < d + 4; i++)
        for (int j = k - 1; j < k + 3; j++)
            if (A[i - d][j - k + 1])
                if (M[i][j])
                    return false;
    return true;
}

int main()
{
    int M[16][10]; //方格图
    int A[4][4];   //板块
    int k;         //板块列位置
    int c = 1;     //计数下降行数

    for (int i = 0; i < 15; i++) //输入方格图
        for (int j = 0; j < 10; j++)
            cin >> M[i][j];
    for (int i = 0; i < 10; i++) //将方格图底部封上
        M[15][i] = 1;
    for (int i = 0; i < 4; i++) //输入板块
        for (int j = 0; j < 4; j++)
            cin >> A[i][j];
    cin >> k;                 //输入板块列位置
    while (judge(M, A, k, c)) //模拟板块下落进行判断
        c++;
    c--;
    for (int i = c; i < c + 4; i++) //更新方格图
        for (int j = k - 1; j < k + 3; j++)
            if (A[i - c][j - k + 1])
                M[i][j] = 1;
    for (int i = 0; i < 15; i++) //输出方格图
    {
        for (int j = 0; j < 10; j++)
            cout << M[i][j] << " ";
        cout << endl;
    }
}