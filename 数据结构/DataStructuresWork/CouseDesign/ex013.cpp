//13.��2����������Ϸ    CSP 201512-2	
#include <iostream>
using namespace std;

struct Point
{
    int value;
    int status; //�Ƿ�ɱ�����
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

    for (i = 0; i < n; i++) //�����ж����޿����������ȱ��
    {
        k = 1; //������������
        last = 0;
        for (j = 0; j < m; j++) //�ж�ÿһ��
        {
            if (map[i][j].value == last)
                k++; //�������ּ���
            else
            {               //������ֹ
                if (k >= 3) //�ж��Ƿ���
                    for (int l = 0; l < k; l++)
                        map[i][j - l - 1].status = 1;
                k = 1;
            }
            last = map[i][j].value;
        }
        if (k >= 3) //��ĩ�ж�������Ҫ���
            for (int l = 0; l < k; l++)
                map[i][j - l - 1].status = 1;
    }
    for (j = 0; j < m; j++) //�����ж����޿����������ȱ��
    {
        k = 1; //������������
        last = 0;
        for (i = 0; i < n; i++) //�ж�ÿһ��
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