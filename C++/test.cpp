#include <iostream>
using namespace std;

void isPrime(long n)
{
    cout << "����" << n << "��������Ϊ��";
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
    cout << "������Ҫ�ֽ�ĺ�����";
    while (cin >> num)
    {
        isPrime(num);
        cout << "������Ҫ�ֽ�ĺ�����";
    }
    return 0;
}