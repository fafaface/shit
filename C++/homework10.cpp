#include<iostream>
using namespace std;

int main()
{
	int n, x, y;
	bool ok = 0;
	cin >> n >> x;
	srand(x);//��������
	for (int i = 1; i <= n; ++i)
	{
		y = i;
	//	y = rand() % (n - 1)+ 1;//1<=y, y<=n-1
		if (y * y % n == x)
		{	ok = 1;
	
			cout << "���� " << y << endl;
			break;
		}
	}
	if (!ok) cout << "�޽�" << endl;
	return 0;
}