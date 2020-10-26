#include<iostream>
using namespace std;
int score[5][5] = {//课程的复习天数和提高分数的关系
	0,0,0,0,0,
	0,4,3,5,2,//如, 这一行代表复习1天, 课程1~4提高的分数
	0,4,5,6,4,//score[i][[j]代表复习i天, 课程j提高的分数
	0,5,6,8,7,
	0,8,7,8,8,
};
int pattern[8][5] = {//符合要求的课程安排的走法
	0,0,0,0,0,
	0,4,1,1,1,//如,pattern[i][j]代表此次遇到的打乱顺序的四门课程, 按照4,1,1,1天分别分配
	0,3,2,1,1,
	0,1,1,3,2,
	0,1,1,2,3,
	0,1,3,1,2,
	0,1,3,2,1,
	0,1,2,2,2,
};

int day;//代表日程安排是pattern[day]中的安排方式
bool vis[5];//vis[i]代表课程i是否已经安排完
int sche[5] = { 0 };//sche表示schedule, sche[i]代表课程i复习天数

//day表示课程安排的走法(1-6), course表示课程1,2,3,4, pos表示课程安排走法到了第几门课了, ans表示目前累积的分数
int dp( int day,int course,int pos, int ans)
{//由于course每次传值都为1, 所以是从课程1开始遍历的
	while (vis[course] == 1) {//如果当前课程已经被安排过了
		course++;//数字加一, 轮到下一门课
		if (course == 5)//如果course==5, 说明真实存在的课程1-4已经安排完毕了
			return ans;//返回目前累积的提高分数
	} 
	vis[course]= 1;//标记这门课被安排复习了
	sche[course] = pattern[day][pos];//记录这次课程course安排复习的天数 pattern[day][pos]
	ans = dp(day, 1,pos+1,ans+score[pattern[day][pos]][course]);
	return ans;//返回目前累积的提高分数
}
int main()
{
	int ans,maxn;
	int cnt = 1;
	maxn = 0;//初始化最大值
	int maxsche[5] = { 0 };//初始化最大情况下的课程安排
	for (int p = 1; p < 8; p++){
		for (int i = 1; i < 5; ++i){
			ans = 0;//初始化本次安排的提高分数
			memset(vis, 0, sizeof(vis));//初始化课程是否已安排标记
			memset(sche, 0, sizeof(sche));//初始化各个课程安排天数
			vis[i]= 1;//记录该课程被安排
			sche[i] = pattern[p][1];//记录该课程被安排的天数
			ans = dp(p,1,2, ans+score[pattern[p][1]][i]);
			printf("%d: %d\n",cnt++, ans);
			if (maxn < ans){//如果当前值大于目前的最大值
				maxn = ans;//更新最大值
				for (int j = 0; j < 5; j++)
					maxsche[j] = sche[j];//更新最大情况下的复习时间安排
			}
		}
	}
	printf("最大值为%d\n", maxn);
	for (int j = 1; j < 5; j++)
		printf("课程%d复习%d天\n", j, maxsche[j]);
	return 0;
}
