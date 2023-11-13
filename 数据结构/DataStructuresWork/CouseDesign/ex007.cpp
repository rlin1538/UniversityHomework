//7.B-����Ӧ��
#include <iostream>
#include <fstream>
#include <cmath>
#define MAX_M 3
using namespace std;

typedef struct node
{
    int keynum;           //�������ؼ��ָ���
    int key[MAX_M + 1];   //���ؼ������飬MAX_M�ŵ�Ԫ�ſ�
    node *parent;         //�����ָ��
    node *ptr[MAX_M + 1]; //���ӽ��ָ������
} BTNode;                 //B-�����ṹ��

class BTree
{
private:
    BTNode *root;

public:
    void Creat()
    {
        root = new BTNode;
        root->keynum = 0;
        root->parent = NULL;
        for (int i = 0; i < MAX_M; i++)
        {
            root->ptr[i] = NULL;
        }
    }
    void Read()
    {
        ifstream fin("B-Tree.txt");
        int temp;

        Creat();
        while (!fin.eof())
        {
            fin >> temp;
            Insert(temp);
        }
    }
    BTNode *GetRoot()
    {
        return root;
    }
    BTNode *Search(int e, int &num)
    {
        node *p;
        int k = 0;

        p = root; //�Ӹ���㿪ʼ
        while (p != NULL)
        {
            if (e == p->key[k])
            {
                //cout << e << " ���ҳɹ���" << endl;
                num = k;
                return p;
            }
            if (e < p->key[k])
            {
                p = p->ptr[k];
                k = 0;
            }
            else
            {
                k++;
                if (k == p->keynum)
                {
                    p = p->ptr[p->keynum];
                    k = 0;
                }
            }
        }
        return NULL;
    }
    BTNode *FindPosition(int e)
    {
        node *p;
        int k = 0;

        p = root;
        while (p->ptr[0] != NULL)
        {
            if (e < p->key[k])
                p = p->ptr[k];
            else
            {
                k++;
                if (k == p->keynum)
                {
                    p = p->ptr[p->keynum];
                    k = 0;
                }
            }
        }
        return p;
    }
    void InsertKey(BTNode *cur, int e, BTNode *nex)
    {
        int i, j, mid;
        BTNode *newnode, *newroot;
        for (i = 0; i < cur->keynum; i++) //�Ƚ��ùؼ��ּ���һ֧��ַ���뵱ǰ�����ʵ�λ��
            if (e < cur->key[i])
                break;
        for (j = cur->keynum; j > i; j--)
        {
            cur->key[j] = cur->key[j - 1]; //���ؼ��ֺ�ָ�������
            cur->ptr[j + 1] = cur->ptr[j];
        }
        cur->key[i] = e; //�����µĹؼ��ֺ�ָ��
        cur->ptr[i + 1] = nex;
        if (cur->keynum < MAX_M - 1) //����ǰ��֧���Ĺؼ�����С��m-1��ֱ�Ӳ��벻����
        {
            cur->keynum++;
            return; //ֱ���˳���������
        }
        else //���򣬷��Ѵ���
        {
            //��curΪ�����ʱ
            if (cur == root)
            { //�¿�һ�������,�����������
                newroot = new BTNode;
                newroot->keynum = 0;
                newroot->parent = NULL;
                for (j = 0; j < MAX_M; j++)
                    newroot->ptr[j] = NULL;
                cur->parent = newroot;
                newroot->ptr[0] = cur;
                root = newroot;
            }
            newnode = new BTNode;
            newnode->parent = cur->parent; //��ʼ���½�㸸��ָ��
            for (j = 0; j < MAX_M; j++)
                newnode->ptr[j] = NULL; //��ʼ���½�㺢��ָ������
            i = floor((MAX_M - 1) / 2) + 1;
            mid = i - 1;
            newnode->keynum = MAX_M - i;               //��ʼ���½��ؼ�����
            cur->keynum = MAX_M - newnode->keynum - 1; // ���µ�ǰ���ʣ��ؼ�����
            j = 0;
            while (i < MAX_M)
            {
                newnode->key[j] = cur->key[i]; //ת��cur�м�ؼ���֮��Ĺؼ���
                newnode->ptr[j] = cur->ptr[i]; //ת����Ӧ����ָ��
                if (newnode->ptr[j])
                    newnode->ptr[j]->parent = newnode;
                cur->ptr[i] = NULL;
                i++;
                j++;
            }
            newnode->ptr[j] = cur->ptr[i]; //ת�����һ��ָ��
            if (newnode->ptr[j])
                newnode->ptr[j]->parent = newnode;
            InsertKey(cur->parent, cur->key[mid], newnode); //�м�ؼ��ּ�ָ���½��ָ�����cur�ĸ������
        }
    }
    void Insert(int e)
    {
        BTNode *p;
        p = FindPosition(e);

        InsertKey(p, e, NULL);
    }
    BTNode *FindChildMin(BTNode *p, int &min)
    {
        if (p->ptr[0] == NULL) //pΪ��ײ�
        {
            min = p->key[0]; //����
            return p;
        }
        else
        {
            return FindChildMin(p->ptr[0], min);
        }
    }
    BTNode *Merge(BTNode *cur, BTNode *bro, int num)
    {
        int temp;                //�游��������ƵĹؼ���
        int flag_l = 0;          //broΪcur���ֵܱ�ǣ�1Ϊ���ֵܣ�0Ϊ���ֵ�
        BTNode *newnode, *other; //�½�㣬��ϲ���Ľ��
        int i = 0, j = 0, k = 0;

        if (bro != cur->parent->ptr[num + 1]) //broΪcur���ֵ�
        {
            num -= 1; //����numΪ��������ƹؼ���λ��
            flag_l = 1;
        }
        temp = cur->parent->key[num];
        for (int i = num; i < cur->parent->keynum; i++)
        {
            cur->parent->key[i] = cur->parent->key[i + 1];
            cur->parent->ptr[i + 1] = cur->parent->ptr[i + 2];
        }
        cur->parent->keynum--;
        if (flag_l) //broΪcur���ֵ�
        {
            bro->key[bro->keynum] = temp;            //��temp
            bro->ptr[bro->keynum + 1] = cur->ptr[0]; //���ұߵĽ��ͷ����ָ��ת��
            if (cur->ptr[0])
                cur->ptr[0]->parent = bro;
            bro->keynum++;
            newnode = bro;
            other = cur;
        }
        else //����broΪcur���ֵ�
        {
            cur->key[cur->keynum] = temp; //��temp
            cur->ptr[cur->keynum + 1] = bro->ptr[0];
            if (bro->ptr[0])
                bro->ptr[0]->parent = cur;
            cur->keynum++;
            newnode = cur;
            other = bro;
        }

        for (int i = newnode->keynum; i < newnode->keynum + other->keynum; i++)
        {
            newnode->key[i] = other->key[i - newnode->keynum]; //ת����һ���ڵ��е�����
            newnode->ptr[i + 1] = other->ptr[i - newnode->keynum + 1];
            if (newnode->ptr[i + 1] != NULL)
                newnode->ptr[i + 1]->parent = newnode; //�����º���ָ��ĸ����
        }
        newnode->keynum = cur->keynum + bro->keynum;

        other = NULL;

        return newnode;
    }
    void DeleteButtonKey(BTNode *cur, int num)
    {
        int k, temp;
        BTNode *l, *r;
        for (int i = num; i < cur->keynum; i++)
        {
            cur->key[i] = cur->key[i + 1]; //ɾ���ؼ���
            //ɾ��ָ��?
        }
        //���cur�Ǹ���ֱ��ɾ
        cur->keynum--; //�ؼ�����-1

        if (cur->keynum >= (ceil(MAX_M / 2.0) - 1) || cur == root) //���ɾȥ��ؼ������Բ�С��[m/2]-1
        {

            return; //ֱ��ɾ��������
        }
        else
        {
            while (cur->keynum < (ceil(MAX_M / 2.0) - 1))
            {
                temp = 0;
                if (cur->parent == NULL) //������ݵ������
                {
                    if (cur->keynum == 0) //�����������
                    {
                        if (cur->ptr[0] != NULL) //�������㻹�к���
                        {
                            root = cur->ptr[0]; //���ĸ��ڵ�
                            root->parent = NULL;
                        }
                        else
                            root = NULL; //����B�����
                        delete cur;
                        break;
                    }
                }
                for (int i = 0; i <= cur->parent->keynum; i++)
                    if (cur->parent->ptr[i] == cur)
                        temp = i;
                if (temp - 1 >= 0 && cur->parent->ptr[temp - 1]->keynum > ceil(MAX_M / 2.0) - 1) //������ֵܵĹؼ���������[m/2]-1
                {
                    l = cur->parent->ptr[temp - 1];
                    k = 0;
                    while (k < cur->parent->keynum && l->key[l->keynum - 1] > cur->parent->key[k]) //�ҵ�����������ƹؼ���λ��
                        k++;
                    for (int i = cur->keynum; i > 0; i--) //���Ƹ����Ĺؼ���,ȫ������,���ڵ�һλ
                        cur->key[i] = cur->key[i - 1];
                    cur->key[0] = cur->parent->key[k];
                    cur->parent->key[k] = l->key[l->keynum - 1]; //�������ֵ������Ĺؼ���
                    l->keynum--;                                 //���ֵ���һ���ؼ���
                    cur->keynum++;                               //cur�ؼ���+1
                }
                else
                {
                    if (temp + 1 <= cur->parent->keynum && cur->parent->ptr[temp + 1]->keynum > ceil(MAX_M / 2.0) - 1) //������ֵܵĹؼ���������[m/2]-1
                    {
                        r = cur->parent->ptr[temp + 1];
                        k = 0;
                        while (k < cur->parent->keynum && r->key[0] > cur->parent->key[k]) //�ҵ�����������ƹؼ���λ��
                            k++;
                        k -= 1;
                        cur->key[cur->keynum] = cur->parent->key[k]; //���Ƹ����Ĺؼ��֣������һλ
                        cur->parent->key[k] = r->key[0];             //�������ֵ�����С�Ĺؼ���
                        r->keynum--;                                 //���ֵ���һ���ؼ���
                        cur->keynum++;                               //cur�ؼ���+1
                    }
                    else
                    {
                        //��������ֵܵĹؼ�����������������кϲ�
                        if (temp + 1 <= cur->parent->keynum)
                            Merge(cur, cur->parent->ptr[temp + 1], temp); //���ֵܴ���
                        else
                            Merge(cur, cur->parent->ptr[temp - 1], temp); //���ֵܴ���
                        cur = cur->parent;                                //����
                    }
                }
            }
        }
    }
    void Delete(int e)
    {
        int num;
        BTNode *q;

        if (q = Search(e, num)) //���ң�����ؼ��ִ���
        {
            if (q->ptr[0] == NULL) //�ؼ���λ�ڵײ���
            {
                DeleteButtonKey(q, num); //ֱ��ɾ��
            }
            else //�����q���num+1������ȡ��С�ؼ��������ǣ��ٽ������С�ؼ���ɾ��
            {
                q = FindChildMin(q->ptr[num + 1], q->key[num]); //����num+1�����е���С�ؼ��֣����ǵ�ǰ��������qΪ���ҵ��ĵײ���
                DeleteButtonKey(q, 0);                          //ɾ���ײ�����С�ؼ���
            }
        }
        else //�ؼ��ֲ�����
            cout << "�ؼ��ֲ����ڣ�" << endl;
    }
    void Print(BTNode *cur)
    {
        if (cur == NULL)
            return;

        if (cur->parent)
            cout << "parent:" << cur->parent->key[0] << '\t';
        cout << "keys:";
        for (int i = 0; i < cur->keynum; i++)
            cout << cur->key[i] << "\t";
        cout << endl;
        for (int i = 0; i <= cur->keynum; i++)
            Print(cur->ptr[i]);
    }
};

int main()
{
    BTree T;
    int e, temp, sel;

    T.Read();
    while (1)
    {
        system("cls");
        cout << "---------B-������--------\n";
        cout << "1.��ѯ����\n2.�������\n3.ɾ������\n4.��ʾ��ϵ��\n������ѡ��";
        cin >> sel;
        switch (sel)
        {
        case 1:
            cout << "\n��������Ҫ��ѯ������:";
            cin >> e;
            if (T.Search(e, temp))
                cout << '\n'
                     << e << "���ҳɹ���\n";
            else
                cout << '\n'
                     << e << "����ʧ�ܣ�\n";
            system("pause");
            break;
        case 2:
            cout << "\n��������Ҫ��ӵ�����:";
            cin >> e;
            if (T.Search(e, temp))
            {
                cout << '\n'
                     << e << "�Ѵ��ڣ�\n��ǰ��ϵ��Ϊ��\n";
                T.Print(T.GetRoot());
            }
            else
            {
                T.Insert(e);
                cout << '\n'
                     << e << "��ӳɹ�\n��ǰ��ϵ��Ϊ��\n";
                T.Print(T.GetRoot());
            }
            system("pause");
            break;
        case 3:
            cout << "\n��������Ҫɾ��������:";
            cin >> e;
            if (!T.Search(e, temp))
            {
                cout << '\n'
                     << e << "�����ڣ�\n��ǰ��ϵ��Ϊ��\n";
                T.Print(T.GetRoot());
            }
            else
            {
                T.Delete(e);
                cout << '\n'
                     << e << "ɾ���ɹ�\n��ǰ��ϵ��Ϊ��\n";
                T.Print(T.GetRoot());
            }
            system("pause");
            break;
        case 4:
            cout << "\n��ǰ��ϵ��Ϊ��\n";
            T.Print(T.GetRoot());
            system("pause");
            break;
        case 0:
            exit(0);
        }
    }
}