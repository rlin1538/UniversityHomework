#include <iostream>
using namespace std;

int main()
{
    int n;       //�������
    int a[1000]; //������������
    int k;       //ÿ���������走������
    int ans = 0;
    int temp = 0;

    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n; i++)
    {
        temp += a[i];
        if (temp >= k)
        {
            temp = 0;
            ans++;
        }
    }
    if (temp)
        ans++;
    cout << ans;
}