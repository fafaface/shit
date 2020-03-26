#include <iostream>
#include <time.h>
#include <stdio.h> 
#include <set>
#include<vector>
#include<string>
using namespace std;

vector<string> fizzBuzz(int n) {
	string b1, b2, b3;
	b1="Fizz"; b2="Buzz"; b3="FizzBuzz";
	vector<string> ans;
	for (int i = 1; i <= n; ++i)
	{
		if (i % 3 != 0 && i % 5 != 0)
			ans.push_back(to_string(i));
		else if (i % 3 == 0 && i % 5 != 0) {
			ans.push_back(b1);
		}
		else if (i % 3 != 0 && i % 5 == 0) {
			ans.push_back(b2);
		}
		else {
			ans.push_back(b3);
		}
	}
	return ans;
}

int main()
{
	vector<string> v1,v2;
	int n,x;
	cin >> n;
	v1 = fizzBuzz(n);
	for (size_t i = 0; i < v1.size(); ++i)
		cout << v1[i] << endl;
	//cout << endl;
	return 0;
}
