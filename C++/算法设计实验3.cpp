#include <iostream>

using namespace std;

struct point {
	double x;
	double y;
}p[10001];


point bf()//������
{
	point minpair;

	return minpair;
}
int main()
{
	point ans;
	int n;
	while (scanf("%d",&n)!=EOF&&n) {
		cout << "����" << n << "����Ե�x��y���ꡣ" << endl;
		for (int i = 0; i < n; ++i) {
			scanf("%lf%lf", &p[i].x, &p[i].y);
		}
		ans=bf();
	}

	return 0;
}