#include<iostream>
#include<queue>
using namespace std;
queue<double> q;

void print(double a[][101])
{
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j)
			printf("%5lf ", a[i][j]);
		cout << endl;
	}
	//delete a;
}
void algorithm1(int n) {
	double r, g, b;
	int x, y;
	x = y = 0;
	double a[101][101];
	for (int i = 0; i < n/3; ++i)
	{
		r = q.front(); q.pop();
		g = q.front(); q.pop();
		b = q.front(); q.pop();
		a[x][y++] = (r + g + b) / 3.0;
	//	cout << x << " " << y << a[x][y-1] << endl;
		if (y == 5) {
			x++; y = 0;
		}
	}
	print(a);
}
void algorithm2(int n) {
	double r, g, b;
	int x, y;
	x = y = 0;
	double a[101][101];
	for (int i = 0; i < n / 3; ++i)
	{
		r = q.front(); q.pop();
		g = q.front(); q.pop();
		b = q.front(); q.pop();
		a[x][y++] = 0.3*r + 0.59*g + 0.11*b;
		if (y == 5) {
			x++; y = 0;
		}
	}
	print(a);
}
int main()
{
	int n;
	cout << "请输入彩色图像区域方格个数: ";
	cin >> n;
	n *= 3;
	for (int i = 0; i < n; ++i)
	{
		double x;
		cin >> x;
		q.push(x);
	}
	int op;
	cout << "请选择转换算法: " << endl << "0:(R+G+B)/3"<<endl<<"1:0.3R+0.59G+0.11B" << endl;
	cout << "输入数字0或1: ";
	cin >> op;
	if (!op)
		algorithm1(n);//  (R+G+B)/3
	else
		algorithm2(n);//  0.3R+0.59G+0.11B

	while (!q.empty()) {
		q.pop();
	}
	return 0;
}