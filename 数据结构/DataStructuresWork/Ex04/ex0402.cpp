#include <iostream>
#define MAXSIZE 256
using namespace std;

int main()
{
    int A[MAXSIZE][MAXSIZE];
    int m,n;    //m行n列
    int rowmin[MAXSIZE]={0};    //记录每行最小值的列位置
    int colmax[MAXSIZE]={0};    //记录每列最大值的行位置

    cout << "输入行、列：";
    cin >> m >> n;
    cout << "输入矩阵" << endl;
    for (int i = 0; i < m; i++) //输入矩阵
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
            cout<<"马鞍点为："<<'('<<i<<','<<rowmin[i]<<')'<<'='<<A[i][rowmin[i]]<<endl;
            return 0;
        }
    }
    cout<<"无马鞍点";
}