#include <iostream>
using namespace std;

int main()
{
    int n;                               //人员数
    int k;                               //逗留标准
    int t;                               //位置记录条数
    int x, y;                            //存放某个点
    int xl, yd, xr, yu;                  //存放高危区域
    int flagG = 0, flagS = 0, count = 0; //经过标记、逗留标记、停留计数
    int ansG = 0, ansS = 0;              //结果

    cin >> n >> k >> t >> xl >> yd >> xr >> yu;
    for (int i = 0; i < n; i++)
    {
        flagG = 0;
        flagS = 0;
        count = 0;
        for (int j = 0; j < t; j++)
        {
            cin >> x >> y;
            if ((xl <= x && x <= xr) && (yd <= y && y <= yu)) //如果位于高危区域
            {
                flagG = 1;      //标记经过
                count++;        //停留计数
                if (count >= k) //如果停留时间超过k
                    flagS = 1;  //标记逗留
            }
            else
            {
                count = 0; //停留中断
            }
        }
        if (flagG)
            ansG++;
        if (flagS)
            ansS++;
    }
    cout << ansG << endl;
    cout << ansS << endl;
}