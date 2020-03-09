// 0202.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdio.h> 

using namespace std;
void rotate(vector<int>& nums, int k) {
	int len = nums.size();
	int l;
	len - k < 0 ? l = k - len : l=len - k;
	for (int i = 0; i < l; i++)
		nums.push_back(nums[i]);
	for (int i = 0; i < l; i++)
		nums.erase(nums.begin());


}
int main()
{

	return 0;
}
