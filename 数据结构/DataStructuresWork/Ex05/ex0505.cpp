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
    int n;     //����n����
    int c = 0; //��Ǽ��ұ���0��1��2��3
    int i = 1; //ÿ�α���������1��ʼ

    cin >> n;
    while (n) //��n��������ʱѭ��
    {
        c %= 4;        //����cΪ0��1��2��3
        if (jump(i++)) //���iΪҪ��������
        {
            ans[c++]++; //��c���������Ĵ���+1��c++������һ����
            continue;
        }
        n--; //ʣ�౨������-1
        c++; //��һ����
    }
    for (int i = 0; i < 4; i++)
        cout << ans[i] << endl;
}