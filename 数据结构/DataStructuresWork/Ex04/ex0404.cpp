#include <iostream>
using namespace std;

int main()
{
    int n;                 //购票指令数量
    int p;                 //指令p
    int i, j, k, l;        //循环变量
    int ans[100][5] = {0}; //每条指令的结果
    int row[20] = {0};     //车厢座位数组，共二十排，其中row[i]表示第i排已占座位数

    cin >> n;
    for (i = 0; i < n; i++) //输入n次指令
    {
        cin >> p; //输入指令p
        for (j = 0; j < 20; j++)
        {
            if ((5 - row[j]) >= p) //如果第j+1排剩余座位足够
            {
                for (k = 0; k < p; k++)
                {
                    ans[i][k] = j * 5 + row[j] + k + 1; //存放选择的座位号
                }
                row[j] += p; //更新row[j][0]
                p = 0;
                break;
            }
        }
        l = 0;
        k = 0;
        while (p) //如果p不为零，即没有连续的座位
        {
            if (l<20 && (5 - row[l])) //如果第l+1排有空位
            {
                ans[i][k] = l * 5 + row[l] + k + 1;   //存放选择的座位号
                k++;
                row[l]++;
                p--;
            }
            else
            {
                l++;    //下一排
            }
        }
    }
    for (i=0;i<n;i++)
    {
        for(j=0;j<5;j++)
        {
            if (ans[i][j]) cout<<ans[i][j]<<'\t';
        }
        cout<<endl;
    }
}