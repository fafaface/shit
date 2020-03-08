#include <iostream>
#include <time.h>
#include <stdio.h> 
#include <set>
using namespace std;

int countPrimes(int n) {
    const int maxn = 1007;   //我们先打个1000000以内的表
    int is_prime[maxn];  //这个表示i这个数是不是质数， 1表示是质数，0表示不是
    int num[maxn];  //存下所有的素数，质数；
    int preprime[maxn];
    for (int i = 2; i <= 1000; i++) is_prime[i] = 1;
    for (int i = 2; i <= 1000; i++) {
        if (is_prime[i] == 1)
        {
            num[i] = i;//存入质数表
        //  printf("质数：%d\n",i);
            for (int j = i + i; j <= 1000; j += i) is_prime[j] = 0; // 从2*i开始，枚举这个素数的全部                  倍数，他的倍数肯定是合数，如果是合数，就置0；
        }
    }
    memset(preprime, 0, sizeof(preprime));
    int counting = 0;
    for (int i = 1; i <= 1000; i++)
    {

        num[i] == i ? preprime[i] = ++counting : preprime[i] = counting;
    }
    return preprime[n];
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF&&n)
    {
 cout << countPrimes(n) << endl;
   }
   
    return 0;
}
