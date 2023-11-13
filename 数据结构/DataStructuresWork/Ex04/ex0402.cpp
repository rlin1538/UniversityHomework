#include <iostream>
#define MAXSIZE 256
using namespace std;

int main()
{
    int A[MAXSIZE][MAXSIZE];
    int m,n;    //m��n��
    int rowmin[MAXSIZE]={0};    //��¼ÿ����Сֵ����λ��
    int colmax[MAXSIZE]={0};    //��¼ÿ�����ֵ����λ��

    cout << "�����С��У�";
    cin >> m >> n;
    cout << "�������" << endl;
    for (int i = 0; i < m; i++) //�������
        for (int j = 0; j < n; j++)
            cin >> A[i][j];

    for (int i=0;i<m;i++)
    {
        for (int j=0;j<n;j++)
        {
            if (A[i][j]<A[i][rowmin[i]])
                rowmin[i] = j;
            if (A[i][j]>A[colmax[j]][j])
                colmax[j] = i;    
        }
    }
    
    for (int i=0;i<m;i++)
    {
        if (colmax[rowmin[i]]==i)
        {
            cout<<"����Ϊ��"<<'('<<i<<','<<rowmin[i]<<')'<<'='<<A[i][rowmin[i]]<<endl;
            return 0;
        }
    }
    cout<<"������";
}