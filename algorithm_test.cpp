#include <cstdlib>
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

//我的想法是算出该区域的总价值，将目标定为总价值的一半
//用一个前缀和数组记录，原始矩阵的行列和
//例如：[行1，行2，行3，列1，列2，列3]
//分别计算行相加和列相加哪一个更加接近总价值的一半

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> arr(n, vector<int>(m));
  int total_sum = 0;
  vector<int> rows(n, 0);
  vector<int> cols(m, 0);

  //读取数据并计算行和
  for (int i = 0; i < n; i++) 
  {
    for (int j = 0; j < m; j++) 
    {
      cin >> arr[i][j];
      rows[i] += arr[i][j];
      total_sum += arr[i][j];
    }
  }
  //计算列和
  for (int i = 0; i < m; i++) 
  {
    for (int j = 0; j < n; j++) 
    {
      cols[i] += arr[j][i];
    }
  }

  //寻找最优划分
  int min_diff = INT_MAX;
  int current_sum = 0;

  for (int i = 0; i < n - 1; i++) //至少留一行给对方
  {
    current_sum += rows[i];
    int diff = abs(2 * current_sum - total_sum);
    if(diff < min_diff)
    {
        min_diff = diff;
    }
  }

  current_sum = 0;
  for (int i = 0; i < m - 1; i++) //至少留一列给对方
  {
    current_sum += cols[i];
    int diff = abs(2 * current_sum - total_sum);
    if(diff < min_diff)
    {
        min_diff = diff;
    }
  }
  cout << min_diff << endl;
  return 0;
}

// 没有考虑到要留出一行给对方人员
// 没有想到用公式推导出最简洁的解法



/*
9/24
 */

//哨兵节点无需考虑头结点的情况
struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        //处理极端情况
        if(!head) return head;
        ListNode* dummy = new ListNode(0, head);
        ListNode* prev = dummy;
        ListNode* cur = head;

        while(cur)
        {
            if(cur->val == val)
            {
                //说明此时需要删除
                prev->next = cur->next;
                delete cur;
                cur = prev->next;
            }
            else
            {
                prev = prev->next;
                cur = cur->next;
            }
        }
        //哨兵节点的真正作用在于记录头结点，从而无需单独考虑删除头结点的情况
        ListNode* result = dummy->next;
        delete dummy;

        return result;
    }
};
//无哨兵节点需要考虑头结点
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {

        //删除头结点
        while(head != nullptr && head->val == val)
        {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
        ListNode* cur = head;
        //非头结点
        while(cur != nullptr && cur->next != nullptr)
        {
            if(cur->next->val == val)
            {
                ListNode* temp = cur->next;
                cur->next = cur->next->next;
                delete temp;
            }
            else
            {
                cur = cur->next;
            }
        }
        return head;
    }
};
//递归删除的策略
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if(!head) return nullptr;

        if(head->val == val)
        {
            ListNode* newNode =  removeElements(head->next, val);
            delete head;
            return newNode;
        }
        else
        {
            head->next = removeElements(head->next, val);
            return head;
        }
    }
};


