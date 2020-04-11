#include <iostream>
#include <stdlib.h>
#include <climits>
#include<cstdio>
#include <windows.h>
using namespace std;
int zero(int n) {//如果最大子段和小于0,则返回0;
	return n < 0 ? 0 : n;
}
int bf(int arr[], int x) {//BruteForce 01 蛮力法
	int ans = -1;//因为如果答案为负数,那么必为0,如果遇到比负数大的子段和,则更新
	int size = 0;//目标子段长度
	for (int i = 1; i <= x; ++i)//从长度1到数组中的所有数字个数
	{
		size = i;//目标子段长度
		int nownum = 0;//当前计算的子段中的数字个数
		int nowsum = 0;//当前计算的子段的和
		int beg = 0;//从头开始遍历
		int j = beg;//j作为起始下标
		for (; j < x; ++j)//从起始位置一直到最远位置(除非容量超过目前的目标子段长度  nownum>size)
		{
			nownum++;//当前子段长度 +1
			if (nownum > size)//容量超过目前的目标子段长度
			{
				nowsum = 0; nownum = 0;//因为要重新计算子段和,所以当前和与当前子段长度清零
				beg++;//数组后移,计算新的子段
				j = beg;//因为j不会自己变更为起始坐标
				continue;
			}
			nowsum += arr[j];//累加子段和
			if (nowsum > ans)//如果大于目前最大子段和,则赋值给ans
				ans = nowsum;//更新ans大小
		}
	}
	return ans;
}

int maxn(int a, int b) {//求两数中的较大数
	return a > b ? a : b;//若a>b,则返回a,反之返回b
}
int maxn(int a, int b, int c) {//求三个数中的最大数,重载
	return maxn(maxn(a, b), c);//调用上面的比较两个数的max函数
}
int crossing(int arr[], int l, int mid, int later)//计算含有中点的最大子段和
{
	int nowsum = 0;//当前子段和
	int lsum = -1;//左侧最大子段和
	for (int i = mid; i >= l; --i)//从中间向左移动
	{
		nowsum += arr[i];//累加子段数字
		if (nowsum > lsum)//如果当前子段和大于用于记录左侧最大子段和的lsum
			lsum = nowsum;//则赋值记录
	}
	nowsum = 0;//注意初始化当前子段和
	int rsum = -1;//右侧最大子段和
	for (int i = mid + 1; i <= later; ++i)//从中间向右移动
	{
		nowsum += arr[i];//累加子段数字
		if (nowsum > rsum)//如果当前子段和大于用于记录右侧最大子段和的rsum
			rsum = nowsum;//则赋值记
	}
	return lsum + rsum;//左右最大子段和之和就是包含中点的最大子段和
}
int dc(int arr[], int l, int later) {//Divide and Conquer 02 分治法
	if (l == later)//首尾下标重合
		return arr[l];//返回该点值
	int mid = (l + later) / 2;//取中点
	return maxn(dc(arr, l, mid), dc(arr, mid + 1, later), crossing(arr, l, mid, later));
}

int b[2001];

int dp(int n[], int x) {//Dynamic Programming 03 动态规划法
	memset(b, 0, sizeof(b));//初始化记录每步最大子段和的dp数组
	int ans = 0;//最大子段和
	int j = 0;//数组的下标 0~(num-1)
	int p = 1;//dp数组的下标 
	for (; j < x; ++j, ++p)//每次循环,下标后移
	{
		b[p] = max(b[p - 1] + n[j], n[j]);//由动态规划函数进行计算
		if (b[p] > ans) ans = b[p];//如果此步子段和大于最大子段和,则赋值记录
	}
	return ans;
}
int main()
{
	int num;
	int arr[200007];
	int ans;
	LARGE_INTEGER c1;//开始计时
	LARGE_INTEGER c2;//结束计时
	LARGE_INTEGER frequency;//计时器频率
	QueryPerformanceFrequency(&frequency);
	double quadpart = (double)frequency.QuadPart;
	scanf("%d", &num);
	for (int i = 0; i < num; ++i)
		scanf("%d ", &arr[i]);
	//QueryPerformanceCounter(&c1);
	//ans = zero(bf(arr, num));//01 蛮力法
	//QueryPerformanceCounter(&c2);
	//cout << "高精度计数器用时：" << (double)((c2.QuadPart - c1.QuadPart) * 1.0 / quadpart * 1.0) * 1000000 << endl;

//	cout << "最大子段和是" << ans << endl;
	QueryPerformanceCounter(&c1);
	ans = zero(dc(arr, 0, num - 1));//02 分治法
	QueryPerformanceCounter(&c2);
	cout << "高精度计数器用时：" << (double)((c2.QuadPart - c1.QuadPart) * 1.0 / quadpart * 1.0) * 1000000 << endl;

	cout << "最大子段和是" << ans << endl;
	QueryPerformanceCounter(&c1);
	ans = zero(dp(arr, num));//03 动态规划法
	QueryPerformanceCounter(&c2);
	cout << "高精度计数器用时：" << (double)((c2.QuadPart - c1.QuadPart) * 1.0 / quadpart * 1.0) * 1000000 << endl;

	cout << "最大子段和是" << ans << endl;
	return 0;
}