#include <iostream>
using namespace std;

int path[101][101];							//存图路径
int n;												//点数
int edge_num;									//边的条数
int cnt;												//当前找到的路径长度
int ans[101];										//答案路径
auto s=make_pair(1, 2);

void Hierholzer(int l)						//取最后一次输入的点作为第一个被选中的点
{
	size_t i;
	while (path[l][0]) {						//说明l还有未被删除的无向边
		for (i = 1; i < n; ++i){
			if (path[l][i]) break;
		}
		path[l][i] = 0; path[i][l] = 0;		//删除边
		path[l][0]--; path[i][0]--;          //该点的边数减一
		Hierholzer(i);
	}
	ans[cnt++] = l;
}
int main()
{

	/*
	memset(path, 0, sizeof(path));			//初始化
	cin >> n >> edge_num;					//输入点数和边数
	int l, r;												//边的两个端点
	l = 1;
	cnt = 0;
	for (size_t i = 0; i < edge_num; ++i)
	{
		cin >> l >> r;								//左右端点值∈[1~n]
		path[l][r] = 1;								// l r 存在边
		path[l][0]++;								//计算该端点有几条边
		path[r][l] = 1;
		path[r][0]++;
	}
	Hierholzer(l);									//寻找欧拉回路
	*/
	cout << s.first<<s.second << endl;
	return 0;
}