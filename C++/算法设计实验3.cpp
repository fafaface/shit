#include <iostream>
#include <cmath>
#include <windows.h>
#include<algorithm>
using namespace std;

struct point {
	double x;
	double y;
};

struct point_pair {
	point a;
	point b;
}minest_pair;

double dist(point p, point q) {//�������
	double x = fabs(p.x - q.x);//������֮��
	double y = fabs(p.y - q.y);//������֮��
	return sqrt(x * x + y * y);
}

void bf(point p[], int n)//������
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

bool cmpx(point a, point b) {//�Ƚ�x�������С
	return a.x > b.x;
}
bool cmpy(point a, point b) {//�Ƚ�y�������С
	return a.y > b.y;
}
point_pair min_pair(point_pair m, point_pair n) {//�Ƚ�����������ĸ�����
	return dist(m.a, m.b) > dist(n.a, n.b) ? n : m;
}


point_pair bruteforce(point p[],int n)//������
{
	double mindist = 9999999;//��ʼ��Ϊ���ֵ
	point_pair ans;
	ans.a = p[0]; ans.b = p[1];
	for (int i = 0; i < n - 1; ++i)
		for (int j = i + 1; j < n; ++j)//һһ�Ƚ�
		{
			double distance = dist(p[i], p[j]);
			if (distance < mindist) {
				mindist = distance;
				ans.a = p[i]; ans.b = p[j];//���������
			}
		}
	return ans;//���������
}

point_pair closest_strip(point strip[], int size, point_pair d) {
	double mind = dist(d.a,d.b);
	sort(strip, strip + size, cmpy);
	for (int i = 0; i < size; ++i) {
		for(int j=i+1;j<size&&(strip[j].y-strip[i].y)<mind;++j)
			if (dist(strip[i], strip[j]) < mind)
			{
				mind = dist(strip[i], strip[j]);
				d.a = strip[i];
				d.b = strip[j];
			}
	}
	return d;
}
point_pair closest_div(point p[],int n) {
	if (n <= 3) {
		return bruteforce(p,n);//ʣ�¼�����,��ֱ��������
	}
	int mid = n / 2;//�ҵ��м�ָ��
	point mid_point = p[mid];
	point_pair disleft=closest_div(p,mid);//����
	point_pair disright = closest_div(p+mid,n-mid);//�Ұ��
	point_pair d1 = min_pair(disleft, disright);//�ۺ���������

	point* strip = new point[n];
	int j = 0;
	for (int i = 0; i < n; ++i) {
		if (fabs(p[i].x - mid_point.x) < dist(d1.a, d1.b))
			strip[j++] = p[i];
	}
	return min_pair(d1, closest_strip(strip, j, d1));
}
point_pair divide_conquer(point p[],int n) {//���η��ܺ���
	sort(p,p+n,cmpx);//����x����������
	return closest_div(p,n);//���η� ������԰�ֵݹ�
}



int main(){
	int n;//����
	point p[10001];
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
	//	bf(n);//������,��Ҫ��ʱ���޸ĳɷ��η�
		point_pair ans = divide_conquer(p,n);
		cout << "�������:" << "(" << ans.a.x << "," << ans.a.y << ") " << "(" << ans.b.x << "," << ans.b.y << ")" << endl;
		QueryPerformanceCounter(&c2);
		cout << "�߾��ȼ�������ʱ��" << (double)((c2.QuadPart - c1.QuadPart) * 1.0 / quadpart * 1.0) * 1000000 << endl;
	}
	return 0;
}