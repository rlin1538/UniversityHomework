#include <iostream>
using namespace std;

int main()
{
    int n;                 //��Ʊָ������
    int p;                 //ָ��p
    int i, j, k, l;        //ѭ������
    int ans[100][5] = {0}; //ÿ��ָ��Ľ��
    int row[20] = {0};     //������λ���飬����ʮ�ţ�����row[i]��ʾ��i����ռ��λ��

    cin >> n;
    for (i = 0; i < n; i++) //����n��ָ��
    {
        cin >> p; //����ָ��p
        for (j = 0; j < 20; j++)
        {
            if ((5 - row[j]) >= p) //�����j+1��ʣ����λ�㹻
            {
                for (k = 0; k < p; k++)
                {
                    ans[i][k] = j * 5 + row[j] + k + 1; //���ѡ�����λ��
                }
                row[j] += p; //����row[j][0]
                p = 0;
                break;
            }
        }
        l = 0;
        k = 0;
        while (p) //���p��Ϊ�㣬��û����������λ
        {
            if (l<20 && (5 - row[l])) //�����l+1���п�λ
            {
                ans[i][k] = l * 5 + row[l] + k + 1;   //���ѡ�����λ��
                k++;
                row[l]++;
                p--;
            }
            else
            {
                l++;    //��һ��
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