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
	string in,out;//��������ļ���
	vector<int>odds;//�������
	int** cost;
	int n,pathLength;//��������  ��̾���
	int** graph;
	int** path_vals;//·��
	vector<int> circuit;//ŷ��·��
	vector<City> cities;
	vector<int>* adjlist;
	TSP(string in);//���캯��
	~TSP();//��������
	int get_num() { return n; };
	int dis(struct City c1, struct City c2) { return floor((float)(sqrt((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y)) + .5)); }//��������
	void Match();//����ƥ��
	void Euler(int start, vector<int>& path);//Ѱ��ŷ����·
	void Hamilton(vector<int>& path, int& pathCost);//Ѱ�ҹ��ܶ�·��
	void Tree();//Prim�㷨
};

TSP::TSP(string input) {//����
	ifstream in;
	in.open(input.c_str(), ios::in);
	int c,count = 0;//���, ����
	double x, y;
	while (!in.eof()) {
		in >> c >> x >> y;
		count++;
	    City temp; temp.x = x; temp.y = y;
		cities.push_back(temp);
	}in.close();
	count--;n = count;
	graph = new int* [n];//��ʼ���ĸ�����
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

TSP::~TSP() {//����
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

void TSP::Tree() {//����Prim�㷨��ȷ����С������
	int* key = new int[n];
	bool* included = new bool[n];
	int* parent = new int[n];
	for (int i = 0; i < n; i++) {
		key[i] = 0x7fffffff;//��ʼ��ÿ�������븳һ���ϴ�ֵ
		included[i] = false;//��С���������Ƿ��иõ�
	}
	key[0] = 0;//��С�������ĸ��ľ���Ϊ0
	parent[0] = -1;//û�и��ڵ�
	for (int i = 0; i < n - 1; i++) {
		//Ѱ��δ����������С���������������
		int min = 0x7ffffff;
		int min_index;
		for (int i = 0; i < n; i++) {//����ÿ������
			if (included[i] == false && key[i] < min) {//�����������Ѿ�û��δ���ʹ��ĸ�����ֵ����
				min = key[i];//��ֵ��min min_index
				min_index = i;
			}
		}
		included[min_index] = true;//�ҵ���, ������Ϊ����������С��������
		for (int j = 0; j < n; j++) {//������¼���Ľ���û�б���⵽�ĸ�������
			if (graph[min_index][j] && included[j] == false && graph[min_index][j] < key[j]) {
				parent[j] = min_index;//���¸��ڵ�
				key[j] = graph[min_index][j];//���¼�ֵ
			}
		}
	}
	for (int i = 0; i < n; i++) {//�����ڱ�
		int j = parent[i];
		if (j != -1) {
			adjlist[i].push_back(j);
			adjlist[j].push_back(i);
		}
	}
}

void TSP::Match() {//��̰�ķ��ҵ�M������ƥ��
	int closest, length; 
	std::vector<int>::iterator tmp, first;
	for (int i = 0; i < n; i++)
		if ((adjlist[i].size() % 2) != 0)//�������������������
			odds.push_back(i);//������������//Ѱ��������Ķ���
	while (!odds.empty()) {
		first = odds.begin();
		vector<int>::iterator it = odds.begin() + 1;
		vector<int>::iterator end = odds.end();
		length = std::numeric_limits<int>::max();
		for (; it != end; ++it) {
			if (graph[*first][*it] < length) {//��������ȵ�ǰ�ĸ���,��������ĳ��Ⱥ��±�
				length = graph[*first][*it];
				closest = *it;
				tmp = it;
			}//�����㱻ƥ��, һֱ������������б�Ϊ��
		} 
		adjlist[*first].push_back(closest);
		adjlist[closest].push_back(*first);
		odds.erase(tmp);
		odds.erase(first);
	}
}

void TSP::Euler(int start, vector<int>& path) {//Ѱ��ŷ����·
	vector<int>* tempList = new vector<int>[n];
	for (int i = 0; i < n; i++) {
		tempList[i].resize(adjlist[i].size());//���ƽ����б�
		tempList[i] = adjlist[i];
	}
	stack<int> stack;
	int pos = start;
	path.push_back(start);
	while (!stack.empty() || tempList[pos].size() > 0) {
		if (tempList[pos].empty()) {//��ǰ���û���ھ�
			path.push_back(pos);//�ӵ�·����
			pos = stack.top();//�Ƴ���һ������
			stack.pop();
		}
		else {//��ǰ������ھ�
			stack.push(pos);//�Ѷ�����뵽ջ��
			int neighbor = tempList[pos].back();
			tempList[pos].pop_back();//�Ƴ���ǰ������ھ�֮��ı�
			for (int i = 0; i < tempList[neighbor].size(); i++) {
				if (tempList[neighbor][i] == pos) {
					tempList[neighbor].erase(tempList[neighbor].begin() + i);
				}
			}
			pos = neighbor;//���ھ�����Ϊ��ǰ���
		}
	}
	path.push_back(pos);
}

void TSP::Hamilton(vector<int>& path, int& pathCost) {//��ȥ����Ķ���
	bool* visited = new bool[n];//�Ƴ�ŷ����·�б����ʹ��Ľ��
	for (int i = 0; i < n; i++)
		visited[i] = 0;
	pathCost = 0;
	int root = path.front();
	vector<int>::iterator cur = path.begin();
	vector<int>::iterator iter = path.begin() + 1;
	visited[root] = 1;
	bool addMore = true;//������·
	while (iter != path.end()) {
		if (!visited[*iter]) {
			pathCost += graph[*cur][*iter];//�������
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
	TSP tsp("C://Users/yuehan lian/Desktop/data.txt");//��������
	int city_num = tsp.get_num();
	for (int i = 0; i < tsp.n; i++)//����������
		for (int j = 0; j < tsp.n; j++)
			tsp.graph[i][j] = tsp.graph[j][i] = tsp.dis(tsp.cities[i], tsp.cities[j]);
	tsp.Tree();//��С������
	tsp.Match();//Ѱ���������������СȨֵƥ��� M
	int mindis = INT_MAX;//�洢��ǰ��̾���
	int mincity=0;//�洢��ǰ��̾���������ĳ���
	for (long t = 0; t < city_num; t++) {
		vector<int> path;
		tsp.Euler(t, path);
		int length;
		tsp.Hamilton(path, length);
		tsp.path_vals[t][0] = t; //�������
		tsp.path_vals[t][1] = length;//�����յ�
		if (tsp.path_vals[t][1] < mindis) {
			mincity = tsp.path_vals[t][0];
			mindis = tsp.path_vals[t][1];
		}
	}
	tsp.Euler(mincity, tsp.circuit);//��Сŷ����·
	tsp.Hamilton(tsp.circuit, tsp.pathLength);
	cout << endl;
	cout << "·��Ϊ:" << endl << tsp.circuit.front() << "\t" << "����" << endl;
	for (vector<int>::iterator it = tsp.circuit.begin(); it != tsp.circuit.end() - 1; ++it) {
		cout << *(it + 1) << "\t" << tsp.graph[*it][*(it + 1)] << endl;
	}
	cout << "\n·������: " << tsp.pathLength << endl << endl;
}