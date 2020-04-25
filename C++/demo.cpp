#include <iostream>
using namespace std;

int path[101][101];							//��ͼ·��
int n;												//����
int edge_num;									//�ߵ�����
int cnt;												//��ǰ�ҵ���·������
int ans[101];										//��·��
auto s=make_pair(1, 2);

void Hierholzer(int l)						//ȡ���һ������ĵ���Ϊ��һ����ѡ�еĵ�
{
	size_t i;
	while (path[l][0]) {						//˵��l����δ��ɾ���������
		for (i = 1; i < n; ++i){
			if (path[l][i]) break;
		}
		path[l][i] = 0; path[i][l] = 0;		//ɾ����
		path[l][0]--; path[i][0]--;          //�õ�ı�����һ
		Hierholzer(i);
	}
	ans[cnt++] = l;
}
int main()
{

	/*
	memset(path, 0, sizeof(path));			//��ʼ��
	cin >> n >> edge_num;					//��������ͱ���
	int l, r;												//�ߵ������˵�
	l = 1;
	cnt = 0;
	for (size_t i = 0; i < edge_num; ++i)
	{
		cin >> l >> r;								//���Ҷ˵�ֵ��[1~n]
		path[l][r] = 1;								// l r ���ڱ�
		path[l][0]++;								//����ö˵��м�����
		path[r][l] = 1;
		path[r][0]++;
	}
	Hierholzer(l);									//Ѱ��ŷ����·
	*/
	cout << s.first<<s.second << endl;
	return 0;
}