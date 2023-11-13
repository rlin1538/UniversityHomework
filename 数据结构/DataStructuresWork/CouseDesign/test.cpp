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
    //��������
    void CreatSample()
    {
        ofstream fout("sample.txt");
        int temp;

        for (int i = 0; i < 10; i++)
            for (int j = 1; j <= N; j++)
                E[i][j] = rand(); //�����������

        QuickSort(0, 1, N); //��һ�������
        DeQuickSort(1, 1, N); //�ڶ��������

        for (int i = 0; i < 10; i++) //д���ļ�
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
    //���Ժ���
    void Test(void (*Sort)(int a[N + 1]))
    {
        ifstream fin("sample.txt");
        int start_time;

        for (int i = 0; i < 10; i++)
            for (int j = 1; j <= N; j++)
                fin >> E[i][j]; //ÿ�δ������ļ��л�ȡ���ݵ�E����

        start_time = clock(); //��ʱ��ʼ
        for (int i = 0; i < 10; i++)
            Sort(E[i]);                                             //����ʮ������
        cout << "��ʱ��\t" << clock() - start_time << "ms" << endl; //��ʱ���������ʱ��
    }
    void Test(void (*Sort)(int k, int head, int tail)) //Test���������أ�������
    {
        ifstream fin("sample.txt");
        int start_time;

        for (int i = 0; i < 10; i++)
            for (int j = 1; j <= N; j++)
                fin >> E[i][j];

        start_time = clock();
        for (int i = 0; i < 10; i++)
            Sort(i, 1, N);
        cout << "��ʱ��\t" << clock() - start_time << "ms" << endl;

       /* ofstream fout("out.txt"); //�����������

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

//����low��high����Ŀ��������㷨
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