#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

class TSP
{
public:
	typedef struct City {
		int x;
		int y;
	};
	string in,out;//输入输出文件名
	vector<int>odds;//奇数结点
	int** cost;
	int n,pathLength;//城市数量  最短距离
	int** graph;
	int** path_vals;//路径
	vector<int> circuit;//欧拉路径
	vector<City> cities;
	vector<int>* adjlist;
	TSP(string in);//构造函数
	~TSP();//析构函数
	int get_num() { return n; };
	int dis(struct City c1, struct City c2) { return floor((float)(sqrt((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y)) + .5)); }//四舍五入
	void Match();//完美匹配
	void Euler(int start, vector<int>& path);//寻找欧拉回路
	void Hamilton(vector<int>& path, int& pathCost);//寻找哈密顿路径
	void Tree();//Prim算法
};

TSP::TSP(string input) {//构造
	ifstream in;
	in.open(input.c_str(), ios::in);
	int c,count = 0;//序号, 计数
	double x, y;
	while (!in.eof()) {
		in >> c >> x >> y;
		count++;
	    City temp; temp.x = x; temp.y = y;
		cities.push_back(temp);
	}in.close();
	count--;n = count;
	graph = new int* [n];//初始化四个变量
	cost = new int* [n];
	path_vals = new int* [n];
	adjlist = new vector<int>[n];
	for (int i = 0; i < n; i++) {
		graph[i] = new int[n];
		for (int j = 0; j < n; j++) graph[i][j] = 0;
	}
	for (int i = 0; i < n; i++) cost[i] = new int[n];
	for (int i = 0; i < n; i++) path_vals[i] = new int[n];
	for (int i = 0; i < cities.size(); i++) struct City cur = cities[i];
}

TSP::~TSP() {//析构
	for (int i = 0; i < n; i++) {
		delete[] graph[i];
		delete[] cost[i];
		delete[] path_vals[i];
	}
	delete[] path_vals;
	delete[] graph;
	delete[] cost;
	delete[] adjlist;
}

void TSP::Tree() {//利用Prim算法来确定最小生成树
	int* key = new int[n];
	bool* included = new bool[n];
	int* parent = new int[n];
	for (int i = 0; i < n; i++) {
		key[i] = 0x7fffffff;//初始化每个结点距离赋一个较大值
		included[i] = false;//最小生成树中是否有该点
	}
	key[0] = 0;//最小生成树的根的距离为0
	parent[0] = -1;//没有父节点
	for (int i = 0; i < n - 1; i++) {
		//寻找未被包括在最小生成树的最近顶点
		int min = 0x7ffffff;
		int min_index;
		for (int i = 0; i < n; i++) {//遍历每个顶点
			if (included[i] == false && key[i] < min) {//如果这个顶点已经没有未访问过的更近键值顶点
				min = key[i];//赋值给min min_index
				min_index = i;
			}
		}
		included[min_index] = true;//找到了, 则设置为被包括在最小生成树里
		for (int j = 0; j < n; j++) {//检查最新加入的结点的没有被检测到的更近顶点
			if (graph[min_index][j] && included[j] == false && graph[min_index][j] < key[j]) {
				parent[j] = min_index;//更新父节点
				key[j] = graph[min_index][j];//更新键值
			}
		}
	}
	for (int i = 0; i < n; i++) {//构建邻边
		int j = parent[i];
		if (j != -1) {
			adjlist[i].push_back(j);
			adjlist[j].push_back(i);
		}
	}
}

void TSP::Match() {//用贪心法找到M的完美匹配
	int closest, length; 
	std::vector<int>::iterator tmp, first;
	for (int i = 0; i < n; i++)
		if ((adjlist[i].size() % 2) != 0)//如果这个顶点度数是奇数
			odds.push_back(i);//放入奇数表中//寻找奇度数的顶点
	while (!odds.empty()) {
		first = odds.begin();
		vector<int>::iterator it = odds.begin() + 1;
		vector<int>::iterator end = odds.end();
		length = std::numeric_limits<int>::max();
		for (; it != end; ++it) {
			if (graph[*first][*it] < length) {//如果这个点比当前的更近,更新最近的长度和下标
				length = graph[*first][*it];
				closest = *it;
				tmp = it;
			}//两个点被匹配, 一直到奇度数顶点列表为空
		} 
		adjlist[*first].push_back(closest);
		adjlist[closest].push_back(*first);
		odds.erase(tmp);
		odds.erase(first);
	}
}

void TSP::Euler(int start, vector<int>& path) {//寻找欧拉回路
	vector<int>* tempList = new vector<int>[n];
	for (int i = 0; i < n; i++) {
		tempList[i].resize(adjlist[i].size());//复制近邻列表
		tempList[i] = adjlist[i];
	}
	stack<int> stack;
	int pos = start;
	path.push_back(start);
	while (!stack.empty() || tempList[pos].size() > 0) {
		if (tempList[pos].empty()) {//当前结点没有邻居
			path.push_back(pos);//加到路径中
			pos = stack.top();//移除上一个顶点
			stack.pop();
		}
		else {//当前结点有邻居
			stack.push(pos);//把顶点加入到栈里
			int neighbor = tempList[pos].back();
			tempList[pos].pop_back();//移除当前顶点和邻居之间的边
			for (int i = 0; i < tempList[neighbor].size(); i++) {
				if (tempList[neighbor][i] == pos) {
					tempList[neighbor].erase(tempList[neighbor].begin() + i);
				}
			}
			pos = neighbor;//把邻居设置为当前结点
		}
	}
	path.push_back(pos);
}

void TSP::Hamilton(vector<int>& path, int& pathCost) {//剪去多余的顶点
	bool* visited = new bool[n];//移除欧拉回路中被访问过的结点
	for (int i = 0; i < n; i++)
		visited[i] = 0;
	pathCost = 0;
	int root = path.front();
	vector<int>::iterator cur = path.begin();
	vector<int>::iterator iter = path.begin() + 1;
	visited[root] = 1;
	bool addMore = true;//遍历回路
	while (iter != path.end()) {
		if (!visited[*iter]) {
			pathCost += graph[*cur][*iter];//计算代价
			cur = iter;
			visited[*cur] = 1;
			iter = cur + 1;
		}
		else
			iter = path.erase(iter);
	}
	if (iter != path.end()) {
		pathCost += graph[*cur][*iter];
	}
}
int main() {
	TSP tsp("C://Users/yuehan lian/Desktop/data.txt");//输入数据
	int city_num = tsp.get_num();
	for (int i = 0; i < tsp.n; i++)//构造距离矩阵
		for (int j = 0; j < tsp.n; j++)
			tsp.graph[i][j] = tsp.graph[j][i] = tsp.dis(tsp.cities[i], tsp.cities[j]);
	tsp.Tree();//最小生成树
	tsp.Match();//寻找与奇数顶点的最小权值匹配点 M
	int mindis = INT_MAX;//存储当前最短距离
	int mincity=0;//存储当前最短距离所代表的城市
	for (long t = 0; t < city_num; t++) {
		vector<int> path;
		tsp.Euler(t, path);
		int length;
		tsp.Hamilton(path, length);
		tsp.path_vals[t][0] = t; //设置起点
		tsp.path_vals[t][1] = length;//设置终点
		if (tsp.path_vals[t][1] < mindis) {
			mincity = tsp.path_vals[t][0];
			mindis = tsp.path_vals[t][1];
		}
	}
	tsp.Euler(mincity, tsp.circuit);//最小欧拉回路
	tsp.Hamilton(tsp.circuit, tsp.pathLength);
	cout << endl;
	cout << "路径为:" << endl << tsp.circuit.front() << "\t" << "距离" << endl;
	for (vector<int>::iterator it = tsp.circuit.begin(); it != tsp.circuit.end() - 1; ++it) {
		cout << *(it + 1) << "\t" << tsp.graph[*it][*(it + 1)] << endl;
	}
	cout << "\n路径长度: " << tsp.pathLength << endl << endl;
}