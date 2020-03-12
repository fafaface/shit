#include <iostream>
#include<stdlib.h>
using namespace std;
int main()
{
    int a[5][5];
    int b[8];
    memset(b, 0, sizeof(b));
    cout << "ÇëÊäÈë5*5¸öÊý×Ö: ";
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
        {
            int x; cin >> x;
            a[i][j] = x;
            b[x]++;
        }
    for (int i = 0; i < 8; ++i)
    {
        cout << i << "|";
        for (int j = 0; j< b[i]; ++j)
            cout << "*";
        cout << endl;
    }
    return 0;
}