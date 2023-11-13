//4.Huffman编码与解码
#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>
#include <string.h>
#define N 256
using namespace std;

typedef struct
{
    unsigned int weight;
    unsigned int parent, lchild, rchild;
    char word;
} HTNode, *HufTree;

class Huffman
{
    HufTree HT;  //霍夫曼树数组
    int n;       //结点数n
    char *HC[N]; //字符的编码

public:
    void InitHufTree()
    {
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
    }
    //选择两个最小的数
    void sel_tow_min(int k, int &s1, int &s2)
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
    //判断字符a是否已在霍夫曼树数组中
    int Exist(char a)
    {
        for (int i = 0; i < n; i++)
        {
            if (HT[i + 1].word == a)
                return i + 1;
        }
        return 0;
    }
    //统计文档字符数
    void CountCharacters()
    {
        char a;
        int pos;
        ifstream fin("source.txt");

        HT = new HTNode[N]; //动态分配HT数组空间
        n = 0;
        for (int i = 0; i < N; i++) //HT初始化
        {
            HT[i].weight = 0;
            HT[i].parent = 0;
            HT[i].lchild = 0;
            HT[i].rchild = 0;
        }
        fin.get(a);
        while (!fin.eof())
        {
            if (pos = Exist(a)) //如果字符读取过
            {
                HT[pos].weight++;
            }
            else //如果未读取过
            {
                n++;
                HT[n].word = a;
                HT[n].weight++;
            }
            fin.get(a);
        }
    }
    //创建霍夫曼树
    void HufCreat()
    {
        int s1, s2; //存放最小两个数

        if (n <= 1)
            return; //如果只有一个结点，直接返回

        for (int i = n + 1; i < 2 * n; i++) //建立霍夫曼树
        {
            sel_tow_min(i - 1, s1, s2);
            HT[s1].parent = HT[s2].parent = i;
            HT[i].weight = HT[s1].weight + HT[s2].weight;
            HT[i].lchild = s1;
            HT[i].rchild = s2;
        }

        /*cout << "num" << '\t' << "weight" << '\t' << "parent" << '\t' << "lchild" << '\t' << "rchild" << endl;
        for (int i = 1; i < 2 * n; i++) //输入霍夫曼树结构
            cout << i << '\t' << HT[i].weight << '\t' << HT[i].parent << '\t' << HT[i].lchild << '\t' << HT[i].rchild << endl;*/
    }
    //对创建的霍夫曼树进行编码
    void HufCode()
    {
        char *temp;
        int start;
        ofstream out("Huffman.txt");

        temp = new char[n];
        for (int i = 1; i <= n; i++)
        {
            start = 0;
            for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
            {
                if (HT[f].lchild == c)
                    temp[start++] = '0';
                else
                    temp[start++] = '1';
            }
            temp[start] = '\0';
            strrev(temp);
            HC[i] = new char[start];
            strcpy(HC[i], temp);
        }
        delete temp;

        for (int i = 1; i <= n; i++)
            out << "字符：" << HT[i].word << "\t出现次数：" << HT[i].weight << "\t编码：" << HC[i] << endl;
    }
    //对文档进行转码
    void HufTransferToStr() //存为字符文件
    {
        char a;
        ifstream fin("source.txt");
        ofstream out("code01.dat");

        fin.get(a);
        while (!fin.eof())
        {
            out << HC[Exist(a)]; //查到a的编码，将编码写入code.dat
            fin.get(a);
        }
    }
    void HufTransfer() //存为二进制文件
    {
        char a;
        char *b;
        int bin[8] = {0};
        int pos, k = 1;
        int count = 0;
        ifstream fin("source.txt");
        ofstream out("code.dat", ios::binary);

        b = new char;
        while (!fin.eof())
        {
            fin.get(a);
            count++;
            pos = Exist(char(a));
            for (int i = 0; i < strlen(HC[pos]); i++)
            {
                bin[k++] = HC[pos][i] - '0'; //一位一位存编码
                if (k == 8)
                {
                    //存到八位后转为十进制再转ASCII字符写入文档

                    b[0] = char(bin[7] + bin[6] * 2 + bin[5] * 4 + bin[4] * 8 + bin[3] * 16 + bin[2] * 32 + bin[1] * 64);
                    out.write(b, sizeof(char));
                    k = 1; //清空bin数组
                    for (int j = 0; j < 8; j++)
                        bin[j] = 0;
                }
            }
            //fin.get(a);
        }
        fin.close();
        out.close();
    }
    //对压缩数据文件进行解码
    /*void HufDecode()
    {
        char *temp;
        char a;
        int start = 0;
        ofstream out("recode.txt");
        ifstream fin("code.dat", ios::binary);

        temp = new char[n];
        fin.get(a);
        while (!fin.eof())
        {
            temp[start++] = a; //一个bit一个bit输入编码temp
            temp[start] = '\0';
            for (int i = 1; i <= n; i++)
            {
                if (strcmp(temp, HC[i]) == 0) //直到当前的编码temp存在，将编码解为字符输出
                {
                    out << HT[i].word;
                    start = 0;
                }
            }
            fin.get(a);
        }
        out.close();
        fin.close();
    }*/
    void HufDecode()
    {
        char *temp;
        char a;
        char *b;
        int int_a;
        int start = 0;
        int bin[8] = {0};
        int k = 1;
        ofstream out("recode.txt");
        ifstream fin("code.dat", ios::binary);

        b = new char;
        temp = new char[n];
        while (!fin.eof())
        {
            fin.read(b, sizeof(char));
            a = b[0];
            int_a = int(a);
            k = 1;
            while (k < 8)
            {
                if (int_a >= pow(2, 7 - k))
                {
                    int_a = int_a - pow(2, 7 - k);
                    temp[start++] = '1';
                }
                else
                    temp[start++] = '0';
                k++;
                temp[start] = '\0';
                for (int i = 1; i <= n; i++)
                {
                    if (strcmp(temp, HC[i]) == 0) //直到当前的编码temp存在，将编码解为字符输出
                    {
                        out << HT[i].word;
                        start = 0;
                    }
                    if (fin.eof())
                        break;
                }
                if (fin.eof())
                    break;
            }
        }

        out.close();
        fin.close();
    }
};
int main()
{
    Huffman T; //霍夫曼树

    T.CountCharacters(); //统计字符
    T.HufCreat();        //创建霍夫曼树
    cout<<"霍夫曼树创建完成。\n";
    T.HufCode();         //编码
    cout<<"文档编码完成,内容存储在：Huffman.txt\n";
    T.HufTransfer();     //转码
    cout<<"文档已转码为：code.dat\n";
    T.HufDecode();       //解码
    cout<<"转码文件已解码为：recode.txt\n";
}