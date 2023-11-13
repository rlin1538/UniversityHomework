#include <iostream>
using namespace std;

struct Point
{
    int x;
    int y;
};
Point a[1000];
int n;

bool judge(Point t)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i].x - 1 == t.x && a[i].y == t.y)
            count++;
        if (a[i].x + 1 == t.x && a[i].y == t.y)
            count++;
        if (a[i].x == t.x && a[i].y + 1 == t.y)
            count++;
        if (a[i].x == t.x && a[i].y - 1 == t.y)
            count++;
    }
    if (count == 4)
        return true;
    return false;
}
int score(Point t)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i].x - 1 == t.x && a[i].y - 1 == t.y)
            count++;
        if (a[i].x + 1 == t.x && a[i].y - 1 == t.y)
            count++;
        if (a[i].x - 1 == t.x && a[i].y + 1 == t.y)
            count++;
        if (a[i].x + 1 == t.x && a[i].y + 1 == t.y)
            count++;
    }
    return count;
}
int main()
{
    int ans[5] = {0};

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i].x >> a[i].y;

    for (int i = 0; i < n; i++)
        if (judge(a[i]))
            ans[score(a[i])]++;
    for (int i = 0; i < 5; i++)
        cout << ans[i] << endl;
}