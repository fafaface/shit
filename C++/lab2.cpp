#include <iostream>
#include <time.h>
#include <stdio.h> 
#include <set>
#include <string>
#include<vector>
#include <dos.h> 
#include <windows.h>
#include<fstream>
using namespace std;
int BF(char s[], char t[]) {
	int index = 0;//��ʼ������
	int i = 0, j = 0;
	while ((s[i] != '\0') && (t[j] != '\0'))//�������ַ����±궼û�е��ַ�������λ��
	{
		if (s[i] == t[j]) { i++; j++; }//���,�±궼����ƶ�һλ
		else {
			index++; i = index; j = 0;//�����,ԭʼ�ַ����±�����ƶ�һλ,��ѯ�ַ�����ͷ����Ѱ��
		}
	}
	if (t[j] == '\0') return index + 1;//������ҵ��ַ����Ѿ���ĩβ��,˵��ƥ��ɹ�
	else return 0;//û�е�ĩβ,˵��ԭʼ�ַ����Ѿ��������,����û����Ҫ���ҵ��ַ���
}

void GetNext(char T[], int next[])
{
	int j = 0, k = -1;
	next[0] = -1;
	while (T[j] != '\0')              	//ֱ���ַ���ĩβ
	{
		if (k == -1) {               	//����ͬ�Ӵ�
			next[++j] = 0; k = 0;
		}
		else if (T[j] == T[k]) {        	//ȷ��next[j+1]��ֵ
			k++;               		//����Ӵ����ȼ�1
			next[++j] = k;
		}
		else k = next[k];        	//ȡT[0]��T[j]����һ������Ӵ��ĳ���
	}
}
int nex[99999999];
int KMP(char s[], char t[]) {
	int i = 0, j = 0;
	while ((s[i] != '\0') && (t[j] != '\0'))
	{
		if (s[i] == t[j]) { i++; j++; }
		else j = nex[j];//j����
		if (j == -1) {
			i++; j++;
		}
	}
	if (t[j] == '\0') return i - strlen(t) + 1;//ƥ��ɹ��������Ӵ���λ��
	else return 0;//û�ҵ�
}

int Dist(char t[], char c)//�������뺯��
{
	int len = strlen(t);
	int i = len - 1;
	if (c == t[i])
		return len;
	i--;
	while (i >= 0){
		if (c == t[i])
			return len - 1 - i;
		else
			i--;
	}
	return len;
}

int BM(char S[], char T[])
{
	int n = strlen(S);	int m = strlen(T);
	int i = m - 1;int j = m - 1;
	while (j >= 0 && i < n){//������i����
		if (S[i] == T[j]){//ƥ��
			i--;j--;
		}
		else{//��ƥ��
			i += Dist(T, S[i]);//���ֲ�ƥ��,��ʼ��һ��ƥ��
			j = m - 1;
		}
	}
	if (j < 0)
		return i + 1;
	return -1;
}



int main()
{
	ifstream myfile("C:/Users/yuehan lian/Desktop/123.txt");
	char input[999999];
	char search[1001];
	int i = 0;
	while (!myfile.eof()) //ֱ���ļ���β
	{
		myfile >> input[i++];
	}
	myfile.close();
	//cout << "��������input ";
	//cin >> input;
	//search[0] = 'c'; search[1] = 'a'; search[2] = 'd'; search[3] = 'a'; search[4] = 'b'; search[5] = '\0';
	cout << "����ģʽsearch: ";
	cin >> search;
	memset(nex, 0, sizeof(nex));
	GetNext(search, nex);
	LARGE_INTEGER c1;//��ʼ��ʱ
	LARGE_INTEGER c2;//������ʱ
	LARGE_INTEGER frequency;//��ʱ��Ƶ��
	QueryPerformanceFrequency(&frequency);
	double quadpart = (double)frequency.QuadPart;
	QueryPerformanceCounter(&c1);
	int ans =BF(input, search);//�˴����滻ΪKMP,BM����
	QueryPerformanceCounter(&c2);
	cout << "λ��: " << ans << endl;
	cout << "�߾��ȼ�������ʱ��" << (double)((c2.QuadPart - c1.QuadPart) * 1.0 / quadpart * 1.0) * 1000000 << endl;
	return 0;
}