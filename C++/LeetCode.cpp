#include <iostream>
#include <time.h>
#include <stdio.h> 
#include <set>
#include<vector>
#include<map>
#include<cmath>
using namespace std;

bool isPowerOfThree(int n) {
	return (n > 0 && (log10(n) / log10(3))-(int)( log10(n) / log10(3)) == 0);
}

int main()
{
	vector<vector<char>> v1;
	vector<char> v2;
	int n;
	//char x;
	printf(" ‰»Î ˝◊÷: \n");
	scanf("%d", &n);
	//for (size_t j = 0; j < 9; ++j) {
	//	v2.clear();
	//	for (size_t i = 0; i < 9; ++i)
	//	{
	//		while (1) {
	//			scanf("%c", &x);
	//			if ((x >= '1' && x <= '9') || x == '.')
	//				break;
	//		}
	//		v2.push_back(x);
	//	}
	//	v1.push_back(v2);
	//}

	
	bool ans = isPowerOfThree(n);
		cout <<ans << endl;
	//cout << endl;
	return 0;
}
