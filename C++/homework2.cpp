// 0202.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
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
