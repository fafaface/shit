#include <iostream>
#include <cmath>
#include <windows.h>
#include<algorithm>
using namespace std;

struct point {
	double x;
	double y;
};

struct point_pair {
	point a;
	point b;
}minest_pair;

double dist(point p, point q) {//计算距离
	double x = fabs(p.x - q.x);//横坐标之差
	double y = fabs(p.y - q.y);//纵坐标之差
	return sqrt(x * x + y * y);
}

void bf(point p[], int n)//蛮力法
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

bool cmpx(point a, point b) {//比较x轴坐标大小
	return a.x < b.x;
}
bool cmpy(point a, point b) {//比较y轴坐标大小
	return a.y < b.y;
}
point_pair min_pair(point_pair m, point_pair n) {//比较两个最近对哪个更近
	return dist(m.a, m.b) > dist(n.a, n.b) ? n : m;
}


point_pair bruteforce(point p[],int n)//蛮力法2
{
	double mindist = 999999999;//初始化为最大值
	point_pair ans;
	ans.a = p[0]; ans.b = p[1];
	for (int i = 0; i < n - 1; ++i)
		for (int j = i + 1; j < n; ++j)//一一比较
		{
			double distance = dist(p[i], p[j]);
			if (distance < mindist) {
				mindist = distance;
				ans.a = p[i]; ans.b = p[j];//保存最近对
			}
		}
	return ans;//返回最近对
}

point_pair closest_strip(point strip[], int size, point_pair d) {
	double mind = dist(d.a,d.b);
	sort(strip, strip + size, cmpy);
	for (int i = 0; i < size; ++i) {
		for(int j=i+1;j<size&&(strip[j].y-strip[i].y)<mind;++j)
			if (dist(strip[i], strip[j]) < mind)
			{
				mind = dist(strip[i], strip[j]);
				d.a = strip[i];
				d.b = strip[j];
			}
	}
	return d;
}
point_pair closest_div(point p[],int n) {
	if (n <= 3) {
		return bruteforce(p,n);//剩下几个点,就直接蛮力法
	}
	int mid = n / 2;//找到中间分割点
	point mid_point = p[mid];
	point_pair disleft=closest_div(p,mid);//左半边
	point_pair disright = closest_div(p+mid,n-mid);//右半边
	point_pair d1 = min_pair(disleft, disright);//综合左右两边

	point* strip = new point[n];
	int j = 0;
	for (int i = 0; i < n; ++i) {
		if (fabs(p[i].x - mid_point.x) < dist(d1.a, d1.b))
			strip[j++] = p[i];
	}
	return min_pair(d1, closest_strip(strip, j, d1));
}
point_pair divide_conquer(point p[],int n) {//分治法总函数
	sort(p,p+n,cmpx);//按照x轴坐标排序
	return closest_div(p,n);//分治法 将数组对半分递归
}



int main(){
	int n;//个数
	point p[10001];
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
		point_pair ans = bruteforce(p,n);//蛮力法,需要的时候修改成分治法
		QueryPerformanceCounter(&c2);
		cout << "最近对是:" << "(" << ans.a.x << "," << ans.a.y << ") " << "(" << ans.b.x << "," << ans.b.y << ")" << endl;
		cout << "蛮力法高精度计数器用时：" << (double)((c2.QuadPart - c1.QuadPart) * 1.0 / quadpart * 1.0) * 1000000 << endl;
		QueryPerformanceCounter(&c1);
		ans = divide_conquer(p,n);
		QueryPerformanceCounter(&c2);
		cout << "最近对是:" << "(" << ans.a.x << "," << ans.a.y << ") " << "(" << ans.b.x << "," << ans.b.y << ")" << endl;
		cout << "分治法高精度计数器用时：" << (double)((c2.QuadPart - c1.QuadPart) * 1.0 / quadpart * 1.0) * 1000000 << endl;
		cout << "输入点对的个数: ";
	}
	return 0;
}
