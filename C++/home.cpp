#include <iostream>
#include <time.h>
#include <stdio.h> 
#include <set>
#include <string>
#include<vector>
#include <dos.h> 
#include <windows.h>
using namespace std;
void digui_search(int min, int max, int a[], int low, int high)
{
    int mid;
    mid = (low + high) / 2;
    if (a[mid] < min)
        digui_search(min, max, a, mid, high);
    else if (a[mid] > max)
        digui_search(min, max, a, low, mid);
    else
    {
        for (int i = mid; a[i] >= min && i >= low; i--) cout << a[i] << " ";
        for (int j = mid + 1; a[j] <= max && j <= high; j++)  cout << a[j] << " ";
    }
}

int main()
{
    int a[1001];
    cout << "输入数字个数: ";
    int n;
    cin >> n;
    for(int i=0;i<n;++i)
    {
        cin >> a[i];
    }
    int min, max;
    cout << "输入范围min max: " << min << max;

    digui_search(min,max,a,0,n-1);
	return 0;
}