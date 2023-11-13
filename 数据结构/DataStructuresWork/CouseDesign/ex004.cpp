//4.Huffman���������
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
    HufTree HT;  //������������
    int n;       //�����n
    char *HC[N]; //�ַ��ı���

public:
    void InitHufTree()
    {
        cout << "����Ҷ��������";
        cin >> n;
        HT = new HTNode[2 * n];         //��̬����HT����ռ�
        for (int i = 0; i < 2 * n; i++) //HT��ʼ��
        {
            HT[i].weight = 0;
            HT[i].parent = 0;
            HT[i].lchild = 0;
            HT[i].rchild = 0;
        }
        cout << "����" << n << "��Ȩֵ��";
        for (int i = 0; i < n; i++)
            cin >> HT[i + 1].weight;
    }
    //ѡ��������С����
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
    //�ж��ַ�a�Ƿ����ڻ�������������
    int Exist(char a)
    {
        for (int i = 0; i < n; i++)
        {
            if (HT[i + 1].word == a)
                return i + 1;
        }
        return 0;
    }
    //ͳ���ĵ��ַ���
    void CountCharacters()
    {
        char a;
        int pos;
        ifstream fin("source.txt");

        HT = new HTNode[N]; //��̬����HT����ռ�
        n = 0;
        for (int i = 0; i < N; i++) //HT��ʼ��
        {
            HT[i].weight = 0;
            HT[i].parent = 0;
            HT[i].lchild = 0;
            HT[i].rchild = 0;
        }
        fin.get(a);
        while (!fin.eof())
        {
            if (pos = Exist(a)) //����ַ���ȡ��
            {
                HT[pos].weight++;
            }
            else //���δ��ȡ��
            {
                n++;
                HT[n].word = a;
                HT[n].weight++;
            }
            fin.get(a);
        }
    }
    //������������
    void HufCreat()
    {
        int s1, s2; //�����С������

        if (n <= 1)
            return; //���ֻ��һ����㣬ֱ�ӷ���

        for (int i = n + 1; i < 2 * n; i++) //������������
        {
            sel_tow_min(i - 1, s1, s2);
            HT[s1].parent = HT[s2].parent = i;
            HT[i].weight = HT[s1].weight + HT[s2].weight;
            HT[i].lchild = s1;
            HT[i].rchild = s2;
        }

        /*cout << "num" << '\t' << "weight" << '\t' << "parent" << '\t' << "lchild" << '\t' << "rchild" << endl;
        for (int i = 1; i < 2 * n; i++) //������������ṹ
            cout << i << '\t' << HT[i].weight << '\t' << HT[i].parent << '\t' << HT[i].lchild << '\t' << HT[i].rchild << endl;*/
    }
    //�Դ����Ļ����������б���
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
            out << "�ַ���" << HT[i].word << "\t���ִ�����" << HT[i].weight << "\t���룺" << HC[i] << endl;
    }
    //���ĵ�����ת��
    void HufTransferToStr() //��Ϊ�ַ��ļ�
    {
        char a;
        ifstream fin("source.txt");
        ofstream out("code01.dat");

        fin.get(a);
        while (!fin.eof())
        {
            out << HC[Exist(a)]; //�鵽a�ı��룬������д��code.dat
            fin.get(a);
        }
    }
    void HufTransfer() //��Ϊ�������ļ�
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
                bin[k++] = HC[pos][i] - '0'; //һλһλ�����
                if (k == 8)
                {
                    //�浽��λ��תΪʮ������תASCII�ַ�д���ĵ�

                    b[0] = char(bin[7] + bin[6] * 2 + bin[5] * 4 + bin[4] * 8 + bin[3] * 16 + bin[2] * 32 + bin[1] * 64);
                    out.write(b, sizeof(char));
                    k = 1; //���bin����
                    for (int j = 0; j < 8; j++)
                        bin[j] = 0;
                }
            }
            //fin.get(a);
        }
        fin.close();
        out.close();
    }
    //��ѹ�������ļ����н���
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
            temp[start++] = a; //һ��bitһ��bit�������temp
            temp[start] = '\0';
            for (int i = 1; i <= n; i++)
            {
                if (strcmp(temp, HC[i]) == 0) //ֱ����ǰ�ı���temp���ڣ��������Ϊ�ַ����
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
                    if (strcmp(temp, HC[i]) == 0) //ֱ����ǰ�ı���temp���ڣ��������Ϊ�ַ����
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
    Huffman T; //��������

    T.CountCharacters(); //ͳ���ַ�
    T.HufCreat();        //������������
    cout<<"��������������ɡ�\n";
    T.HufCode();         //����
    cout<<"�ĵ��������,���ݴ洢�ڣ�Huffman.txt\n";
    T.HufTransfer();     //ת��
    cout<<"�ĵ���ת��Ϊ��code.dat\n";
    T.HufDecode();       //����
    cout<<"ת���ļ��ѽ���Ϊ��recode.txt\n";
}