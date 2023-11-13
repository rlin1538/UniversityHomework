//13.【2】消除类游戏    CSP 201512-2	
#include <iostream>
using namespace std;

struct Point
{
    int value;
    int status; //是否可被消除
};

int main()
{
    int n, m, i, j;
    Point map[30][30];
    int last;
    int k;

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j].value;
            map[i][j].status = 0;
        }

    for (i = 0; i < n; i++) //逐行判断有无可消除，并先标记
    {
        k = 1; //连续个数计数
        last = 0;
        for (j = 0; j < m; j++) //判断每一行
        {
            if (map[i][j].value == last)
                k++; //连续出现计数
            else
            {               //连续中止
                if (k >= 3) //判断是否标记
                    for (int l = 0; l < k; l++)
                        map[i][j - l - 1].status = 1;
                k = 1;
            }
            last = map[i][j].value;
        }
        if (k >= 3) //行末判断有无需要标记
            for (int l = 0; l < k; l++)
                map[i][j - l - 1].status = 1;
    }
    for (j = 0; j < m; j++) //逐列判断有无可消除，并先标记
    {
        k = 1; //连续个数计数
        last = 0;
        for (i = 0; i < n; i++) //判断每一列
        {
            if (map[i][j].value == last)
                k++;
            else
            {
                if (k >= 3)
                    for (int l = 0; l < k; l++)
                        map[i - l - 1][j].status = 1;
                k = 1;
            }
            last = map[i][j].value;
        }
        if (k >= 3)
            for (int l = 0; l < k; l++)
                map[i - l - 1][j].status = 1;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            if (map[i][j].status == 0)
                cout << map[i][j].value << ' ';
            else
                cout << 0 << ' ';
        cout << endl;
    }
}