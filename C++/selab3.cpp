#include<stdio.h>//ͷ�ļ�
/*3.����̰���㷨, ���� ������ֵ����, �ɹ��������ֵ������,
*  �˿�ʵ��֧�������Ӧ����Ʒ�ܽ��֮��
*/
void GreedMoney(int m[], int k, int n) {
	if (n == 0) {
		printf("������Ǯ!\n"); return;
	}
	printf("%s", n > 0 ? "Ӧ����" : "�˿͸�Ǯ����!");

	int num[] = { 0,0,0,0 };
	int money[] = { 50,10,5,1 };//��ſɹ��������ֵ����������
	for (int i = 0; i < k; i++)
		while (n >= m[i]) {//��Ӧ�ҽ����ڵ�ǰ���������
			switch (m[i]) {
			case 50:
				num[0]++;  break;
			case 10:
				num[1]++;  break;
			case 5:
				num[2]++;  break;
			case 1:
				num[3]++;  break;
			}
			n = n - m[i];//����Ѱ�ҹ˿�ʣ���Ǯ
		}
	for (int j = 0; j < 4; ++j)//�����ʾ
		if (num[j] > 0)
			printf("%d��%dԪ ", num[j], money[j]);
	printf("\n");
}
/*4. �����ַ�����������ַ�����ʼλ��,
*  ����λ��, ������ַ�������
*/
int  change(int beg, int pos,  char s[]) {//�ַ�ת��Ϊ����
	int j = beg;
	int num = 0;
	while (j < pos) {
		num = num * 10 + (s[j++] - '0');
	}
	return num;
}
int main() {
	/*
	* 1. �������
	*/
	int money[] = { 50,10,5,1 };//��ſɹ��������ֵ����������
	int k = sizeof(money) / sizeof(money[0]);//�ɹ��������ֵ������

	/*
	* 2. ��whileѭ����, ÿ��ѭ������һ������Ǯ�Ĳ���
	*/
	while (1) {
		int real = 0, input = 0;//Ӧ����Ʒ�ܽ��, �˿͸��Ľ��
		char s[101];
		int gap = 0, end = 0;//����������ּ����λ��
		printf("����Ӧ����Ʒ�ܽ��͹˿�ʵ��֧�����, �ÿո����: \n");
		gets_s(s);//��ȡ�ַ���

		for (int i = 0; i < 101; ++i) {//����
			if (s[i] == ' ')
				gap = i;
			if (s[i] == '\0') {
				end = i;
				break;
			}
		}
		real = change(0, gap, s);//Ӧ����Ʒ�ܽ��
		input = change(gap + 1, end,  s);//�˿�ʵ��֧�����

		printf("%d %d", real, input);//����Ӧ����Ʒ�ܽ��, �˿͸��Ľ��
		if (real > 100 || input > 100 || real <= 0 || input <= 0) {
			printf("�Ƿ�����!\n");
			continue;
		}
		GreedMoney(money, k, input - real);//����ɹ�������ֵ�Ļ��Ҵ�С, ��������, �˿͸�Ǯ���, Ѱ��������㷽��
	}

}