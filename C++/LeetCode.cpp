#include <map>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;
string addBinary(string a, string b) {
    string ans="";
    
    int la = strlen();
    int lb = b.length();
    if (la < lb) {//永远是 a最长,b最短
        string t = a;
        a = b;
        b = a;
        int p = la;
        la = lb;
        lb = la;
    }
    cout << "la" << la << "lb" << lb << endl;
    int gogo = 0;//进位标志
    //两数相加到小的长度
    for (int i = 0; i < lb; ++i)
    {
        //0+0
        if (a[i] - '0' + b[i] - '0'+gogo == 0)
        {
         //   if (gogo) gogo = 0;
            ans+='0';
            cout << "1" << endl;
        }
        //0+1/1+0
        else if (a[i] - '0' + b[i] - '0' +gogo== 1)
        {
            if (gogo) gogo = 0;
            ans += '1';
            cout << "2" << endl;
        }
        //1+0+1
        else if (a[i] - '0' + b[i] - '0' +gogo== 2)
        {
            gogo = 1;
            ans += '0';
            cout << "3" << endl;
        }
        //1+1+1
        else  if (a[i] - '0' + b[i] - '0' + gogo == 3)
        {
            gogo = 1;
            ans += '1';
            cout << "4" << endl;
        }
    }

    for (int i = lb; i < la; ++i)
    {
        if (a[i]-'0' + gogo == 0)//0+0
        {
            ans += '0';
                cout << "a" << endl;
        }
        else if (a[i] - '0' + gogo == 1)//1+0/0+1
        {
            if (gogo) gogo = 0;
            ans += '1';
            cout << "b" << endl;
        }
        else  if (a[i] - '0' + gogo == 2)//1+1
        {
            gogo = 1;
            ans += '0';
            cout << "c" << endl;
        }
    }

    return ans;
}

int main()
{
    string a, b;
    while (1)
    {
        cin >> a >> b;
        a = addBinary(a, b);
        cout << a << endl;
    }

    return 0;
}


