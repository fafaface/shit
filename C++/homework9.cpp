#include <iostream>
using namespace std;
#define num 3     //��Ŀ
#define INIT -1000  //��ʼֵ
int a[num];    //����
void print()    //��ӡ��
{
	int i;
	for (i = 0; i < num; ++i)
		printf("%d ", a[i]);
	printf("\n");
}


int Place(int row, int col)    //�жϵ�row�е�col���Ƿ���Է��ûʺ�
{
	for (int i = 0; i < num; ++i)   //�����̽���ɨ��
	{
		if (a[i] == col || abs(i - row) == abs(a[i] - col))   //�ж��к�б���Ƿ��г�ͻ
			return 0;
	}
	return 1;
}

void Queen() 
{
	bool flag = 0;//�жϵ���û����
	int n = 0;
	int i = 0, j = 0;
	while (i < num)
	{
		while (j < num)        //��i�е�ÿһ�н��в鿴�����Ƿ���Է��ûʺ�
		{
			if (Place(i, j))      //���Է��ûʺ�
			{
				a[i] = j;        //��i�з��ûʺ�
				j = 0;           //��i�з��ûʺ�ȷ����һ�еĻʺ�λ�ã����Դ˴���j���㣬����һ�еĵ�0�п�ʼ���в鿴
				break;
			}
			else ++j;             //����ֵΪ0, ˵������, �����鿴��һ��
		}
		if (a[i] == INIT)         //��i��û�н�
		{
			if (i == 0)             //���ݵ���һ��,˵���Ѿ��ҵ����еĽ�
				break;
			else                    //û���ҵ����Է��ûʺ����,����
			{
				--i;
				j = a[i] + 1;        //����һ�лʺ��λ��������һ��
				a[i] = INIT;      //����һ�лʺ��λ�����������̽��
				continue;
			}
		}
		if (i == num - 1)          
		{
			flag = 1;
			printf("%d : \n", ++n);print();//���һ���ҵ���λ�� ,��ӡ���
			j = a[i] + 1;             //�����һ�з��ûʺ���������һ�м���̽��
			a[i] = INIT;           //������һ�еĻʺ�λ��
			continue;
		}
		++i;              //�����鿴��һ�еĻʺ�λ��
	}
	if(!flag)
		cout << "�޽�" << endl;
}

int main(void)
{
	for (int i = 0; i < num; ++i)//��ʼ��
		a[i] = INIT;
	Queen();
	return 0;
}