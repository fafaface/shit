#include <iostream>
#include <time.h>
#include <stdio.h> 
#include <set>
#include<vector>
#include<map>
#include<cmath>
using namespace std;

 struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };

 void deleteNode(ListNode* node) {
     node->val = node->next->val;
     node->next = node->next->next;
 }
int main()
{
	vector<vector<char>> v1;
	vector<char> v2;
	int n;    printf("链表结点数: \n");
    int x;
    while (scanf("%d", &n) && n) {
        ListNode* list=NULL;
        ListNode* node
        list->next = node;
        node->next = NULL;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &x);
            ListNode* pos;
            pos->next = NULL;
            pos->val = x;
            node->next = pos;
            node = pos;
        }

        deleteNode(list);

        printf("链表结点数: \n");
    }


	return 0;
}
