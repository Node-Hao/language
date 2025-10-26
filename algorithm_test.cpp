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

// 翻转字符串II
// #include <iostream>
// #include <vector>
// #include <list>
// #include <deque>
// #include <stdexcept> // 用于异常处理
// #include <sstream>
// #include <string>

// template <typename T, typename Cotainer = std::deque<T>>
// class MyStack
// {
//     private:
//         Cotainer data;// 使用底层容器存储栈的元素

//     public:
//         // 压入元素到栈顶
//         void push(const T& value)
//         {
//             data.push_back(value);
//         }
//         // 弹出栈顶元素
//         void pop()
//         {
//             if (!empty())
//             {
//                 data.pop_back();
//             }
//             else
//             {
//                 throw std::runtime_error("Stack is empty.");
//             }
//         }
//         // 返回栈顶元素的引用
//         T& top()
//         {
//             if (!empty())
//             {
//                 return data.back();
//             }
//             else
//             {
//                 throw std::runtime_error("Stack is empty.");
//             }
//         }

//         // 检查栈是否为空
//         bool empty() const
//         {
//             return data.empty();
//         }

//         // 返回栈的大小
//         size_t size() const
//         {
//             return data.size();
//         }
// };

// int main() {
//         // 使用 std::deque 作为底层容器的示例
//     MyStack<int, std::deque<int>> stack;

//     int N;
//     std::cin >> N;
//     getchar();

//     std::string line;
//     for (int i = 0; i < N; i++) {
//         std::getline(std::cin, line);
//         std::istringstream iss(line);
//         std::string command;
//         iss >> command;
//         int element;
//         if (command == "push") {
//             iss >> element;
//             stack.push(element);
//         }
//         if (command == "pop") {
//             try {
//                 stack.pop();
//             } catch(const std::runtime_error& e) {
//                 // 不做任何处理
//                 continue;
//             }
//         }
//         if (command == "top") {
//             try {
//                 std::cout << stack.top() << std::endl;
//             } catch(const std::runtime_error& e) {
//                 std::cout << "null" << std::endl;
//             }   
//         }
//         if (command == "size") {
//             std::cout << stack.size() << std::endl;
//         }
//         if (command == "empty") {
//             std::cout << (stack.empty() ? "true" : "false") << std::endl;
//         }
//     }
//     return 0;
// }
// class Solution {
// public:
//     string reverseStr(string s, int k) 
//     {
//         int n = s.size();

//         for (int i = 0; i < n; i += 2 * k)//每次划分出一个区间
//         {
//             // 若剩余字符小于 k 全部反转
//             // 否则反转前 k 个
//             int end = min(i + k - 1, n - 1);
//             reverse(s, i, end);
//         }
//         return s;
//     }
//     void reverse (string &s, int left, int right)
//     {
//         while (left < right)
//         {
//             char tmp = s[left];
//             s[left] = s[right];
//             s[right] = tmp;
//             left++;
//             right--;
//         }
//     }
// };

// 替换字符串
#include <iostream>
#include <string>
#include <cctype>// 包含 isdigit 函数的头文件


// 字符串 s 包含小写字母和数字字符，字母字符不变，数字替换为 number
// 核心思路为新建字符串拼接

std::string replace (std::string s, std::string &new_s)
{
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        char c = s[i];
        if (!isdigit(c))
        {
            new_s.insert(new_s.end(), c);
        }
        else
        {
            new_s.append("number");
        }
    }
    return new_s;
}


int main()
{
    std::string s;
    std::cin >> s;
    std::string new_s;
    std::cout << replace(s, new_s);
}

// 反转字符串中的单词
class Solution {
public:
    string reverseWords(string s) {
        string buffer;
        string result;
        vector<string> arr_s;

        for (char c : s)
        {
            if (c != ' ')
            {
                buffer += c;
            }
            else
            {
                if (!buffer.empty())
                {
                    arr_s.push_back(buffer);
                    buffer.clear();
                }
            }
        }
        if (!buffer.empty())
        {
            arr_s.push_back(buffer);
        }
        if (arr_s.empty())
        {
            return "";
        }
        // 此时 arr_s 中包含所有单词
        int n = arr_s.size();
        int left = 0;
        int right = n - 1;
        
        while (left < right)
        {
            swap(arr_s[left], arr_s[right]);
            ++left;
            --right;
        }
        // 此时arr_s 中单词顺序已经正确，只需往字符串中添加即可
        for (int i = 0; i < n ; i++)
        {
            result.append(arr_s[i]);
            if (i != n - 1)
            {
                result += ' ';
            }
        }
        return result;
    }
};
// 至少一个空格将字符串中的单词分隔开
// 返回字符串用单个空格分隔单词，不需要多于空格
// 不如将所有的单词都创建为字符串，之后直接拼接即可
// 创建一个字符串数组，下标的先后顺序就是字符串的顺序

// 右旋转字符串
#include<iostream>
#include<string>
#include<stack>


int main()
{
    std::string s;
    int k;
    std::cin >> k >> s;
    std::string result;
    size_t n = s.size();
    
    if (!k || !n)
    {
        std::cout << s;
        return 0;
    }

    std::string tail = s.substr(n-k, n);
    std::string head = s.substr(0, n-k);

    result = tail + head;
    std::cout << result;
    
    return 0;
}

// 匹配字符串中的字符的第一个下标
class Solution {
public:
    int strStr(string haystack, string needle) {
        int haylen = haystack.size();
        int needlen = needle.size();

        if (haylen < needlen) return -1;
        // 第一层 for 循环确保遍历到每一个haystack, 顺便作为索引的返回值
        // 第二次 for 循环确保遍历到每一个needle
        for (int i = 0; i < haylen; i++)
        {
            int hayIndex = i;
            int needIndex = 0;

            while (needIndex < needlen && haystack[hayIndex] == needle[needIndex])
            {
                ++hayIndex;
                ++needIndex;
            }
            if (needIndex == needlen) return i;
        }
        return -1;
    }
};

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int len = s.size();
        // 仅枚举可能的子串长度（约数且 <= len/2）
        for (int i = 1; i <= len / 2; ++i) {
            if (len % i != 0) {
                continue;  // 不是约数，跳过
            }
            // 检查所有子串区间是否与第一个子串相同
            bool isRepeated = true;
            for (int j = i; j < len; j++)
            {
                if (s[j] != s[j - i])
                {
                    isRepeated = false;
                    break;
                }
            }
            if (isRepeated) {
                return true;
            }
        }
        return false;
    }
};
// 子串长度为 i , 每重复一次，新的子串就和前一个子串一样
// 因此原字符串中的第 j 个字符必然与新字符串 j - i 个字符相同

class MyQueue {
private:
    // 声明为类成员变量所有成员均可房屋
    std::stack<int> s1;// 输入栈：接收新元素
    std::stack<int> s2;// 输出栈：提供队头元素

    // 辅助函数 s2 为空时，将 s1 中元素全部转移至 s2
    void transfer()
    {
        if (s2.empty())
        {
            while (!s1.empty())
            {
                int val = s1.top();
                s1.pop();
                s2.push(val);
            }
        }
    }

public:
    MyQueue() { }
    
    void push(int x) {
        s1.push(x);
    }
    
    int pop() {
        transfer();
        int val = s2.top();
        s2.pop();
        return val;
    }
    
    int peek() {
        transfer();
        return s2.top();
    }
    
    bool empty() {
        return s1.empty() && s2.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
#include<list>
#include<queue>
 class MyStack {
private:
    std::queue<int, std::list<int>> q1;
    std::queue<int, std::list<int>> q2;

    void transfer()
    {
        int size = q1.size() - 1;
        while (size--)
        {
            int val = q1.front();;
            q1.pop();
            q2.push(val);
        }
    }
    void swapQueue()
    {
        std::queue<int, std::list<int>> q = q1;
        q1 = q2;
        q2 = q;
    }

public:
    MyStack() {
        
    }
    
    void push(int x) {
        q1.push(x);
    }
    
    int pop() {
        transfer();
        int val = q1.front();
        q1.pop();
        swapQueue();
        return val;
        
    }
    
    int top() {
        transfer();
        int val = q1.front();
        q1.pop();
        q2.push(val);
        swapQueue();
        return val;
    }
    
    bool empty() {
        return q1.empty();
    }
};
// 目前不知道哪个是主队列，主队列用来存储，其实只要该一下名字即可，永远让q1当主队列

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

 // 括号的匹配程度 原版代码
 class Solution {
public:
    bool isValid(string s) {
        size_t n = s.size();
        stack<int> sk;
        for (int i = 0; i < n; i++)
        {
            char c = s[i];
            if (c == '(' || c == '[' || c == '{')
            {
                sk.push(c);
            }
            else
            {
                if (sk.empty()) return false;
                char topChar = sk.top();
                sk.pop();
                
                switch (c)
                {
                    case ')':
                        if (topChar != '(') return false;
                        break;
                    case ']':
                        if (topChar != '[') return false;
                        break;
                    case '}':
                        if (topChar != '{') return false;
                        break;
                }
            }
        }
        if (!sk.empty()) return false;
        return true;
    }
};
#include<unordered_map>
// 优化版本
class Solution {
public:
    bool isValid(string s) {
        size_t n = s.size();
        stack<char> sk;
        // 建立由括号到左括号的映射表
        unordered_map<char, char> bracketMap = {{')', '('}, {']', '['}, {'}', '{'}};
        // 奇数剪枝
        if (n % 2 != 0) return false;

        for (char c : s)
        {
            if (c == '(' || c == '[' || c == '{')
            {
                sk.push(c);
            }
            else
            {
                if (sk.empty() || bracketMap[c] != sk.top())
                {
                    return false;
                }
                sk.pop();
            }
        }

        return sk.empty();
    }
};
// 有可能队列为空的时候直接给右括号
#include<algorithm>
#include<string>
// 删除相邻重复元素
// 第一版原始代码
class Solution {
public:
    string removeDuplicates(string s) {
        stack<char> sk;
        string result;
        
        for (char c : s)
        {
            if (sk.empty())
            {
                sk.push(c);
            }
            else
            {
                char topChar = sk.top();
                if (c == topChar)
                {
                    sk.pop();
                }
                else
                {
                    sk.push(c);
                }
            }
        }

        while(!sk.empty())
        {
            char topChar = sk.top();
            sk.pop();
            result += topChar;
        }
       reverse(result.begin(), result.end());

        return result;
    }
};

// 改进算法
class Solution {
public:
    string removeDuplicates(string s) {
        string res;
        for (char c : s)
        {
            // 若栈非空且栈顶与当前元素一致，直接弹出元素
            if(!res.empty() && res.back() == c)
            {
                res.pop_back();
            }
            else
            {
                res.push_back(c);
            }
        }
        return res;
    }
};
#include<set>
#include<unordered_set>
// 逆波兰表达式求值
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> sk;
        unordered_set<string> ops = {"+", "-", "*", "/"};
        
        for (string s : tokens)
        {
            if (ops.count(s))
            {
                int right = sk.top(); sk.pop();
                int left = sk.top(); sk.pop();
                int result;
                switch(s[0])
                {
                    case '+': 
                        result = left + right;
                        break;
                    case '-': 
                        result = left - right;
                        break;
                    case '/': 
                        result = left / right;
                        break;
                    case '*': 
                        result = left * right;
                        break;
                }
                sk.push(result);
            }else{
                sk.push(stoi(s));
            }
        }
        return sk.top();
    }
};

// 滑动窗口求最大值

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        deque<pair<int,int>> sk;
        int n = nums.size();

        for (int i = 0; i < n; i++)
        {
            // 计算当前窗口的左边界，只有当 i >= 2 时才有意义
            int left = i - k + 1;
            while(!sk.empty() && sk.front().second < left)
            {
                // 移除队列中所有在窗户外的元素
                sk.pop_front();
            }
            
            // 队尾移除所有小于当前元素的元素，维持单调栈的特性
            while (!sk.empty() && sk.back().first <= nums[i])
            {
                sk.pop_back();
            }
            // 将当前元素加入到队尾
            sk.push_back({nums[i], i});

            // 当i >= k - 1 时窗口形成, 队头即为窗口最大值
            if (i >= k - 1)
            {
                result.push_back(sk.front().first);
            }
        }
        return result;
    }
};
// 栈中永远只存最大的元素 ， 开始先做好准备工作，把第一个窗口的内容全部判断完毕
// 此时栈中内容为 3，窗口移动之后，将新出现的元素与栈中元素做对比
// 现在关键的问题在于栈中的最大值会随着窗口出去
// 我的想法是用 hash 表将元素与它的索引对应起来，用索引来控制窗口的移动
// 但是如果多个元素连续一样，还是没法判断先后顺序
// 现在最大的问题在于何时淘汰栈的最大值(已解决)

// 前 k 个最大元素
// 法一：map 转 vector 排序法
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int n = nums.size();
        vector<int> result;
        
        for (int i = 0; i < n; i++)
        {
            freq[nums[i]]++;
        }

        vector<pair<int, int>> freq_vec(freq.begin(), freq.end());
        sort(freq_vec.begin(), freq_vec.end(),
            [](const pair<int,int> &a, const pair<int, int> &b){
                return a.second > b.second;//降序排列
            });
        
        for (int i = 0; i < k; ++i)
        {
            result.push_back(freq_vec[i].first);
        }
        return result;
    }
};

// 法二： 转为小根堆
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int n = nums.size();
        vector<int> result;
        
        for (int i = 0; i < n; i++)
        {
            freq[nums[i]]++;
        }

        priority_queue<pair<int,int>, vector<pair<int,int>>,greater<pair<int,int>>> min_heap;

        for (const auto& p : freq)
        {
            min_heap.emplace(p.second, p.first);
            if (min_heap.size() > k)
            {
                min_heap.pop();// 超过k个元素移除频率最小的元素
            }
        }
        
        while (!min_heap.empty())
        {
            result.push_back(min_heap.top().second);
            min_heap.pop();
        }

        reverse(result.begin(), result.end());

        return result;
    }
};

// 二叉树前序遍历递归法
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        Traversal(root, result);
        return result;
    }
    void Traversal(TreeNode* cur, vector<int> &vec){//1.确定参数和返回值
        if (cur == nullptr) return;
        vec.push_back(cur->val);
        Traversal(cur->left, vec);
        Traversal(cur->right, vec);
    }
};

class Solution {
private:
    vector<int> result;
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if (root == nullptr) return result;
        result.push_back(root->val);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
        return result;
    }
};
// 前序遍历迭代法
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> vec;
        if (root == nullptr) return vec;
        stack<TreeNode*> sk;
        TreeNode* cur = root;
        sk.push(cur);
        
        while (!sk.empty())
        {
            cur = sk.top();
            vec.push_back(cur->val);
            sk.pop();

            if (cur->right) sk.push(cur->right);

            if (cur->left) sk.push(cur->left);
        }
        return vec;
    }
};

// 中序遍历迭代法
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> sk;
        TreeNode* cur = root;
        vector<int> result;
        
        while (cur != nullptr || !sk.empty())
        {
            if (cur != nullptr)
            {
                sk.push(cur);
                cur = cur->left;//左
            }else{
                cur = sk.top();
                sk.pop();
                result.push_back(cur->val);//中
                cur = cur->right;//右
            }
        }
        return result;
    }
};

// 中序遍历迭代法 空指针标记法
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> sk;
        vector<int> result;
        sk.push(root);
        if (root == nullptr) return result;

        while (!sk.empty())
        {
            TreeNode* cur = sk.top();
            if (cur != nullptr)
            {
                sk.pop();
                if (cur->right) sk.push(cur->right);
                sk.push(cur);
                sk.push(nullptr);//标记中间节点
                if (cur->left) sk.push(cur->left);
            }else{
                sk.pop();
                cur = sk.top();
                sk.pop();
                result.push_back(cur->val);
            }
        }
        return result;
    }
};
// 空指针标记法，主要用于标记访问过但没有操作的元素，没有节点都可以看做是中间节点

// 中序遍历迭代法 bool 标记法
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<pair<TreeNode*, bool>> sk;
        vector<int> result;
        if (root != nullptr) sk.push(make_pair(root, false));
        
        while (!sk.empty())
        {
            TreeNode* cur = sk.top().first;
            bool visited = sk.top().second;
            sk.pop();

            if (visited)//表示当前节点和他的左右孩子节点都已被访问过，可以收割了
            {
                result.push_back(cur->val);
                continue;
            }

            if (cur->right)
            {
                sk.push(make_pair(cur->right, false));
            }

            sk.push(make_pair(cur, true));

            if (cur->left)
            {
                sk.push(make_pair(cur->left, false));
            }
        }
        return result;
    }
};

// 二叉树的层序遍历
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        vector<vector<int>> result;
        if (root != nullptr)  q.push(root);

        while (!q.empty())
        {
            int size = q.size();
            vector<int> tmp;
            for (int i = 0; i < size; i++)
            {
                TreeNode* cur = q.front();
                tmp.push_back(cur->val);
                q.pop();
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
            result.push_back(tmp);
        }
        return result;
    }
};
// 二叉树的层序遍历二
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> result;
        queue<TreeNode*> q;
        if (root != nullptr) q.push(root);

        while (!q.empty())
        {
            size_t size = q.size();
            vector<int> tmp;
            for (size_t i = 0; i < size; i++)
            {
                TreeNode* cur = q.front();
                q.pop();
                tmp.push_back(cur->val);
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
            result.push_back(tmp);
        }
        // int left = 0;
        // int right = result.size() - 1;
        // while (left < right)
        // {
        //     vector<int> tmp = result[left];
        //     result[left] = result[right];
        //     result[right] = tmp;
        //     ++left;
        //     --right;
        // }
        reverse(result.begin(), result.end());
        return result;
    }
};