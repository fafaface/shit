#include <iostream>
#include <time.h>
#include <stdio.h> 
#include <set>
#include <string>
#include<vector>
#include <dos.h> 
#include <windows.h>
#include<fstream>
using namespace std;
int BF(char s[], char t[]) {
	int index = 0;//初始化变量
	int i = 0, j = 0;
	while ((s[i] != '\0') && (t[j] != '\0'))//当两个字符串下标都没有到字符串结束位置
	{
		if (s[i] == t[j]) { i++; j++; }//相等,下标都向后移动一位
		else {
			index++; i = index; j = 0;//不相等,原始字符串下标向后移动一位,查询字符串从头继续寻找
		}
	}
	if (t[j] == '\0') return index + 1;//如果查找的字符串已经到末尾了,说明匹配成功
	else return 0;//没有到末尾,说明原始字符串已经遍历完成,其中没有需要查找的字符串
}

void GetNext(char T[], int next[])
{
	int j = 0, k = -1;
	next[0] = -1;
	while (T[j] != '\0')              	//直到字符串末尾
	{
		if (k == -1) {               	//无相同子串
			next[++j] = 0; k = 0;
		}
		else if (T[j] == T[k]) {        	//确定next[j+1]的值
			k++;               		//相等子串长度加1
			next[++j] = k;
		}
		else k = next[k];        	//取T[0]…T[j]的下一个相等子串的长度
	}
}
int nex[1001];
int KMP(char s[], char t[]) {
	int i = 0, j = 0;
	while ((s[i] != '\0') && (t[j] != '\0'))
	{
		if (s[i] == t[j]) { i++; j++; }
		else j = nex[j];
		if (j == -1) {
			i++; j++;
		}
	}
	if (t[j] == '\0') return i-strlen(t)+1;
	else return 0;
}

int main()
{
	ifstream myfile("C:/Users/yuehan lian/Desktop/123.txt");
	char input[1001];
	char search[1001];
	int i = 0;
	while (!myfile.eof()) //直到文件结尾
	{
		myfile >> input[i++];
	}
	myfile.close();
	cout << "输入主串input ";
	cin >> input;
	search[0] = 'c'; search[1] = 'a'; search[2] = 'd'; search[3] = 'a'; search[4] = 'b'; search[5] = '\0';
	//cout << "输入模式search: ";
	//cin >> search;
	memset(nex, 0, sizeof(nex));
	GetNext(search, nex);
	LARGE_INTEGER c1;//开始计时
	LARGE_INTEGER c2;//结束计时
	LARGE_INTEGER frequency;//计时器频率
	QueryPerformanceFrequency(&frequency);
	double quadpart = (double)frequency.QuadPart;
	QueryPerformanceCounter(&c1);
	int ans = KMP(input, search);//此处可替换为KMP,BM函数
	QueryPerformanceCounter(&c2);
	cout << "位置: " << ans << endl;
	cout << "高精度计数器用时：" << (double)((c2.QuadPart - c1.QuadPart) * 1.0 / quadpart * 1.0) * 1000000000000 << endl;
	return 0;
}

