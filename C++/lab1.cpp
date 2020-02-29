// 0202.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <time.h>
#include <stdio.h> 
#include <dos.h> 
#include <windows.h>
#include <set>
using namespace std;

const int maxn = 1000007;
int is_prime1[maxn];  
int is_prime2[maxn]; 
int ans;


void init()//初始化两个数的质因数数组(包括重复数字)
{
    for (int i = 0; i < maxn; ++i)
    {
        is_prime1[i] = 0;
        is_prime2[i] = 0;
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

int fun3_b(int x,int* array)
{
   // cout << x << endl;
    int cnt = 0;
    while (x > 1)
    {
        for (int i = 2; i <= x; ++i)
        {
            if (x % i == 0)
            {
                x /= i;
                cout << i << " ";
                array[cnt++] = i;
                break;
            }
        }
    }
   // cout << endl;
    return cnt;
}
int fun3_a(int m, int n) {//算法3 分解质因数
    int ans = 1;
    int QAQ = fun3_b(m, is_prime1);
    int QWQ = fun3_b(n, is_prime2);
    int a = 0, b = 0;
    while (a < QAQ && b < QWQ)
    {
        if (is_prime1[a] == is_prime2[b])
        {
           // cout << is_prime1[a] << " ";
            ans *= is_prime1[a];
            a++;
            b++;
        }
        else if (is_prime1[a] > is_prime2[b])
        {
            b++;
        }
        else
        {
            a++;
        }
    }

   // cout << endl;
    return ans;
}



int main()
{
    int m, n;
    init();
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
    int ans = fun3_a(m, n);
    //结束计时
    a2 = clock();
    b2 = time(NULL);
    QueryPerformanceCounter(&c2);
    cout << m << "和" << n << "的最大公约数是" << ans << endl;

    cout << "计数器计时：" << (a2 * 1000 - a1 * 1000) / 1000.0 << endl;
    cout << "计时器计时：" << difftime(b2, b1) * 1.0 << endl;
    cout << "高精度计数器用时：" << (double)((c2.QuadPart - c1.QuadPart) * 1.0 / quadpart * 1.0) * 1000000 << endl;

}
