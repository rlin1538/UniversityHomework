#include <iostream>
using namespace std;

int main()
{
    int n;                 //苹果树个数
    int m;                 //检查次数
    long tree[2000] = {0}; //苹果树上的苹果数
    int fall[2000] = {0};  //苹果树掉落情况
    int temp;
    long ansT = 0;
    int ansD = 0, ansE = 0; //输出结果

    cin >> n;
    for (int i = 0; i < n; i++) //输入各行苹果树
    {
        cin >> m;                   //输入检查次数
        cin >> tree[i];             //输入第一次检查的苹果数
        for (int j = 1; j < m; j++) //循环输入各次检查情况
        {
            cin >> temp;   //记录本次检查情况
            if (temp <= 0) //疏果
            {
                tree[i] += temp;
            }
            else
            {
                if (temp < tree[i]) //判断是否有苹果掉落
                {
                    fall[i] = 1;
                    tree[i] = temp;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        ansT += tree[i]; //计算苹果总数
        if (fall[i])
            ansD++; //计算掉落苹果树棵树
        if (i == 0) //计算相邻三棵树的掉落情况
        {
            if (fall[n - 1] && fall[i] && fall[i + 1])
                ansE++;
        }
        else
        {
            if (i == n - 1)
            {
                if (fall[i - 1] && fall[i] && fall[0])
                    ansE++;
            }
            else
            {
                if (fall[i - 1] && fall[i] && fall[i + 1])
                    ansE++;
            }
        }
    }
    cout << ansT << ' ' << ansD << ' ' << ansE;
}