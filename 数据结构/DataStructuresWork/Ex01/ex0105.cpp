#include <iostream>
using namespace std;

int main()
{
    int i = 0;     //跳跃次数
    int score = 0; //得分
    int cur;       //当前跳跃情况
    int por;       //上一次跳跃得分

    cin >> cur;
    i++;
    while (cur)
    {
        if (cur == 1)
        {
            score++;
            por = 1;
        }
        else
        {
            if (por == 1 || i == 1)
            {
                score += 2;
                por = 2;
            }
            else
            {
                por += 2;
                score += por;
            }
        }
        cin >> cur;
        i++;
    }
    cout << score;
    return 0;
}