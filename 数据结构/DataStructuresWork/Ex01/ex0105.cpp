#include <iostream>
using namespace std;

int main()
{
    int i = 0;     //��Ծ����
    int score = 0; //�÷�
    int cur;       //��ǰ��Ծ���
    int por;       //��һ����Ծ�÷�

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