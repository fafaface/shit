#include <iostream>
using namespace std;

void isPrime(long n)
{
    cout << "合数" << n << "的质因数为：";
    while (n > 1)
    {
        for (long i = 2; i <= n; i++)
        {
            if (n % i == 0)
            {
                n = n / i;
                cout << i << "  ";
                break;
            }
        }
    }
    cout << endl << endl;
}
int main()
{
    long num = 0;
    cout << "请输入要分解的合数：";
    while (cin >> num)
    {
        isPrime(num);
        cout << "请输入要分解的合数：";
    }
    return 0;
}