// 0202.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include <time.h>
#include <stdio.h> 
#include <set>
#include<vector>
#include <string>
#include <dos.h> 
#include <windows.h>
using namespace std;

#define MAX 101
//�����ʾ
int k;			//�������ʾ
int a[MAX][MAX];	//��ű����ճ̱������±�Ϊ0��Ԫ�ز��ã�

void Plan(int k)
{
	int i, j, n, t, temp;
	n = 2;			//n��2^1=2��ʼ
	a[1][1] = 1; a[1][2] = 2; //���2��ѡ�ֱ����ճ�,�õ����Ͻ�Ԫ��
	a[2][1] = 2; a[2][2] = 1;
	for (t = 1; t < k; t++)	//��������2^2(t=1)��,2^k(t=k-1)��ѡ��
	{
		temp = n;				//temp=2^t
		n = n * 2; 				//n=2^(t+1)
		for (i = temp + 1; i <= n; i++)		//�����½�Ԫ��
			for (j = 1; j <= temp; j++)
				a[i][j] = a[i - temp][j] + temp; //�������½�Ԫ��
		for (i = 1; i <= temp; i++)		//�����Ͻ�Ԫ��
			for (j = temp + 1; j <= n; j++)
				a[i][j] = a[i + temp][(j + temp) % n];
		for (i = temp + 1; i <= n; i++)		//�����½�Ԫ��
			for (j = temp + 1; j <= n; j++)
				a[i][j] = a[i - temp][j - temp];
	}
}

int main()
{
	cin >> k; 
	LARGE_INTEGER c1;//��ʼ��ʱ
	LARGE_INTEGER c2;//������ʱ
	LARGE_INTEGER frequency;//��ʱ��Ƶ��
	QueryPerformanceFrequency(&frequency);
	double quadpart = (double)frequency.QuadPart;
	QueryPerformanceCounter(&c1);
	Plan(k);
	QueryPerformanceCounter(&c2);
	int len = pow(2, k);
	for (int i = 1; i <= len; ++i) {
		for (int j = 1; j <= len; ++j)
			cout << a[i][j] << "  ";
		cout << endl;
	}
	cout << "�߾��ȼ�������ʱ��" << (double)((c2.QuadPart - c1.QuadPart) * 1.0 / quadpart * 1.0) * 1000000 << endl;
	return 0;
}