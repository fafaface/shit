#include <iostream>
#include <cmath>
#include <windows.h>
using namespace std;

struct point {
	double x;
	double y;
}p[10001];

struct point_pair {
	point a;
	point b;
}minest_pair;

double dist(point p, point q) {//�������
	double x = fabs(p.x - q.x);//������֮��
	double y = fabs(p.y - q.y);//������֮��
	return sqrt(x * x + y * y);
}

void bf(int n)//������
{
	int minpair[2]; minpair[0] = 0; minpair[1] = 0;
	double mindist=9999999;
	for (int i = 0; i < n - 1; ++i)
		for (int j = i + 1; j < n; ++j)
		{
			double distance = dist(p[i], p[j]);
			if (distance < mindist) {
				mindist = distance;
				minpair[0] = i; minpair[1] = j;
			}
		}
	cout << "��С������: " << mindist << endl;
	cout << "�������:" << "(" << p[minpair[0]].x << "," << p[minpair[0]].y << ") " << "(" << p[minpair[1]].x << "," << p[minpair[1]].y << ")" << endl;
}

/*���η�*/

point_pair bruteforce(int n)//������
{

	double mindist = 9999999;
	point_pair ans;
	for (int i = 0; i < n - 1; ++i)
		for (int j = i + 1; j < n; ++j)
		{
			double distance = dist(p[i], p[j]);
			if (distance < mindist) {
				mindist = distance;
				ans.a = p[i]; ans.b = p[j];
			}
		}
	return ans;
}

point_pair closest_div(int n) {
	if (n <= 3) {
		return bruteforce(n);//ʣ�¼�����,��ֱ��������
	}
	int mid = n / 2;//�ҵ��м�ָ��
	point mid_point = p[mid];
}
double  divide_concuer(int n) {//���η��ܺ���
	qsort(p, n, sizeof(point), cmp);//����x����������
	return closest_div(n);//���η� ������԰�ֵݹ�
}
int main(){
	int n;//����
	cout << "�����Եĸ���: ";
	while (scanf("%d",&n)!=EOF&&n) {//���Ϊ0 ,�������
		cout << "����" << n << "����Ե�x��y���ꡣ" << endl;
		for (int i = 0; i < n; ++i) {
			scanf("%lf%lf", &p[i].x, &p[i].y);//�������Լ��̵�n���������
		}
		LARGE_INTEGER c1;//��ʼ��ʱ
		LARGE_INTEGER c2;//������ʱ
		LARGE_INTEGER frequency;//��ʱ��Ƶ��
		QueryPerformanceFrequency(&frequency);
		double quadpart = (double)frequency.QuadPart;
		QueryPerformanceCounter(&c1);
		bf(n);//������,��Ҫ��ʱ���޸ĳɷ��η�
		QueryPerformanceCounter(&c2);
		cout << "�߾��ȼ�������ʱ��" << (double)((c2.QuadPart - c1.QuadPart) * 1.0 / quadpart * 1.0) * 1000000 << endl;
	}
	return 0;
}