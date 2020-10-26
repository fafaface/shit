#include<iostream>
using namespace std;
int score[5][5] = {//�γ̵ĸ�ϰ��������߷����Ĺ�ϵ
	0,0,0,0,0,
	0,4,3,5,2,//��, ��һ�д���ϰ1��, �γ�1~4��ߵķ���
	0,4,5,6,4,//score[i][[j]����ϰi��, �γ�j��ߵķ���
	0,5,6,8,7,
	0,8,7,8,8,
};
int pattern[8][5] = {//����Ҫ��Ŀγ̰��ŵ��߷�
	0,0,0,0,0,
	0,4,1,1,1,//��,pattern[i][j]����˴������Ĵ���˳������ſγ�, ����4,1,1,1��ֱ����
	0,3,2,1,1,
	0,1,1,3,2,
	0,1,1,2,3,
	0,1,3,1,2,
	0,1,3,2,1,
	0,1,2,2,2,
};

int day;//�����ճ̰�����pattern[day]�еİ��ŷ�ʽ
bool vis[5];//vis[i]����γ�i�Ƿ��Ѿ�������
int sche[5] = { 0 };//sche��ʾschedule, sche[i]����γ�i��ϰ����

//day��ʾ�γ̰��ŵ��߷�(1-6), course��ʾ�γ�1,2,3,4, pos��ʾ�γ̰����߷����˵ڼ��ſ���, ans��ʾĿǰ�ۻ��ķ���
int dp( int day,int course,int pos, int ans)
{//����courseÿ�δ�ֵ��Ϊ1, �����Ǵӿγ�1��ʼ������
	while (vis[course] == 1) {//�����ǰ�γ��Ѿ������Ź���
		course++;//���ּ�һ, �ֵ���һ�ſ�
		if (course == 5)//���course==5, ˵����ʵ���ڵĿγ�1-4�Ѿ����������
			return ans;//����Ŀǰ�ۻ�����߷���
	} 
	vis[course]= 1;//������ſα����Ÿ�ϰ��
	sche[course] = pattern[day][pos];//��¼��ογ�course���Ÿ�ϰ������ pattern[day][pos]
	ans = dp(day, 1,pos+1,ans+score[pattern[day][pos]][course]);
	return ans;//����Ŀǰ�ۻ�����߷���
}
int main()
{
	int ans,maxn;
	int cnt = 1;
	maxn = 0;//��ʼ�����ֵ
	int maxsche[5] = { 0 };//��ʼ���������µĿγ̰���
	for (int p = 1; p < 8; p++){
		for (int i = 1; i < 5; ++i){
			ans = 0;//��ʼ�����ΰ��ŵ���߷���
			memset(vis, 0, sizeof(vis));//��ʼ���γ��Ƿ��Ѱ��ű��
			memset(sche, 0, sizeof(sche));//��ʼ�������γ̰�������
			vis[i]= 1;//��¼�ÿγ̱�����
			sche[i] = pattern[p][1];//��¼�ÿγ̱����ŵ�����
			ans = dp(p,1,2, ans+score[pattern[p][1]][i]);
			printf("%d: %d\n",cnt++, ans);
			if (maxn < ans){//�����ǰֵ����Ŀǰ�����ֵ
				maxn = ans;//�������ֵ
				for (int j = 0; j < 5; j++)
					maxsche[j] = sche[j];//�����������µĸ�ϰʱ�䰲��
			}
		}
	}
	printf("���ֵΪ%d\n", maxn);
	for (int j = 1; j < 5; j++)
		printf("�γ�%d��ϰ%d��\n", j, maxsche[j]);
	return 0;
}
