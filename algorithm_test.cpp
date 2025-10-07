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


// //反转链表的三种做法
// //双指法
struct ListNode {
    int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};
// class Solution {
// public:
//     ListNode* reverseList(ListNode* head) {
//         if(!head || !head->next) return head;
//         //先把两个节点的情况搞定
//         ListNode* cur = head->next;
//         ListNode* prev = head;
//         ListNode* tmp = cur->next;
//         prev->next = nullptr;
//         cur->next = prev;
//         while(tmp)
//         {
//             prev = cur;
//             cur = tmp;
//             tmp = cur->next;
//             cur->next = prev;
//         }
//         return cur;
//     }
// };
//模拟双指针的递归法
//从后往前的递归法
// class Solution {
// public:
//     ListNode* reverseList(ListNode* head) {
//         if(!head || !head->next) return head;

//         //只用操心当前节点的事，剩余节点交给后面的人做
//         ListNode* last = reverseList(head->next);
//         //last 记录后一个节点
//         head->next->next = head;
//         head->next = nullptr;
//         return last;
//     }
// };
// //模拟双指针的递归法
// class Solution {
// public:
//     ListNode* reverse(ListNode* pre,ListNode* cur){
//         if(cur == NULL) return pre;
//         ListNode* temp = cur->next;
//         cur->next = pre;
//         // 可以和双指针法的代码进行对比，如下递归的写法，其实就是做了这两步
//         // pre = cur;
//         // cur = temp;
//         return reverse(cur,temp);
//     }
//     ListNode* reverseList(ListNode* head) {
//         // 和双指针法初始化是一样的逻辑
//         // ListNode* cur = head;
//         // ListNode* pre = NULL;
//         return reverse(NULL, head);
//     }
// };



// //两两交换链表节点
// class Solution {
// public:
//     ListNode* swapPairs(ListNode* head) {
//         //涉及到对虚拟头结点的深刻理解
//         //1.无需考虑临界情况 2.无需额外记录头结点
//         ListNode* dummy = new ListNode(0);
//         dummy->next = head;
//         ListNode* prev = dummy;
//         //保证始终有两组可以交换
//         while(prev->next && prev->next->next)
//         {
//             //记录交换节点
//             ListNode* first = prev->next;
//             ListNode* second = prev->next->next;
//             //开始交换
//             first->next = second->next;
//             second->next = first;
//             prev->next = second;
//             //走到下一组节点之前
//             prev = first;
//         }
//         ListNode* result = dummy->next;
//         delete dummy;
//         return result;
//     }
// };

//删除倒数第 N 个节点
// class Solution {
// public:
//     ListNode* removeNthFromEnd(ListNode* head, int n) {
//         if(!n) return head;
//         ListNode* fast = head;
//         ListNode* slow = head;
//         ListNode* dummy = new ListNode(0);
//         dummy->next = head;//无需考虑特殊情况
//         ListNode* prev = dummy;
//         while (n - 1)// 让前一个指针走 n - 1步
//         {
//             fast = fast->next;
//             --n;
//         }
//         while (fast->next)// 每个点都走到对的位置
//         {
//             prev = slow;
//             fast = fast->next;
//             slow = slow->next;
//         }
//         // 删除 slow 节点
//         prev->next = slow->next;
//         return dummy->next;
//     }
// };
// 首先要意识到如何找到链表的倒数第N个节点和前一个节点
// 我的想法在于用前后指针之间的差距，当前指针到末尾时，之间的差距为 n - 1，那么后指针就在倒数第n个节点的位置，想要删除该节点还得有一个记录该节点前一项的指针

// 链表相交
// class Solution {
// public:
//     ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
//         if (!headA || !headB) return nullptr;
//         size_t A_len = 0;
//         size_t B_len = 0;
//         size_t diff = 0;
//         ListNode *curA = headA;
//         ListNode *curB = headB;

//         while (curA)
//         {
//             ++A_len;
//             curA = curA->next;
//         }

//         while (curB)
//         {
//             ++B_len;
//             curB = curB->next;
//         }
//         curA = headA;
//         curB = headB;

//         if (A_len > B_len)
//         {
//             diff = A_len - B_len;
//             while (diff--)
//             {
//                 curA = curA->next;
//             }
//         }else if (B_len > A_len)
//         {
//             diff = B_len - A_len;
//             while (diff--)
//             {
//                 curB = curB->next;
//             }
//         }

//         while (curA != curB)
//         {
//             curA = curA->next;
//             curB = curB->next;
//         }

//         if (curA == curB)
//         {
//             return curA;
//         }

//     }
// };
// 我的想法是记录每一个链表的长度，例如：A 为 5 , B 为 6 那么之间的差值为 1
// 让 B 先走一步，之后两个指针一起走，相交的点就是交点，否则没有交点

// 环形链表 II
// class Solution {
// public:
//     ListNode *detectCycle(ListNode *head) {
//         if (!head || !head->next) return nullptr;
//         // 先找到 快慢指针相遇点
//         ListNode *fast = head;
//         ListNode *slow = head;
//         while (fast  && fast->next ) 
//         {
//             fast = fast->next->next;
//             slow = slow->next;
//             if (fast == slow) break;
//         }
//         if (!fast || !fast->next) return nullptr;
//         // 此时找到相遇节点
//         ListNode *meet = fast;
//         ListNode *first = head;
//         while (first != meet)
//         {
//             first = first->next;
//             meet = meet->next;
//         }
//         return first;
//     }
// };

// 异位字母
// class Solution {
// public:
//     bool isAnagram(string s, string t) {
//         int arr[26] = {0};
        
//         size_t a_len = s.length();
//         size_t b_len = t.length();
//         if (a_len != b_len) return false;

//         for (size_t i = 0; i < a_len; i++)
//         {
//             char c = s.at(i);
//             arr[c - 'a'] += 1;
//         }

//         // 此时检查 t 的情况
//         for (size_t i = 0; i < a_len; i++)
//         {
//             char c = t.at(i);
//             arr[c - 'a'] -= 1;
//         }
         
//         // 此时检查是否是异位词
//         for (size_t i = 0; i < 26; i++)
//         {
//             if (arr[i] != 0)
//             {
//                 return false;
//             }
//         }
//         return true;
//     }
// };
// 也就是说只要把 s 存到 hash 表里，判断 t 是否存在即可
// 当前的疑问只要在于，如何操作unorder_set, 以及查询是键的返回值是什么？
// 如果不使用 hash 表，也可以实在数组来模拟

// 之后发现，可能会有重复的情况。 因此我考虑，用 t 中的元素去减去 s 中的元素
// 如果均为 0，如果数组最终为 0，那么就是字母异位词

// 两个数组的交集
// class Solution {
// public:
//     vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
//         unordered_set<int> nums1_set(nums1.begin(), nums1.end());
//         unordered_set<int> result_set;//存储交集结果去重

//         for (int elem : nums2)
//         {
//             if (nums1_set.find(elem) != nums1_set.end())
//             {
//                 result_set.insert(elem);
//             }
//         }
//         return vector<int>(result_set.begin(), result_set.end());
//     }
// };

//快乐数 Floyed 判圈法
// class Solution {
// public:
//     bool isHappy(int n) 
//     {
//         int slow = n;
//         int fast = getNext(n);
//         while (fast != 1 && fast != slow)
//         {
//             slow = getNext(slow);
//             fast = getNext(getNext(fast));
//         }
//         return fast == 1;
//     }
//     int getNext(int num)
//     {
//         int sum = 0;
//         while (num > 0)
//         {
//             int digit = num % 10;
//             sum += digit * digit;
//             num /= 10;
//         }
//         return sum;
//     }
// };

// class Solution {
// public:
//     vector<int> twoSum(vector<int>& nums, int target) {
//         unordered_map<int, int> map;
//         vector<int> result;
//         for (int i = 0; i < nums.size(); i++)
//         {
//             int num = nums[i];
//             int diff = target - num;
//             if (map.find(diff) != map.end())
//             {
//                 // 此说明找到了
//                 result.push_back(i);
//                 result.push_back(map[diff]);
//                 return result;
//             }
//             map.insert({num, i});
//         }
//         return result;
//     }
// };
// 常规思路通常为 两重 for 循环
// 但我更想和 hash 表建立联系
// hash 表的作用在于去重和查找以及存在的元素

// 四数之和
// class Solution {
// public:
//     int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4)
//     {
//         unordered_map<int, int> map;
//         int result = 0;

//         // 计算第一组的和
//         for (int a : nums1)
//         {
//             for (int b : nums2)
//             {
//                 int sum1 = a + b;
//                 // 无论map是否存在，value都要++
//                 map[sum1] += 1;
//             }
//         }

//         for (int a : nums3)
//         {
//             for (int b : nums4)
//             {
//                 int sum2 = a + b;
//                 // 计算 sum2 的相反数，在 hash 表中查找该值
//                 auto it = map.find(-sum2);
//                 if (it != map.end())
//                 {
//                     result += it->second;  // 直接通过迭代器获取值，减少一次查找
//                 }
//             }
//         }
//         return result;
//     }
// };
// 使用 hash 表将四重 for 循环简化为两重
// 四个数组分为两组，判断两组数组是否能够互补

// 赎金信
// class Solution {
// public:
//     bool canConstruct(string ransomNote, string magazine) {
//         unordered_map<char, int> map1;
//         unordered_map<char, int> map2;

//         for (char c : ransomNote)
//         {
//            map1[c]++;
//         }

//         for (char c : magazine)
//         {
//             map2[c]++;
//         }
//         // 现在只需判断 map2 是否能满足 map1
//         for (auto& pair : map1)
//         {
//             char c = pair.first;
//             int need = pair.second;
//             if (map2[c] < need) return false;
//         }
//         return true;
//     }
// };
// 字符为key 出现次数为 value

// 三数之和
// class Solution {
// public:
//     vector<vector<int>> threeSum(vector<int>& nums) {
//         vector<vector<int>> result;
//         int n = nums.size();
//         if (n < 3) return result;
//         sort(nums.begin(), nums.end());

//         for (int i = 0; i < nums.size(); i++)
//         {
//             // 如果第一个元素大于0，说明三元组必定大于0
//             if (nums[i] > 0) return result;
//             // 去重，确保第一个三元组不重复
//             if (i > 0 && nums[i] == nums[i - 1]) continue;
//             int left = i + 1;
//             int right = n - 1;

//             while (left < right)
//             {
//                 int sum = nums[i] + nums[left] + nums[right];
//                 if (sum == 0)
//                 {
//                     // 因为排序的缘故，三元组不可能重复
//                     result.push_back({nums[i], nums[left], nums[right]});
//                     while (left < right && nums[left] == nums[left + 1]) left++;
//                     while (left < right && nums[right] == nums[right - 1]) right--;

//                     left++;
//                     right--;
//                 }
//                 else if (sum > 0)
//                 {
//                     right--;
//                 }
//                 else
//                 {
//                     left++;
//                 }
//             }
//         }
//         return result;
//     }
// };