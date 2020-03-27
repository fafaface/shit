#include <iostream>
#include <cmath>
#include <windows.h>
using namespace std;

struct point {
	double x;
	double y;
}p[10001];

struct point_pair {
	point a;
	point b;
}minest_pair;

double dist(point p, point q) {//计算距离
	double x = fabs(p.x - q.x);//横坐标之差
	double y = fabs(p.y - q.y);//纵坐标之差
	return sqrt(x * x + y * y);
}

void bf(int n)//蛮力法
{
	int minpair[2]; minpair[0] = 0; minpair[1] = 0;
	double mindist=9999999;
	for (int i = 0; i < n - 1; ++i)
		for (int j = i + 1; j < n; ++j)
		{
			double distance = dist(p[i], p[j]);
			if (distance < mindist) {
				mindist = distance;
				minpair[0] = i; minpair[1] = j;
			}
		}
	cout << "最小距离是: " << mindist << endl;
	cout << "最近对是:" << "(" << p[minpair[0]].x << "," << p[minpair[0]].y << ") " << "(" << p[minpair[1]].x << "," << p[minpair[1]].y << ")" << endl;
}

/*分治法*/

point_pair bruteforce(int n)//蛮力法
{

	double mindist = 9999999;
	point_pair ans;
	for (int i = 0; i < n - 1; ++i)
		for (int j = i + 1; j < n; ++j)
		{
			double distance = dist(p[i], p[j]);
			if (distance < mindist) {
				mindist = distance;
				ans.a = p[i]; ans.b = p[j];
			}
		}
	return ans;
}

point_pair closest_div(int n) {
	if (n <= 3) {
		return bruteforce(n);//剩下几个点,就直接蛮力法
	}
	int mid = n / 2;//找到中间分割点
	point mid_point = p[mid];
}
double  divide_concuer(int n) {//分治法总函数
	qsort(p, n, sizeof(point), cmp);//按照x轴坐标排序
	return closest_div(n);//分治法 将数组对半分递归
}
int main(){
	int n;//个数
	cout << "输入点对的个数: ";
	while (scanf("%d",&n)!=EOF&&n) {//如果为0 ,程序结束
		cout << "输入" << n << "个点对的x、y坐标。" << endl;
		for (int i = 0; i < n; ++i) {
			scanf("%lf%lf", &p[i].x, &p[i].y);//接收来自键盘的n个点对坐标
		}
		LARGE_INTEGER c1;//开始计时
		LARGE_INTEGER c2;//结束计时
		LARGE_INTEGER frequency;//计时器频率
		QueryPerformanceFrequency(&frequency);
		double quadpart = (double)frequency.QuadPart;
		QueryPerformanceCounter(&c1);
		bf(n);//蛮力法,需要的时候修改成分治法
		QueryPerformanceCounter(&c2);
		cout << "高精度计数器用时：" << (double)((c2.QuadPart - c1.QuadPart) * 1.0 / quadpart * 1.0) * 1000000 << endl;
	}
	return 0;
}