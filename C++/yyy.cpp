#include<iostream>
#include<algorithm>
using namespace std;

double a[5][4] = {
	0.5,0.67,0.35,0.03,
	0,0,0,0,
	0.89,0.73,1,0.09,
	1,1,0.6,0.6,
	0.56,0.42,0.84,1,
};
double b[5][5] = { 0 };
double ave_col[5] = { 0 };

double fun(int i, int j)
{
	double r;
	//·Ö×Ó
	double x ,y,t1,t2;
	x = 0;
	for (int k = 0; k < 4; ++k)
	{
		x=x+(a[i][k] - ave_col[i])* (a[j][k] - ave_col[j]);
	}
	x = fabs(x);
	y = 0;
	t1 = 0, t2 = 0;
	//·ÖÄ¸
	for (int k = 0; k < 4; ++k)
	{
		t1 = t1 + pow((a[i][k] - ave_col[i]), 2);
		t2 = t2 + pow((a[j][k] - ave_col[j]), 2);
	}
	y = sqrt(t1 * t2);
	r = x / y;
	return r;
}

int main()
{

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			ave_col[i] += a[j][i];
		}
		ave_col[i] /= 5;
		//printf("%lf\n", ave_col[i]);
	}
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			b[i][j] = fun(i, j);
			printf("%lf\n", b[i][j]);
		}
		printf("\n");
	}

	return 0;
}