#include <iostream>
using namespace std;
#define num 3     //数目
#define INIT -1000  //初始值
int a[num];    //棋盘
void print()    //打印解
{
	int i;
	for (i = 0; i < num; ++i)
		printf("%d ", a[i]);
	printf("\n");
}


int Place(int row, int col)    //判断第row行第col列是否可以放置皇后
{
	for (int i = 0; i < num; ++i)   //对棋盘进行扫描
	{
		if (a[i] == col || abs(i - row) == abs(a[i] - col))   //判断列和斜线是否有冲突
			return 0;
	}
	return 1;
}

void Queen() 
{
	bool flag = 0;//判断到底没有有
	int n = 0;
	int i = 0, j = 0;
	while (i < num)
	{
		while (j < num)        //对i行的每一列进行查看，看是否可以放置皇后
		{
			if (Place(i, j))      //可以放置皇后
			{
				a[i] = j;        //第i行放置皇后
				j = 0;           //第i行放置皇后确定下一行的皇后位置，所以此处将j清零，从下一行的第0列开始逐列查看
				break;
			}
			else ++j;             //返回值为0, 说明不行, 继续查看下一列
		}
		if (a[i] == INIT)         //第i行没有解
		{
			if (i == 0)             //回溯到第一行,说明已经找到所有的解
				break;
			else                    //没有找到可以放置皇后的列,回溯
			{
				--i;
				j = a[i] + 1;        //把上一行皇后的位置往后移一列
				a[i] = INIT;      //把上一行皇后的位置清除，重新探测
				continue;
			}
		}
		if (i == num - 1)          
		{
			flag = 1;
			printf("%d : \n", ++n);print();//最后一行找到了位置 ,打印结果
			j = a[i] + 1;             //从最后一行放置皇后列数的下一列继续探测
			a[i] = INIT;           //清除最后一行的皇后位置
			continue;
		}
		++i;              //继续查看下一行的皇后位置
	}
	if(!flag)
		cout << "无解" << endl;
}

int main(void)
{
	for (int i = 0; i < num; ++i)//初始化
		a[i] = INIT;
	Queen();
	return 0;
}