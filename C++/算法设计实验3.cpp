#include <iostream>
#include <cmath>
#include <windows.h>
using namespace std;

struct point {
	double x;
	double y;
}p[10001];

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

void 
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