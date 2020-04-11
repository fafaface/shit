#include <map>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

int sum = 0;//
int n;
int num = 0;//����ɼ���ľ��
int l;//ÿ��ľ���ĳ���
pair<int, int> sticks[100];//first:lengh second:�Ƿ�ʹ�ù�
int dfs(int s, int len, int pos)//s ����ɵ�ľ����Ŀ,len�Ѿ���ɵĳ��ȣ�pos������ľ�����±��λ��
{
    if (s == num)return l;
    for (int i = pos + 1; i < n; i++)
    {

        if (sticks[i].second)continue;//�Ѿ�ʹ�ù� ��������
        if (len + sticks[i].first == l)
        {
            sticks[i].second = true;
            if (dfs(s + 1, 0, -1))return true;
            sticks[i].second = false;
            return false;
        }
        else if (sticks[i].first + len < l) {
            sticks[i].second = true;
            if (dfs(s, len + sticks[i].first, i))
                return true;
            sticks[i].second = false;//��֦

            if (len == 0)return false;//��֦

            while (sticks[i].first == sticks[i + 1].first)i++;
        }
    }
    return false;
}

int cmp(pair<int, int> a, pair <int, int> b) //�����ȴӴ�С����
{
    return a.first > b.first;
}


int main()
{
    int num;
    while (cin >> n && n)
    {
        sum = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> sticks[i].first;
            sum += sticks[i].first;
            sticks[i].second = 0;
        }
        sort(sticks, sticks + n, cmp);

        for (l = sticks[0].first; l <= sum; l++)//��֦
        {
            if (sum % l != 0)
                continue;

            else num = sum / l;//number of sticks before chopping
            if (dfs(1, 0, -1))
            {
                cout << l << endl;
                break;
            }

        }


    }
    return 0;
}