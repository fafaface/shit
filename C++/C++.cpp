// 0202.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <time.h>
#include <stdio.h> 
#include <dos.h> 
#include <windows.h>
#include <set>
using namespace std;

const int maxn = 1000007;   //先打个1000000以内的素数表
int is_prime[maxn];  //这个表示i这个数是不是质数， 1表示是质数，0表示不是
int is_public[maxn]; //这个表示i是不是两个整数的公共质因数
int ans;

set<int> s;
void db() {//da biao 打表
    for (int i = 2; i <= 1000000; i++) {
        is_prime[i] = 1;
        is_public[i] = 1;
    }
    for (int i = 2; i <= 1000000; i++) {
        if (is_prime[i] == 1)
        {
            for (int j = i + i; j <= 1000000; j += i) is_prime[j] = 0; // 从2*i开始，枚举这个素数的全部倍数，他的倍数肯定是合数，如果是合数，就置0；
        }
    }
}

int fun1(int m, int n)//算法1
{
    int t = m < n ? m : n;
    while (t--) {
        if (m % t == 0 && n % t == 0)
            return t;
    }
}
int fun2(int m, int n)//算法2
{
    int r = m % n;
    while (r != 0) {
        m = n;
        n = r;
        r = m % n;
    }
    return n;
}

int fun3(int m, int n) {//分解质因数
    int ans = 1;
    int i = 0;
    while (1)
    {
        shishi;
    }
    return ans;
}



int main()
{
    int m, n;
    db();//打素数表
    cout << "input two integers: ";
    cin >> m >> n;
    double a1, a2;
    time_t b1, b2;
    LARGE_INTEGER c1;//开始计时
    LARGE_INTEGER c2;//结束计时
    LARGE_INTEGER frequency;//计时器频率
    QueryPerformanceFrequency(&frequency);
    double quadpart = (double)frequency.QuadPart;
    //开始计时
    a1 = clock();
    b1 = time(NULL);
    QueryPerformanceCounter(&c1);
    //开始计算
    int ans = fun3(m, n);
    //结束计时
    a2 = clock();
    b2 = time(NULL);
    QueryPerformanceCounter(&c2);
    cout << m << "和" << n << "的最大公约数是" << ans << endl;

    cout << "计数器计时：" << (a2 * 1000 - a1 * 1000) / 1000.0 << endl;
    cout << "计时器计时：" << difftime(b2, b1) * 1.0 << endl;
    cout << "高精度计数器用时：" << (double)((c2.QuadPart - c1.QuadPart) * 1.0 / quadpart * 1.0) * 1000000 << endl;

}
