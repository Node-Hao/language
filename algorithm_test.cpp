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
// struct ListNode {
//       int val;
//       ListNode *next;
//       ListNode() : val(0), next(nullptr) {}
//       ListNode(int x) : val(x), next(nullptr) {}
//       ListNode(int x, ListNode *next) : val(x), next(next) {}
//  };
// class Solution {
// public:
//     ListNode* removeElements(ListNode* head, int val) {
//         //处理极端情况
//         if(!head) return head;
//         ListNode* dummy = new ListNode(0, head);
//         ListNode* prev = dummy;
//         ListNode* cur = head;

//         while(cur)
//         {
//             if(cur->val == val)
//             {
//                 //说明此时需要删除
//                 prev->next = cur->next;
//                 delete cur;
//                 cur = prev->next;
//             }
//             else
//             {
//                 prev = prev->next;
//                 cur = cur->next;
//             }
//         }
//         //哨兵节点的真正作用在于记录头结点，从而无需单独考虑删除头结点的情况
//         ListNode* result = dummy->next;
//         delete dummy;

//         return result;
//     }
// };
// //无哨兵节点需要考虑头结点
// class Solution {
// public:
//     ListNode* removeElements(ListNode* head, int val) {

//         //删除头结点
//         while(head != nullptr && head->val == val)
//         {
//             ListNode* temp = head;
//             head = head->next;
//             delete temp;
//         }
//         ListNode* cur = head;
//         //非头结点
//         while(cur != nullptr && cur->next != nullptr)
//         {
//             if(cur->next->val == val)
//             {
//                 ListNode* temp = cur->next;
//                 cur->next = cur->next->next;
//                 delete temp;
//             }
//             else
//             {
//                 cur = cur->next;
//             }
//         }
//         return head;
//     }
// };
// //递归删除的策略
// class Solution {
// public:
//     ListNode* removeElements(ListNode* head, int val) {
//         if(!head) return nullptr;

//         if(head->val == val)
//         {
//             ListNode* newNode =  removeElements(head->next, val);
//             delete head;
//             return newNode;
//         }
//         else
//         {
//             head->next = removeElements(head->next, val);
//             return head;
//         }
//     }
// };


#include <iostream>
#include <deque>
#include <vector>
// //把 deque 当做是滑动窗口，往窗口中塞入元素的同时也要比较大小，当前元素与窗口末尾的进行比较

// void slidingWindowMaximum(const std::vector<int>& nums, int k) {
//     std::deque<int> window;
    
//     for (size_t i = 0; i < nums.size(); ++i) {
//         // 移除窗口左边界之外的元素
//         if (!window.empty() && window.front() == i - k) {
//             window.pop_front();
//         }
        
//         // 保持 `deque` 的递减顺序
//         while (!window.empty() && nums[i] > nums[window.back()]) {
//             window.pop_back();
//         }
        
//         // 添加当前元素的索引
//         window.push_back(i);
        
//         // 从窗口开始时输出最大值
//         if (i >= k - 1) {
//             std::cout << nums[window.front()] << " ";
//         }
//     }
//     std::cout << std::endl;
// }
// class MyLinkedList {
// public:
//     struct LinkedNode{
//         int val;
//         LinkedNode* next;
//         LinkedNode(int val): val(val), next(nullptr){}
//     };
//     //初始化链表
//     MyLinkedList() {
//         //需要一个哨兵节点
//         dummy = new LinkedNode(0);
//         size = 0;
//     }
    
//     int get(int index) {
//         if(index < 0 || index >= size)
//         {
//             return -1;
//         }
//         //拿到头结点
//         LinkedNode* cur = dummy->next;
//         while(index--)
//         {
//             cur = cur->next;
//         }
//         return cur->val;
//     }
    
//     void addAtHead(int val) {
//         //头插法
//         LinkedNode* newNode = new LinkedNode(val);
//         newNode->next = dummy->next;
//         dummy->next = newNode;
//         ++size;
//     }
    
//     void addAtTail(int val) {
//         //尾插法
//         LinkedNode* newNode = new LinkedNode(val);
//         LinkedNode* cur = dummy;//有可能为空链表
//         while(cur->next)
//         {
//             cur = cur->next;
//         }
//         cur->next = newNode;
//         ++size;        
//     }
    
//     void addAtIndex(int index, int val) {
//         if(index > size) return;
//         if(index < 0) index = 0;
//         LinkedNode* newNode = new LinkedNode(val);
//         LinkedNode* cur = dummy;
//         while(index--)
//         {
//             cur = cur->next;
//         }
//         newNode->next = cur->next;
//         cur->next = newNode;
//         ++size;
//     }
    
//     void deleteAtIndex(int index) {
//         if(index < 0 || index >= size) return;
//         //任意位置删除
//         LinkedNode* cur = dummy;
//         while(index--)
//         {
//             cur = cur->next;
//         }
//         //此时 cur 走到了待删除节点的前一个位置，需要记录待删除节点的下一个位置
//         LinkedNode* tmp = cur->next;
//         cur->next = tmp->next;
//         delete tmp;
//         tmp = nullptr;
//         --size;
//     }
// private:
//     LinkedNode* dummy;
//     size_t size; 
// };

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */


//反转链表的三种做法
//双指法
struct ListNode {
    int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head || !head->next) return head;
        //先把两个节点的情况搞定
        ListNode* cur = head->next;
        ListNode* prev = head;
        ListNode* tmp = cur->next;
        prev->next = nullptr;
        cur->next = prev;
        while(tmp)
        {
            prev = cur;
            cur = tmp;
            tmp = cur->next;
            cur->next = prev;
        }
        return cur;
    }
};
//模拟双指针的递归法

