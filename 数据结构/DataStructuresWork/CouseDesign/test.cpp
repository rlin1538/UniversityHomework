/*#include <fstream>

using namespace std;

int main()
{
    
    fstream out;
    out.open("test.dat", std::fstream::binary);
    out.write(reinterpret_cast<const char *>(b), sizeof(int) * 5);
    out.close();
}
#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;

int main(int argc, char **argv)
{

    char *a = "00101011";
    bitset<sizeof(a)> x(a);

    ofstream ouF;
    ouF.open("test.dat", std::ofstream::binary);
    ouF.write(reinterpret_cast<bitset>(a), sizeof(char));
    ouF.close();

  /*  ifstream inF;
    inF.open("test.dat", std::ifstream::binary);
    inF.read(reinterpret_cast<bitset>(b), sizeof(char));
    inF.close();

    for (int i = 0; i < 5; i++)
    {
        cout << b[i] << endl;
    }
    return 0;
}*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <fstream>
#define N 50000
using namespace std;


class SortTest
{
public:
    //创建样例
    void CreatSample()
    {
        ofstream fout("sample.txt");
        int temp;

        for (int i = 0; i < 10; i++)
            for (int j = 1; j <= N; j++)
                E[i][j] = rand(); //生成随机数组

        QuickSort(0, 1, N); //第一组调正序
        DeQuickSort(1, 1, N); //第二组调倒序

        for (int i = 0; i < 10; i++) //写入文件
        {
            for (int j = 1; j <= N; j++)
            {
                fout << E[i][j] << ' ';
                if (j % 100 == 0)
                    fout << endl;
            }
            fout << endl;
        }
        fout.close();
    }
    //测试函数
    void Test(void (*Sort)(int a[N + 1]))
    {
        ifstream fin("sample.txt");
        int start_time;

        for (int i = 0; i < 10; i++)
            for (int j = 1; j <= N; j++)
                fin >> E[i][j]; //每次从样例文件中获取数据到E数组

        start_time = clock(); //计时开始
        for (int i = 0; i < 10; i++)
            Sort(E[i]);                                             //排序十组数据
        cout << "用时：\t" << clock() - start_time << "ms" << endl; //计时结束，输出时间
    }
    void Test(void (*Sort)(int k, int head, int tail)) //Test函数的重载，快排用
    {
        ifstream fin("sample.txt");
        int start_time;

        for (int i = 0; i < 10; i++)
            for (int j = 1; j <= N; j++)
                fin >> E[i][j];

        start_time = clock();
        for (int i = 0; i < 10; i++)
            Sort(i, 1, N);
        cout << "用时：\t" << clock() - start_time << "ms" << endl;

       /* ofstream fout("out.txt"); //排序输出测试

        for (int i = 0; i < 10; i++)
        {    for (int j = 1; j <= N; j++)
            {
                fout<<E[i][j]<<' ';
                if (j%100==0) fout<<endl;
            }
            fout<<endl;
        }
        fout.close();*/
    }
};


int E[50001];
int Partition(int low, int high)
{
    int temp = E[(low + high) / 2];
    int pivotkey = E[(low + high) / 2];
    E[(low+high)/2]=E[low];/////
    E[low] = temp;
    while (low < high)
    {
        while (low < high && E[high] >= pivotkey)
            high--;
        E[low] = E[high];
        while (low < high && E[low] <= pivotkey)
            low++;
        E[high] = E[low];
    }
    E[low]=temp;////
    return low;
}

//基于low和high区间的快速排序算法
void QSort(int low, int high)
{
    if (low < high)
    {
        int pivotloc = Partition(low, high);
        QSort(low, pivotloc - 1);
        QSort(pivotloc + 1, high);
    }
}

int main()
{
    SortTest T;
    T.Test(QSort);
    cout << int('a');
}