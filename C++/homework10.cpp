#include<iostream>
using namespace std;

int main()
{
	int n, x, y;
	bool ok = 0;
	cin >> n >> x;
	srand(x);//生成种子
	for (int i = 1; i <= n; ++i)
	{
		y = i;
	//	y = rand() % (n - 1)+ 1;//1<=y, y<=n-1
		if (y * y % n == x)
		{	ok = 1;
	
			cout << "答案是 " << y << endl;
			break;
		}
	}
	if (!ok) cout << "无解" << endl;
	return 0;
}