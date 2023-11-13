//3.���׹���ϵͳ
#pragma warning(disable : 4996)
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>
#define CHILD 5 //�������
using namespace std;

ofstream out; //�����ļ�
struct date   //���ڽṹ
{
    int year;  //��
    int mouth; //��
    int day;   //��
};

struct Member //��Ա���ݽṹ
{
    char *name;    //����
    date birth;    //����
    bool merry;    //���
    char *address; //��ַ
    bool alive;    //���ڷ�
    date death;    //����
};

typedef struct BiTNode //�����ṹ
{
    Member data;                  //��Ա����
    int generation;               //����
    BiTNode *parent;              //����ָ��
    int childnum;                 //������
    struct BiTNode *child[CHILD]; //����ָ��
} BiTNode, *BiTree;

void InitBiNode(BiTNode *a) //��ʼ����Ա���
{
    for (int i = 0; i < CHILD; i++)
        a->child[i] = NULL;
    a->data.name = new char[20];
    a->data.address = new char[30];
}

class FamilyTree //��������
{
    BiTree root; //�������ָ��
public:
    void Creat()
    {
        BiTNode *q;
        int y, m, d, temp;
        string s;

        q = new BiTNode[1];
        InitBiNode(q);

        root = q; //���ø����
        q->parent = NULL;
        q->generation = 1;
        q->childnum = 0;

        cout << "������һ����Ա��" << endl;

        cout << "����������";
        cin >> s;
        strcpy(q->data.name, s.c_str());
        cout << "�Ƿ��ڣ�0Ϊ��1Ϊ�ǣ���";
        while (1)
        {
            cin >> temp;
            if (temp == 0)
                q->data.alive = false;
            else if (temp == 1)
                q->data.alive = true;
            else
            {
                cout << "���������������룺";
                continue;
            }
            break;
        }
        cout << "������������գ��Կո�Ϊ�ָ�����";
        while (1)
        {
            cin >> y >> m >> d;
            if (m < 0 || m > 12 || d < 0 || d > 31)
            {
                cout << "���������������룺";
                continue;
            }
            else
            {
                q->data.birth.year = y;
                q->data.birth.mouth = m;
                q->data.birth.day = d;
            }
            break;
        }
        if (q->data.alive == false)
        {
            cout << "����ȥ�������գ��Կո�Ϊ�ָ�����";
            while (1)
            {
                cin >> y >> m >> d;
                if (m < 0 || m > 12 || d < 0 || d > 31 || y < q->data.birth.year)
                {
                    cout << "���������������룺";
                    continue;
                }
                else
                {
                    q->data.birth.year = y;
                    q->data.birth.mouth = m;
                    q->data.birth.day = d;
                }
                break;
            }
        }
        cout << "�Ƿ��ѻ飨0Ϊ��1Ϊ�ǣ���";
        while (1)
        {
            cin >> temp;
            if (temp == 0)
                q->data.merry = false;
            else if (temp == 1)
                q->data.merry = true;
            else
            {
                cout << "���������������룺";
                continue;
            }
            break;
        }
        cout << "�����ַ��";
        cin >> s;
        strcpy(q->data.address, s.c_str());
    }
    void Import(char *file) //�������
    {
        //���ݸ�ʽ������,�ѹ�,YYYY.MM.DD-YYYY.MM.DD,�ѻ�,��ַ
        BiTNode *father[20]; //��¼��ǰ��������
        BiTNode *p;          //�½��
        int i, k, num;       //������
        int rad;             //����ת������
        int ymd;             //�����ռ�¼,0��1��2��
        char *a;             //�ļ�һ��
        char *temp;          //��ʱ�ַ���
        char *c;             //�洢����
        ifstream fin(file);

        c = new char[4];
        a = new char[200];
        temp = new char[30];

        while (!fin.eof())
        {
            fin.getline(a, 200);
            p = new BiTNode[1];
            InitBiNode(p);
            i = 0;
            while (a[i] == '\t') //�Ե��Ʊ��
                i++;
            if (i == 0) //����ǵ�һ��
            {
                //root = new BiTNode;
                root = p; //���ø����
                p->parent = NULL;
                father[0] = p;
                p->generation = 1;
                p->childnum = 0;
            }
            else //�����ǵ�һ��
            {
                father[i] = p;
                p->parent = father[i - 1];                           //ȷ������
                father[i - 1]->child[father[i - 1]->childnum++] = p; //ȷ������
                p->generation = p->parent->generation + 1;           //ȷ������
                p->childnum = 0;
            }

            //����
            strcpy(temp, "");
            while (a[i] != ',')
            {
                c[0] = a[i];
                c[1] = a[i + 1];
                c[2] = '\0';
                strcat(temp, c); //����һ�����ĺ���
                i += 2;
            }
            p->data.name = new char[sizeof(char) * (strlen(temp) + 1)];
            strcpy(p->data.name, temp); //��������
            i++;                        //��һ���ַ�

            //���ڷ�
            strcpy(temp, "");
            while (a[i] != ',')
            {
                c[0] = a[i];
                c[1] = a[i + 1];
                //c[2] = a[i + 2];
                c[2] = '\0';
                strcat(temp, c); //����һ������
                i += 2;
            }
            if (strcmp(temp, "�ѹ�") == 0)
                p->data.alive = false;
            else
                p->data.alive = true;
            i++; //��һ���ַ�

            //��������
            k = 0;
            ymd = 0;
            strcpy(temp, "");
            while (a[i] != '-')
            {
                if (a[i] == '.')
                {
                    rad = 1; //����
                    num = 0;
                    for (int j = strlen(temp) - 1; j >= 0; j--)
                    {
                        num = num + rad * (temp[j] - '0');
                        rad *= 10;
                    }
                    if (ymd == 0)
                        p->data.birth.year = num; //������
                    if (ymd == 1)
                        p->data.birth.mouth = num; //������
                    strcpy(temp, "");
                    k = 0;
                    ymd++;
                    i++;
                }
                temp[k++] = a[i]; //����һ������
                temp[k] = '\0';
                i++;
            }
            rad = 1; //����
            num = 0;
            for (int j = strlen(temp) - 1; j >= 0; j--)
            {
                num = num + rad * (temp[j] - '0');
                rad *= 10;
            }
            p->data.birth.day = num; //������
            i++;                     //��һ���ַ�

            //��������
            if (p->data.alive == false) //����ѹ�
            {
                k = 0;
                ymd = 0;
                strcpy(temp, "");
                while (a[i] != ',')
                {
                    if (a[i] == '.')
                    {
                        rad = 1; //����
                        num = 0;
                        for (int j = strlen(temp) - 1; j >= 0; j--)
                        {
                            num = num + rad * (temp[j] - '0');
                            rad *= 10;
                        }
                        if (ymd == 0)
                            p->data.death.year = num; //������
                        if (ymd == 1)
                            p->data.death.mouth = num; //������
                        strcpy(temp, "");
                        k = 0;
                        ymd++;
                        i++;
                    }
                    temp[k++] = a[i]; //����һ������
                    temp[k] = '\0';
                    i++;
                }
                rad = 1; //����
                num = 0;
                for (int j = strlen(temp) - 1; j >= 0; j--)
                {
                    num = num + rad * (temp[j] - '0');
                    rad *= 10;
                }
                p->data.death.day = num; //������
            }
            i++;

            //���
            strcpy(temp, "");
            while (a[i] != ',')
            {
                c[0] = a[i];
                c[1] = a[i + 1];
                c[2] = '\0';
                strcat(temp, c); //����һ������
                i += 2;
            }
            if (strcmp(temp, "δ��") == 0)
                p->data.merry = false;
            else
                p->data.merry = true;
            i++; //��һ���ַ�

            //��ַ
            strcpy(temp, "");
            while (i < strlen(a))
            {
                c[0] = a[i];
                c[1] = a[i + 1];
                c[2] = '\0';
                strcat(temp, c); //����һ�����ĺ���
                i += 2;
            }
            p->data.address = new char[sizeof(char) * (strlen(temp) + 1)];
            strcpy(p->data.address, temp); //�����ַ

            //for (int i = 0; i < p->generation - 1; i++)
            //    cout << '\t';

            //printf("%s,%d,%d.%d.%d-\n", p->data.name, p->data.alive, p->data.birth.year, p->data.birth.mouth, p->data.birth.day);
        }
        //�������
        fin.close();
    }
    void Export(BiTNode *p) //��������
    {
        int len;
        if (p == NULL)
            return;
        for (int i = 0; i < p->generation - 1; i++)
            out << '\t';
        out << p->data.name << ',';
        if (p->data.alive)
            out << "����," << p->data.birth.year << '.' << p->data.birth.mouth << '.' << p->data.birth.day << '-';
        else
            out << "�ѹ�," << p->data.birth.year << '.' << p->data.birth.mouth << '.' << p->data.birth.day << '-' << p->data.death.year << '.' << p->data.death.mouth << '.' << p->data.death.day;
        if (p->data.merry)
            out << ",�ѻ�," << p->data.address;
        else
            out << ",δ��," << p->data.address;
        out << endl;
        for (int i = 0; i < p->childnum; i++)
            Export(p->child[i]);
    }
    void PrintInfo(BiTNode *p)
    {
        printf("%s\t", p->data.name);
        if (p->data.alive)
            printf("����\t%d.%d.%d-\t\t", p->data.birth.year, p->data.birth.mouth, p->data.birth.day);
        else
            printf("�ѹ�\t%d.%d.%d-%d.%d.%d\t", p->data.birth.year, p->data.birth.mouth, p->data.birth.day, p->data.death.year, p->data.death.mouth, p->data.death.day);
        if (p->data.merry)
            printf("�ѻ�\t%s\n", p->data.address);
        else
            printf("δ��\t%s\n", p->data.address);
    }
    void Print(BiTNode *p) //��ʾ����
    {
        if (p == NULL)
            return;
        for (int i = 0; i < p->generation - 1; i++)
            cout << '\t';
        printf("%s\n", p->data.name);
        for (int i = 0; i < p->childnum; i++)
            Print(p->child[i]);
    }
    BiTNode *GetRoot()
    {
        return root;
    }
    void DisplayNGenera(BiTNode *p, int n) //��ʾ��n�����г�Ա
    {
        if (p == NULL)
            return;
        if (p->generation == n)
            PrintInfo(p);
        for (int i = 0; i < p->childnum; i++)
            DisplayNGenera(p->child[i], n);
    }
    void SearchByName(char *a) //����������ѯ
    {
        BiTNode *p;
        p = Locate(root, a);

        if (p == NULL)
        {
            cout << "δ�ҵ��ó�Ա��" << endl;
            return;
        }
        cout << "���ˣ�" << endl;
        PrintInfo(p);
        if (p->parent)
        {
            cout << "���ף�" << endl;
            PrintInfo(p->parent);
        }
        for (int i = 0; i < p->childnum; i++)
        {
            cout << "��" << i + 1 << "������" << endl;
            PrintInfo(p->child[i]);
        }
    }
    void SearchByBirth(BiTNode *p, int y, int m) //���ճ������²�ѯ��Ա
    {
        if (p == NULL)
            return;
        if (p->data.birth.year == y && p->data.birth.mouth == m)
            PrintInfo(p);
        for (int i = 0; i < p->childnum; i++)
            SearchByBirth(p->child[i], y, m);
    }
    void SearchByBirth(BiTNode *p, int y) //���ճ�����ݲ�ѯ��Ա
    {
        if (p == NULL)
            return;
        if (p->data.birth.year == y)
            PrintInfo(p);
        for (int i = 0; i < p->childnum; i++)
            SearchByBirth(p->child[i], y);
    }
    void Relation(BiTNode *a, BiTNode *b) //ȷ��a��b��ϵ
    {
        //a��b��XXX��
        if (a->parent) //���a���Ǹ���㣬��a�и���,��a����С�ڵ���bʱ
        {
            if (a->parent == b->parent)
            {
                printf("%s��%s���ֵ�\n", a->data.name, b->data.name);
                return;
            }
            if (a->parent == b)
            {
                printf("%s��%s�Ķ���\n", a->data.name, b->data.name);
                return;
            }
            if (a->parent->parent == b)
            {
                printf("%s��%s������\n", a->data.name, b->data.name);
                return;
            }
            if (a->parent->parent && a->parent->parent->parent == b)
            {
                printf("%s��%s��������\n", a->data.name, b->data.name);
                return;
            }
        }
        if (b->parent) //���b���Ǹ���㣬��b�и���,��a���ִ���bʱ
        {
            if (b->parent == a)
            {
                printf("%s��%s�ĸ���\n", a->data.name, b->data.name);
                return;
            }
            if (b->parent->parent == a)
            {
                printf("%s��%s���游\n", a->data.name, b->data.name);
                return;
            }
            if (b->parent->parent && b->parent->parent->parent == a)
            {
                printf("%s��%s�����游\n", a->data.name, b->data.name);
                return;
            }
        }
        printf("%s��%sΪ��ֱϵ��ϵ���ϵ�����Ĵ�\n", a->data.name, b->data.name);
    }
    BiTNode *Locate(BiTNode *p, char *a) //����������λ����ַ
    {
        BiTNode *q = NULL;

        if (p == NULL)
            return NULL;
        if (strcmp(p->data.name, a) == 0)
            return p;
        for (int i = 0; i < p->childnum; i++)
        {
            q = Locate(p->child[i], a);
            if (q != NULL)
                return q;
        }
        return NULL;
    }
    int AddChild(char *a) //Ϊa��Ӻ���
    {
        BiTNode *p, *q;
        string s;
        int temp, y, m, d;

        p = Locate(root, a);
        if (p == NULL)
        {
            cout << "δ�ҵ����ˡ�" << endl;
            return 0;
        }
        q = new BiTNode;
        InitBiNode(q);
        q->parent = p;
        q->generation = p->generation + 1;
        q->childnum = 0; //��ʼ�����½��q

        p->child[p->childnum] = q;
        p->childnum++; //����p���

        cout << "����������";
        cin >> s;
        strcpy(q->data.name, s.c_str());
        cout << "�Ƿ��ڣ�0Ϊ��1Ϊ�ǣ���";
        while (1)
        {
            cin >> temp;
            if (temp == 0)
                q->data.alive = false;
            else if (temp == 1)
                q->data.alive = true;
            else
            {
                cout << "���������������룺";
                continue;
            }
            break;
        }
        cout << "������������գ��Կո�Ϊ�ָ�����";
        while (1)
        {
            cin >> y >> m >> d;
            if (m < 0 || m > 12 || d < 0 || d > 31)
            {
                cout << "���������������룺";
                continue;
            }
            else
            {
                q->data.birth.year = y;
                q->data.birth.mouth = m;
                q->data.birth.day = d;
            }
            break;
        }
        if (q->data.alive == false)
        {
            cout << "����ȥ�������գ��Կո�Ϊ�ָ�����";
            while (1)
            {
                cin >> y >> m >> d;
                if (m < 0 || m > 12 || d < 0 || d > 31 || y < q->data.birth.year)
                {
                    cout << "���������������룺";
                    continue;
                }
                else
                {
                    q->data.birth.year = y;
                    q->data.birth.mouth = m;
                    q->data.birth.day = d;
                }
                break;
            }
        }
        cout << "�Ƿ��ѻ飨0Ϊ��1Ϊ�ǣ���";
        while (1)
        {
            cin >> temp;
            if (temp == 0)
                q->data.merry = false;
            else if (temp == 1)
                q->data.merry = true;
            else
            {
                cout << "���������������룺";
                continue;
            }
            break;
        }
        cout << "�����ַ��";
        cin >> s;
        strcpy(q->data.address, s.c_str());
        return 1;
    }
    void Delete(char *a) //ɾ����Ա
    {
        BiTNode *p;
        int i;

        p = Locate(root, a);
        if (p == NULL)
        {
            cout << "δ�ҵ��ó�Ա��" << endl;
            return;
        }
        if (p->parent)
        {
            for (i = 0; i < p->parent->childnum; i++)
                if (p->parent->child[i] == p)
                    break;
            for (i; i < p->parent->childnum - 1; i++)
                p->parent->child[i] = p->parent->child[i + 1]; //ɾ��p�����ָ��p�ĺ���ָ��
            p->parent->childnum--;
        }
        Relase(p);
    }
    int Modify(char *a) //�޸���Ϣ
    {
        BiTNode *q;
        int choose;
        string s;
        int temp, y, m, d;

        q = Locate(root, a);
        while (1)
        {
            system("cls");
            cout << "��ǰ��Ϣ��";
            PrintInfo(q);
            cout << "\n1.����\n2.���ڷ�\n3.��������\n4.ȥ������\n5.���\n6.��ַ\n0.�˳�\n����Ҫ�޸ĵ�ѡ�";
            cin >> choose;
            switch (choose)
            {
            case 1:
                cout << "����������";
                cin >> s;
                strcpy(q->data.name, s.c_str());
                system("pause");
                break;
            case 2:
                cout << "�Ƿ��ڣ�0Ϊ��1Ϊ�ǣ���";
                while (1)
                {
                    cin >> temp;
                    if (temp == 0)
                        q->data.alive = false;
                    else if (temp == 1)
                        q->data.alive = true;
                    else
                    {
                        cout << "���������������룺";
                        continue;
                    }
                    break;
                }
                system("pause");
                break;
            case 3:
                cout << "������������գ��Կո�Ϊ�ָ�����";
                while (1)
                {
                    cin >> y >> m >> d;
                    if (m < 0 || m > 12 || d < 0 || d > 31)
                    {
                        cout << "���������������룺";
                        continue;
                    }
                    else
                    {
                        q->data.birth.year = y;
                        q->data.birth.mouth = m;
                        q->data.birth.day = d;
                    }
                    break;
                }
                system("pause");
                break;
            case 4:
                if (q->data.alive == false)
                {
                    cout << "����ȥ�������գ��Կո�Ϊ�ָ�����";
                    while (1)
                    {
                        cin >> y >> m >> d;
                        if (m < 0 || m > 12 || d < 0 || d > 31 || y < q->data.birth.year)
                        {
                            cout << "���������������룺";
                            continue;
                        }
                        else
                        {
                            q->data.birth.year = y;
                            q->data.birth.mouth = m;
                            q->data.birth.day = d;
                        }
                        break;
                    }
                }
                else
                {
                    cout << "�޷����ø�ѡ�" << endl;
                }
                system("pause");
                break;
            case 5:
                cout << "�Ƿ��ѻ飨0Ϊ��1Ϊ�ǣ���";
                while (1)
                {
                    cin >> temp;
                    if (temp == 0)
                        q->data.merry = false;
                    else if (temp == 1)
                        q->data.merry = true;
                    else
                    {
                        cout << "���������������룺";
                        continue;
                    }
                    break;
                }
                system("pause");
                break;
            case 6:
                cout << "�����ַ��";
                cin >> s;
                strcpy(q->data.address, s.c_str());
                system("pause");
                break;
            case 0:
                break;
            }
            if (choose == 0)
                break;
        }
        return 1;
    }
    void Relase(BiTNode *p)
    {
        if (p == NULL)
            return;
        for (int i = 0; i < p->childnum; i++)
            Relase(p->child[i]);

        delete p;
    }
    void SetEmpty()
    {
        root = NULL;
    }
};

int menu_sel() //���Բ˵�
{
    char *m[15] = {(char *)"1.�����¼���",
                   (char *)"2.�������",
                   (char *)"3.��������",
                   (char *)"4.��ʾ����",
                   (char *)"5.��ʾ��N����Ա",
                   (char *)"6.��������ѯ",
                   (char *)"7.��������/���²�ѯ��Ա",
                   (char *)"8.ȷ����Ա���Ա�Ĺ�ϵ",
                   (char *)"9.Ϊ��Ա��Ӻ���",
                   (char *)"10.ɾ����Ա",
                   (char *)"11.�޸ĳ�Ա��Ϣ",
                   (char *)"12.ɾ������",
                   (char *)"0.�˳�"};
    int i, choice;
    do
    {
        system("cls");
        cout << "-------���׹���ϵͳ���˵�-------" << endl;
        for (i = 0; i < 13; i++)
            cout << m[i] << endl;
        cout << "������ѡ��";
        cin >> choice;
    } while (choice < 0 || choice > 12);
    return choice;
}

int main()
{
    FamilyTree T;
    string s;
    int sel, choose, y, m;
    BiTNode *a, *b;

    T.Import((char *)"FamilyTree.txt"); //�����ʼ�����ļ�

    while (1)
    {
        if (T.GetRoot() == NULL)
        {
            cout << "��ǰ����δ�������뵼��򴴽���\n";
            system("pause");
        }

        switch (sel = menu_sel())
        {
        case 1:
            system("cls");
            cout << "---------�����¼���---------\n";
            T.Relase(T.GetRoot());
            cout << "��ʼ�����\n";
            T.Creat();
            cout << "��������\n";
            system("pause");
            break;
        case 2:
            system("cls");
            cout << "---------�������---------\n";
            cout << "���뵼���ļ�����";
            cin >> s;
            T.Import((char *)s.c_str());
            cout << "�������" << endl;
            system("pause");
            break;
        case 3:
            system("cls");
            cout << "---------��������---------\n";
            cout << "���뵼���ļ�����";
            cin >> s;
            out.open(s.c_str());
            T.Export(T.GetRoot());
            cout << "��������" << endl;
            system("pause");
            break;
        case 4:
            system("cls");
            cout << "---------��ʾ����---------\n";
            T.Print(T.GetRoot());
            system("pause");
            break;
        case 5:
            system("cls");
            cout << "---------��ʾ��N����Ա---------\n";
            cout << "�������������N��";
            cin >> choose;
            cout << "��" << choose << "����Ա�У�\n";
            T.DisplayNGenera(T.GetRoot(), choose);
            cout << "����\n";
            system("pause");
            break;
        case 6:
            system("cls");
            cout << "---------��������ѯ---------\n";
            cout << "����������";
            cin >> s;
            T.SearchByName((char *)s.c_str());
            system("pause");
            break;
        case 7:
            system("cls");
            cout << "---------��������/���²�ѯ---------\n";
            cout << "������ݣ�";
            cin >> y;
            cout << "�����·�(ģ��������0)��";
            while (1)
            {
                cin >> m;
                if (m < 0 || m > 12)
                    cout << "��������,�����䣺" << endl;
                else
                    break;
            }
            if (m == 0)
                T.SearchByBirth(T.GetRoot(), y);
            else
                T.SearchByBirth(T.GetRoot(), y, m);
            cout << "����" << endl;
            system("pause");
            break;
        case 8:
            system("cls");
            cout << "--------ȷ����Ա���Ա�Ĺ�ϵ----------\n";
            cout << "�����Ա1������";
            while (1)
            {
                cin >> s;
                a = T.Locate(T.GetRoot(), (char *)s.c_str());
                if (a == NULL)
                    cout << "�������������䣺";
                else
                    break;
            }
            cout << "�����Ա2������";
            while (1)
            {
                cin >> s;
                b = T.Locate(T.GetRoot(), (char *)s.c_str());
                if (b == NULL || b == a)
                    cout << "�������������䣺";
                else
                    break;
            }
            T.Relation(a, b);
            system("pause");
            break;
        case 9:
            system("cls");
            cout << "---------Ϊ��Ա��Ӻ���---------\n";
            cout << "����ó�Ա������";
            cin >> s;
            T.AddChild((char *)s.c_str());
            system("pause");
            break;
        case 10:
            system("cls");
            cout << "---------ɾ����Ա---------\n";
            cout << "�����Ա������";
            while (1)
            {
                cin >> s;
                a = T.Locate(T.GetRoot(), (char *)s.c_str());
                if (a == NULL)
                    cout << "�������������䣺";
                else
                    break;
            }
            cout << "��ȷ��Ҫɾ��" << a->data.name << "�������к��?\n1ȷ����0ȡ����";
            cin >> choose;
            if (choose == 1)
            {
                T.Delete((char *)s.c_str());
                cout << "ɾ�����\n";
            }
            system("pause");
            break;
        case 11:
            system("cls");
            cout << "---------�޸���Ϣ---------\n";
            cout << "�����Ա������";
            while (1)
            {
                cin >> s;
                a = T.Locate(T.GetRoot(), (char *)s.c_str());
                if (a == NULL)
                    cout << "�������������䣺";
                else
                    break;
            }
            T.Modify((char *)s.c_str());
            system("pause");
            break;
        case 12:
            system("cls");
            cout << "-----------------ɾ������-------------------\n";
            cout << "��ȷ��Ҫɾ���ü���?\n1ȷ����0ȡ����";
            cin >> choose;
            if (choose == 1)
            {
                T.Relase(T.GetRoot());
                T.SetEmpty();
                cout << "ɾ�����\n";
            }
            system("pause");
            break;

        case 0:
            break;
        }
        if (sel == 0)
            break;
    }
}