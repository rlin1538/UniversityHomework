#include <iostream>
using namespace std;

struct BSTNode
{
    int key; //�ؼ���
    //InfoType data;    //����������
    BSTNode *left, *right; //���Һ���
};
//����keyֵ�Ľ��
BSTNode *BSTSearch(BSTNode *T, int key)
{
    if (T == NULL)
        return NULL;
    else if (T->key == key)
        return T;
    else if (T->key < key)
        return BSTSearch(T->right, key);
    else
        return BSTSearch(T->left, key);
}
//����ֵ
BSTNode *BSTInsert(BSTNode *T, int key)
{
    if (T == NULL)
    {
        T = new BSTNode;
        T->key = key;
        T->left = T->right = NULL;
        return T;
    }
    if (T->key == key)
    {
        cout << endl
             << key << "�Ѵ���" << endl;
        return T;
    }
    if (T->key > key)
        T->left = BSTInsert(T->left, key);
    else
        T->right = BSTInsert(T->right, key);
    return T;
}
//��������������
BSTNode *CreatBST(int n)
{
    BSTNode *T = NULL;
    int key;
    for (int i = 1; i <= n; i++)
    {
        cin >> key;
        T = BSTInsert(T, key);
    }
    return T;
}
//ɾ�����
BSTNode *BSTDelete(BSTNode *T, int key)
{
    BSTNode *p = T, *pa = NULL; //pΪ��ɾ���㣬paΪp�ĸ����
    BSTNode *f, *q;             //qָ��p��֧�е����ֵ��fΪq�����
    //���Ҵ�ɾ����
    while (p)
    {
        if (p->key == key)
            break;
        if (p->key < key)
        {
            pa = p;
            p = p->right;
        }
        else
        {
            pa = p;
            p = p->left;
        }
    }
    if (p == NULL)
    {
        return NULL;
        cout << "���Ҳ��ɹ�" << endl;
    }

    //ɾ��p
    //���pΪҶ���
    if (p->left == NULL && p->right == NULL)
    {
        if (pa) //���p���Ǹ����
        {
            if (pa->key < key) //�ж�p��pa�����ӻ����Һ���
                pa->right = NULL;
            else
                pa->right = NULL;
            delete p;
            return T;
        }
        else //���p�Ǹ����
        {
            delete p;
            return NULL;
        }
    }
    //���pֻ���Һ���
    if (p->left == NULL && p->right)
    {
        if (pa)
        {
            if (pa->key < key) //�ж�p��pa�����ӻ����Һ���
                pa->right = p->right;
            else
                pa->left = p->right;
            delete p;
            return T;
        }
        else //���p�Ǹ���㣬��ֱ�ӽ�p�Һ�������Ϊ�����
        {
            T = p->right;
            delete p;
            return T;
        }
    }
    //���pֻ������
    if (p->left && p->right == NULL)
    {
        if (pa)
        {
            if (pa->key < key) //�ж�p��pa�����ӻ����Һ���
                pa->right = p->left;
            else
                pa->left = p->left;
            delete p;
            return T;
        }
        else //���p�Ǹ���㣬��ֱ�ӽ�p�Һ�������Ϊ�����
        {
            T = p->left;
            delete p;
            return T;
        }
    }
    //���p�����Һ���
    else
    {
        //�ȴ���֧�����ֵ
        f = p;
        q = p->left;
        while (q->right)
        {
            f = q;
            q = q->right;
        }
        p->key = q->key;
        if (f->key < q->key)
            f->right = q->left;
        else
            f->left = q->left;
        delete q;
        return T;
    }
}

int menu_sel() //���Բ˵�
{
    char *m[5] = {(char *)"1.��������������",
                  (char *)"2.����Ԫ��",
                  (char *)"3.ɾ��Ԫ��",
                  (char *)"4.����Ԫ��",
                  (char *)"0.�˳�"};
    int i, choice;
    do
    {
        system("cls");
        cout << "-------���˵�-------" << endl;
        for (i = 0; i < 5; i++)
            cout << m[i] << endl;
        cout << "������ѡ��";
        cin >> choice;
    } while (choice < 0 || choice > 4);
    return choice;
}

int main()
{
    BSTNode *T = NULL;
    int n, sel, key;

    for (;;)
    {
        switch (sel = menu_sel())
        {
        case 1:
            cout << "����Ԫ�ظ�����";
            cin >> n;
            cout << "����Ԫ�أ�";
            T = CreatBST(n);
            system("pause");
            cout << "��������" << endl;
            break;
        case 2:
            cout << "����Ҫ�����Ԫ�أ�";
            cin >> key;
            T = BSTInsert(T, key);
            cout << "�������" << endl;
            system("pause");
            break;
        case 3:
            cout << "����Ҫɾ����Ԫ�أ�";
            cin >> key;
            if (BSTDelete(T, key))
                cout << "ɾ���ɹ�" << endl;
            system("pause");
            break;
        case 4:
            cout << "�������Ԫ�أ�";
            cin >> key;
            if (BSTSearch(T, key))
                cout << "���ҳɹ�" << endl;
            else
                cout << "����ʧ��" << endl;
            system("pause");
            break;
        case 0:
            system("pause");
            break;
        }
        if (sel == 0)
            break;
    }
}