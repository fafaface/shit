#include <iostream>
#include <stdlib.h>
#include <climits>
#include<cstdio>
#include <windows.h>
using namespace std;
int zero(int n) {//�������Ӷκ�С��0,�򷵻�0;
	return n < 0 ? 0 : n;
}
int bf(int arr[], int x) {//BruteForce 01 ������
	int ans = -1;//��Ϊ�����Ϊ����,��ô��Ϊ0,��������ȸ�������Ӷκ�,�����
	int size = 0;//Ŀ���Ӷγ���
	for (int i = 1; i <= x; ++i)//�ӳ���1�������е��������ָ���
	{
		size = i;//Ŀ���Ӷγ���
		int nownum = 0;//��ǰ������Ӷ��е����ָ���
		int nowsum = 0;//��ǰ������Ӷεĺ�
		int beg = 0;//��ͷ��ʼ����
		int j = beg;//j��Ϊ��ʼ�±�
		for (; j < x; ++j)//����ʼλ��һֱ����Զλ��(������������Ŀǰ��Ŀ���Ӷγ���  nownum>size)
		{
			nownum++;//��ǰ�Ӷγ��� +1
			if (nownum > size)//��������Ŀǰ��Ŀ���Ӷγ���
			{
				nowsum = 0; nownum = 0;//��ΪҪ���¼����Ӷκ�,���Ե�ǰ���뵱ǰ�Ӷγ�������
				beg++;//�������,�����µ��Ӷ�
				j = beg;//��Ϊj�����Լ����Ϊ��ʼ����
				continue;
			}
			nowsum += arr[j];//�ۼ��Ӷκ�
			if (nowsum > ans)//�������Ŀǰ����Ӷκ�,��ֵ��ans
				ans = nowsum;//����ans��С
		}
	}
	return ans;
}

int maxn(int a, int b) {//�������еĽϴ���
	return a > b ? a : b;//��a>b,�򷵻�a,��֮����b
}
int maxn(int a, int b, int c) {//���������е������,����
	return maxn(maxn(a, b), c);//��������ıȽ���������max����
}
int crossing(int arr[], int l, int mid, int later)//���㺬���е������Ӷκ�
{
	int nowsum = 0;//��ǰ�Ӷκ�
	int lsum = -1;//�������Ӷκ�
	for (int i = mid; i >= l; --i)//���м������ƶ�
	{
		nowsum += arr[i];//�ۼ��Ӷ�����
		if (nowsum > lsum)//�����ǰ�Ӷκʹ������ڼ�¼�������Ӷκ͵�lsum
			lsum = nowsum;//��ֵ��¼
	}
	nowsum = 0;//ע���ʼ����ǰ�Ӷκ�
	int rsum = -1;//�Ҳ�����Ӷκ�
	for (int i = mid + 1; i <= later; ++i)//���м������ƶ�
	{
		nowsum += arr[i];//�ۼ��Ӷ�����
		if (nowsum > rsum)//�����ǰ�Ӷκʹ������ڼ�¼�Ҳ�����Ӷκ͵�rsum
			rsum = nowsum;//��ֵ��
	}
	return lsum + rsum;//��������Ӷκ�֮�;��ǰ����е������Ӷκ�
}
int dc(int arr[], int l, int later) {//Divide and Conquer 02 ���η�
	if (l == later)//��β�±��غ�
		return arr[l];//���ظõ�ֵ
	int mid = (l + later) / 2;//ȡ�е�
	return maxn(dc(arr, l, mid), dc(arr, mid + 1, later), crossing(arr, l, mid, later));
}

int b[2001];

int dp(int n[], int x) {//Dynamic Programming 03 ��̬�滮��
	memset(b, 0, sizeof(b));//��ʼ����¼ÿ������Ӷκ͵�dp����
	int ans = 0;//����Ӷκ�
	int j = 0;//������±� 0~(num-1)
	int p = 1;//dp������±� 
	for (; j < x; ++j, ++p)//ÿ��ѭ��,�±����
	{
		b[p] = max(b[p - 1] + n[j], n[j]);//�ɶ�̬�滮�������м���
		if (b[p] > ans) ans = b[p];//����˲��Ӷκʹ�������Ӷκ�,��ֵ��¼
	}
	return ans;
}
int main()
{
	int num;
	int arr[200007];
	int ans;
	LARGE_INTEGER c1;//��ʼ��ʱ
	LARGE_INTEGER c2;//������ʱ
	LARGE_INTEGER frequency;//��ʱ��Ƶ��
	QueryPerformanceFrequency(&frequency);
	double quadpart = (double)frequency.QuadPart;
	scanf("%d", &num);
	for (int i = 0; i < num; ++i)
		scanf("%d ", &arr[i]);
	//QueryPerformanceCounter(&c1);
	//ans = zero(bf(arr, num));//01 ������
	//QueryPerformanceCounter(&c2);
	//cout << "�߾��ȼ�������ʱ��" << (double)((c2.QuadPart - c1.QuadPart) * 1.0 / quadpart * 1.0) * 1000000 << endl;

//	cout << "����Ӷκ���" << ans << endl;
	QueryPerformanceCounter(&c1);
	ans = zero(dc(arr, 0, num - 1));//02 ���η�
	QueryPerformanceCounter(&c2);
	cout << "�߾��ȼ�������ʱ��" << (double)((c2.QuadPart - c1.QuadPart) * 1.0 / quadpart * 1.0) * 1000000 << endl;

	cout << "����Ӷκ���" << ans << endl;
	QueryPerformanceCounter(&c1);
	ans = zero(dp(arr, num));//03 ��̬�滮��
	QueryPerformanceCounter(&c2);
	cout << "�߾��ȼ�������ʱ��" << (double)((c2.QuadPart - c1.QuadPart) * 1.0 / quadpart * 1.0) * 1000000 << endl;

	cout << "����Ӷκ���" << ans << endl;
	return 0;
}