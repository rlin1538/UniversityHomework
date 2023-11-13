#include <iostream>
using namespace std;

bool jump(int i)
{
    if (i % 7 == 0)
        return true;
    while (i)
    {
        if (i % 10 == 7)
            return true;
        i /= 10;
    }
    return false;
}

int main()
{
    int ans[4] = {0};
    int n;     //共报n个数
    int c = 0; //标记甲乙丙丁0、1、2、3
    int i = 1; //每次报的数，从1开始

    cin >> n;
    while (n) //当n不等于零时循环
    {
        c %= 4;        //控制c为0、1、2、3
        if (jump(i++)) //如果i为要跳过的数
        {
            ans[c++]++; //第c个人跳过的次数+1，c++进入下一个人
            continue;
        }
        n--; //剩余报数次数-1
        c++; //下一个人
    }
    for (int i = 0; i < 4; i++)
        cout << ans[i] << endl;
}