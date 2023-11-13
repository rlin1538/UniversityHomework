/*
061920125郑伟林
题目：对一个日期（含月m和日d）判断是否合法
输入：月份->month,号数->day
输出：日期合法则输出“日期正确”，日期非法则输出错误信息
 */

#include <iostream>

//对月份进行判断是否为大月，1、3、5、7、8、10、12为大月
bool isBigMonth(int m)
{
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
        return true;
    return false;
}

//对月份进行判断是否为小月，4、6、9、11为小月
bool isSmallMonth(int m)
{
    if (m == 4 || m == 6 || m == 9 || m == 11)
        return true;
    return false;
}

int main()
{
    int month; //月份
    int day;   //号数

    //月份与日期输入
    std::cout << "输入月份：";
    std::cin >> month;
    std::cout << "输入日期：";
    std::cin >> day;

    if (month > 12 || month <= 0)
    {
        /*
        月份输入不正确时，输出提示信息
         */
        std::cout << "月份错误！\n";
    }
    else
    {
        if (isBigMonth(month))
        {
            /*
            如果判断月份是大月
            再对号数进行判断，对超过31和小于等于0的号数提示日期错误
            正确的话提示日期正确
             */
            if (day > 31 || day <= 0)
                std::cout << "日期错误，" << month << "月不存在" << day << "号\n";
            else
                std::cout << "日期正确！\n";
        }
        else if (isSmallMonth(month))
        {
            /*
           如果判断月份是小月
           再对号数进行判断，对超过30和小于等于0的号数提示日期错误
           正确的话提示日期正确
            */
            if (day > 30 || day <= 0)
                std::cout << "日期错误，" << month << "月不存在" << day << "号\n";
            else
                std::cout << "日期正确！\n";
        }
        else
        {
            /*
            剩下的情况只剩二月
            由于不考虑闰年，因此只判断二月有28天
             */
            if (day > 28 || day <= 0)
                std::cout << "日期错误，" << month << "月不存在" << day << "号\n";
            else
                std::cout << "日期正确！\n";
        }
    }

    return 0;
}