#include <map>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

int sum = 0;//
int n;
int num = 0;//能组成几组木棒
int l;//每组木棒的长度
pair<int, int> sticks[100];//first:lengh second:是否使用过
int dfs(int s, int len, int pos)//s 已组成的木棒数目,len已经组成的长度，pos搜索的木棒的下标的位置
{
    if (s == num)return l;
    for (int i = pos + 1; i < n; i++)
    {

        if (sticks[i].second)continue;//已经使用过 继续搜索
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
            sticks[i].second = false;//剪枝

            if (len == 0)return false;//剪枝

            while (sticks[i].first == sticks[i + 1].first)i++;
        }
    }
    return false;
}

int cmp(pair<int, int> a, pair <int, int> b) //按长度从大到小排序
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

        for (l = sticks[0].first; l <= sum; l++)//剪枝
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