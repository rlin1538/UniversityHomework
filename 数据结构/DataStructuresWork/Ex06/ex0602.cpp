#include <iostream>
using namespace std;

typedef struct
{
    unsigned int weight;
    unsigned int parent, lchild, rchild;
} HTNode, *HufTree;

void sel_tow_min(HufTree HT, int k, int &s1, int &s2)
{
    int t = 1;
    while (HT[t].parent != 0)
        t++;
    s1 = t++;
    while (HT[t].parent != 0)
        t++;
    s2 = t++;
    if (HT[s2].weight < HT[s1].weight)
    {
        t = s1;
        s1 = s2;
        s2 = t;
    }
    for (int i = 1; i <= k; i++)
    {
        if (HT[i].parent == 0 && i != s1 && i != s2)
            if (HT[i].weight < HT[s1].weight)
            {
                s2 = s1;
                s1 = i;
            }
            else if (HT[i].weight < HT[s2].weight)
                s2 = i;
    }
}

void HufCreat(int n, HufTree HT) //创建霍夫曼树
{
    int s1, s2; //存放最小两个数

    if (n <= 1)
        return; //如果只有一个结点，直接返回

    for (int i = n + 1; i < 2 * n; i++) //建立霍夫曼树
    {
        sel_tow_min(HT, i - 1, s1, s2);
        HT[s1].parent = HT[s2].parent = i;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
    }

    cout << "num" << '\t' << "weight" << '\t' << "parent" << '\t' << "lchild" << '\t' << "rchild" << endl;
    for (int i = 1; i < 2 * n; i++) //输入霍夫曼树结构
        cout << i << '\t' << HT[i].weight << '\t' << HT[i].parent << '\t' << HT[i].lchild << '\t' << HT[i].rchild << endl;
}

int main()
{
    int n;      //结点数n
    //int w[100]; //存放结点权重数据
    HufTree HT; //霍夫曼树

    cout << "输入叶结点个数：";
    cin >> n;
    HT = new HTNode[2 * n];         //动态分配HT数组空间
    for (int i = 0; i < 2 * n; i++) //HT初始化
    {
        HT[i].weight = 0;
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    cout << "输入" << n << "个权值：";
    for (int i = 0; i < n; i++)
        cin >> HT[i + 1].weight;
    HufCreat(n , HT);
}