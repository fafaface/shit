#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std;
struct Point {	//结构体表示方格的三个参数
	int x, y, step;//x, y轴坐标, 行经的步长
};
queue<Point> q;										 //用以存放扩展节点的队列
int vis[101][101];										 //表示一个方格是否被走过
int dir[4][2] = { 0 , 1 , 1 , 0 , 0 , -1 , -1 , 0 };//表示行走方向
int n, k, a, aa, b, bb;									  //方格边长 封锁方格数 输入起点和终点x,y坐标

int solve() {	  //队列式分支限界法进行搜索
	Point u, v;  //当前用以扩展的点
	while (!q.empty()) {					//如果队列非空
		u = q.front();						//将队列中的首元素取出用以扩展
		q.pop();								//弹出队列首元素
		if (u.x == b && u.y == bb) 
			return u.step;					 //已经是终点了
		for (size_t i = 0; i < 4; i++) { //朝着4 个方向进行扩展
			int xx = u.x + dir[i][0];		//依次是上,右,下,左
			int yy = u.y + dir[i][1];
			if (xx <= 0 || xx > n || yy <= 0 || yy > n) //如果超出n*n方格的边框,则越界
				continue;											   //不符合
			if (vis[xx][yy])										   //如果这个方格已经被封锁了
				continue;											   //不符合
			v.step = u.step + 1;								   //符合,步长+1
			v.x = xx;												   //当前扩展到的坐标就是下一步的横纵坐标
			v.y = yy;
			vis[xx][yy] = 1;										   //标记这个方格的位置被访问过了
			q.push(v);													//放到队列里,下次用以扩展
		}
	}
	return -1;//无解
}
int main() {
	int x, y;													   //x y轴坐标
	while (scanf("%d%d", &n, &k) != EOF) {//输入方格边长和封锁方格数
		memset(vis, 0, sizeof(vis));				   //访问数组重置
		while (!q.empty())								   //若队列非空
			q.pop();										   //则队列清空
		while (k--) {										   //输入封锁的方格的横纵坐标
			scanf("%d%d", &x, &y);					//封锁的方格相当于访问过
			vis[x][y] = 1;										//初始化访问数组, 1表示已经访问过
		}
		scanf("%d%d%d%d", &a, &aa, &b, &bb);//输入起点和终点坐标
		Point u;													  //创建起点
		u.x = a, u.y = aa, u.step = 1;                      //初始化起点
		q.push(u);													  //将起点放入队列中
		int ans = solve();										  //调用函数,寻找最少的方格数
		printf("%d\n", ans);									  //输出答案
	}
}