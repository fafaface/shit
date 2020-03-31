#include<iostream>
using namespace std;

int gcd(int a, int b) {
	int t;
	while (b != 0) {
		t = a % b;
		a = b;
		b = t;
	}
	return a;
}
void egypt(int a,int b) {//埃及算法
	int e;
	bool flag = 0;
	while(1) {
		e = b / a + 1;
		if (!flag) {
			flag = 1;
			cout << "1/" << e;
		}
		else
			cout << "+1/" << e;
		a = a * e - b;
		b = b * e;
		int f = gcd(a, b);
		if (f > 1) {
			a /= f;
			b /= f;
		}
		if (a <= 1)
			break;
	}
	if (!flag)
	{
		flag = 1;
		cout << "1/" << e;
	}
	else
		cout << "+1/" << b;
	cout << endl;
	
}


int main() {
	int a, b;
	cout << "输入一个真分数:";
	scanf("%d/%d", &a, &b);//分子 分母
	egypt(a,b);
	return 0;
}