#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std;
struct Point {	//�ṹ���ʾ�������������
	int x, y, step;//x, y������, �о��Ĳ���
};
queue<Point> q;										 //���Դ����չ�ڵ�Ķ���
int vis[101][101];										 //��ʾһ�������Ƿ��߹�
int dir[4][2] = { 0 , 1 , 1 , 0 , 0 , -1 , -1 , 0 };//��ʾ���߷���
int n, k, a, aa, b, bb;									  //����߳� ���������� ���������յ�x,y����

int solve() {	  //����ʽ��֧�޽編��������
	Point u, v;  //��ǰ������չ�ĵ�
	while (!q.empty()) {					//������зǿ�
		u = q.front();						//�������е���Ԫ��ȡ��������չ
		q.pop();								//����������Ԫ��
		if (u.x == b && u.y == bb) 
			return u.step;					 //�Ѿ����յ���
		for (size_t i = 0; i < 4; i++) { //����4 �����������չ
			int xx = u.x + dir[i][0];		//��������,��,��,��
			int yy = u.y + dir[i][1];
			if (xx <= 0 || xx > n || yy <= 0 || yy > n) //�������n*n����ı߿�,��Խ��
				continue;											   //������
			if (vis[xx][yy])										   //�����������Ѿ���������
				continue;											   //������
			v.step = u.step + 1;								   //����,����+1
			v.x = xx;												   //��ǰ��չ�������������һ���ĺ�������
			v.y = yy;
			vis[xx][yy] = 1;										   //�����������λ�ñ����ʹ���
			q.push(v);													//�ŵ�������,�´�������չ
		}
	}
	return -1;//�޽�
}
int main() {
	int x, y;													   //x y������
	while (scanf("%d%d", &n, &k) != EOF) {//���뷽��߳��ͷ���������
		memset(vis, 0, sizeof(vis));				   //������������
		while (!q.empty())								   //�����зǿ�
			q.pop();										   //��������
		while (k--) {										   //��������ķ���ĺ�������
			scanf("%d%d", &x, &y);					//�����ķ����൱�ڷ��ʹ�
			vis[x][y] = 1;										//��ʼ����������, 1��ʾ�Ѿ����ʹ�
		}
		scanf("%d%d%d%d", &a, &aa, &b, &bb);//���������յ�����
		Point u;													  //�������
		u.x = a, u.y = aa, u.step = 1;                      //��ʼ�����
		q.push(u);													  //�������������
		int ans = solve();										  //���ú���,Ѱ�����ٵķ�����
		printf("%d\n", ans);									  //�����
	}
}