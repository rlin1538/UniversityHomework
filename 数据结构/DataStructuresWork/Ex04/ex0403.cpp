#include <iostream>
using namespace std;

int main()
{
    int n;                               //��Ա��
    int k;                               //������׼
    int t;                               //λ�ü�¼����
    int x, y;                            //���ĳ����
    int xl, yd, xr, yu;                  //��Ÿ�Σ����
    int flagG = 0, flagS = 0, count = 0; //������ǡ�������ǡ�ͣ������
    int ansG = 0, ansS = 0;              //���

    cin >> n >> k >> t >> xl >> yd >> xr >> yu;
    for (int i = 0; i < n; i++)
    {
        flagG = 0;
        flagS = 0;
        count = 0;
        for (int j = 0; j < t; j++)
        {
            cin >> x >> y;
            if ((xl <= x && x <= xr) && (yd <= y && y <= yu)) //���λ�ڸ�Σ����
            {
                flagG = 1;      //��Ǿ���
                count++;        //ͣ������
                if (count >= k) //���ͣ��ʱ�䳬��k
                    flagS = 1;  //��Ƕ���
            }
            else
            {
                count = 0; //ͣ���ж�
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