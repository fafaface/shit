#include <iostream>
#include <time.h>
#include <stdio.h> 
#include <set>
using namespace std;

int countPrimes(int n) {
    const int maxn = 1007;   //�����ȴ��1000000���ڵı�
    int is_prime[maxn];  //�����ʾi������ǲ��������� 1��ʾ��������0��ʾ����
    int num[maxn];  //�������е�������������
    int preprime[maxn];
    for (int i = 2; i <= 1000; i++) is_prime[i] = 1;
    for (int i = 2; i <= 1000; i++) {
        if (is_prime[i] == 1)
        {
            num[i] = i;//����������
        //  printf("������%d\n",i);
            for (int j = i + i; j <= 1000; j += i) is_prime[j] = 0; // ��2*i��ʼ��ö�����������ȫ��                  ���������ı����϶��Ǻ���������Ǻ���������0��
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
