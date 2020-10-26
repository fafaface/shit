#include<stdio.h>//头文件
/*3.利用贪心算法, 传入 货币面值数组, 可供找零的面值种类数,
*  顾客实际支付金额与应付商品总金额之差
*/
void GreedMoney(int m[], int k, int n) {
	if (n == 0) {
		printf("无需找钱!\n"); return;
	}
	printf("%s", n > 0 ? "应该找" : "顾客付钱金额不足!");

	int num[] = { 0,0,0,0 };
	int money[] = { 50,10,5,1 };//存放可供找零的面值，降序排列
	for (int i = 0; i < k; i++)
		while (n >= m[i]) {//当应找金额大于当前最大面额货币
			switch (m[i]) {
			case 50:
				num[0]++;  break;
			case 10:
				num[1]++;  break;
			case 5:
				num[2]++;  break;
			case 1:
				num[3]++;  break;
			}
			n = n - m[i];//继续寻找顾客剩余的钱
		}
	for (int j = 0; j < 4; ++j)//输出提示
		if (num[j] > 0)
			printf("%d张%d元 ", num[j], money[j]);
	printf("\n");
}
/*4. 传入字符数组的数字字符的起始位置,
*  结束位置, 输入的字符串数组
*/
int  change(int beg, int pos,  char s[]) {//字符转变为数字
	int j = beg;
	int num = 0;
	while (j < pos) {
		num = num * 10 + (s[j++] - '0');
	}
	return num;
}
int main() {
	/*
	* 1. 定义变量
	*/
	int money[] = { 50,10,5,1 };//存放可供找零的面值，降序排列
	int k = sizeof(money) / sizeof(money[0]);//可供找零的面值种类数

	/*
	* 2. 在while循环中, 每次循环进行一次找零钱的操作
	*/
	while (1) {
		int real = 0, input = 0;//应付商品总金额, 顾客付的金额
		char s[101];
		int gap = 0, end = 0;//检测两个数字间隔的位置
		printf("输入应付商品总金额和顾客实际支付金额, 用空格隔开: \n");
		gets_s(s);//读取字符串

		for (int i = 0; i < 101; ++i) {//遍历
			if (s[i] == ' ')
				gap = i;
			if (s[i] == '\0') {
				end = i;
				break;
			}
		}
		real = change(0, gap, s);//应付商品总金额
		input = change(gap + 1, end,  s);//顾客实际支付金额

		printf("%d %d", real, input);//输入应付商品总金额, 顾客付的金额
		if (real > 100 || input > 100 || real <= 0 || input <= 0) {
			printf("非法输入!\n");
			continue;
		}
		GreedMoney(money, k, input - real);//带入可供找零面值的货币大小, 货币种数, 顾客付钱金额, 寻找最佳找零方法
	}

}