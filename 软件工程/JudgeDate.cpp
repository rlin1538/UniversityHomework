/*
061920125֣ΰ��
��Ŀ����һ�����ڣ�����m����d���ж��Ƿ�Ϸ�
���룺�·�->month,����->day
��������ںϷ��������������ȷ�������ڷǷ������������Ϣ
 */

#include <iostream>

//���·ݽ����ж��Ƿ�Ϊ���£�1��3��5��7��8��10��12Ϊ����
bool isBigMonth(int m)
{
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
        return true;
    return false;
}

//���·ݽ����ж��Ƿ�ΪС�£�4��6��9��11ΪС��
bool isSmallMonth(int m)
{
    if (m == 4 || m == 6 || m == 9 || m == 11)
        return true;
    return false;
}

int main()
{
    int month; //�·�
    int day;   //����

    //�·�����������
    std::cout << "�����·ݣ�";
    std::cin >> month;
    std::cout << "�������ڣ�";
    std::cin >> day;

    if (month > 12 || month <= 0)
    {
        /*
        �·����벻��ȷʱ�������ʾ��Ϣ
         */
        std::cout << "�·ݴ���\n";
    }
    else
    {
        if (isBigMonth(month))
        {
            /*
            ����ж��·��Ǵ���
            �ٶԺ��������жϣ��Գ���31��С�ڵ���0�ĺ�����ʾ���ڴ���
            ��ȷ�Ļ���ʾ������ȷ
             */
            if (day > 31 || day <= 0)
                std::cout << "���ڴ���" << month << "�²�����" << day << "��\n";
            else
                std::cout << "������ȷ��\n";
        }
        else if (isSmallMonth(month))
        {
            /*
           ����ж��·���С��
           �ٶԺ��������жϣ��Գ���30��С�ڵ���0�ĺ�����ʾ���ڴ���
           ��ȷ�Ļ���ʾ������ȷ
            */
            if (day > 30 || day <= 0)
                std::cout << "���ڴ���" << month << "�²�����" << day << "��\n";
            else
                std::cout << "������ȷ��\n";
        }
        else
        {
            /*
            ʣ�µ����ֻʣ����
            ���ڲ��������꣬���ֻ�ж϶�����28��
             */
            if (day > 28 || day <= 0)
                std::cout << "���ڴ���" << month << "�²�����" << day << "��\n";
            else
                std::cout << "������ȷ��\n";
        }
    }

    return 0;
}