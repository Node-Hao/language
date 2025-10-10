#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

class Solution {
public:
    string reverseStr(string s, int k) 
    {
        int n = s.size();
        int count = 0;
        int two = n / (2 * k);

        for (int i = 0; i < n; i++)
        {
            count++;
            if (count == 2*k)
            {
                // 翻转前 k 个而非后 k 个字符
                reverse(s, i - 1 - k, i - k);
                count = 0;
                --two;//二倍区间减一
                continue;
            }
            // 之所以出现错误是因为2倍数没有算完
            if (two == 0 && n - i - 1 < k)
            {
                reverse(s, i, n - 1);
                return s;
            }

            if (two == 0 && n - i - 1 < 2*k && n - i - 1 >= k)
            {
                reverse(s, i, i + k - 1);
                return s;
            }
        }
        return s;
    }
    void reverse (string &s, int left, int right)
    {
        while (left < right)
        {
            char tmp = s[left];
            s[left] = s[right];
            s[right] = tmp;
            left++;
            right--;
        }
    }
};

int main()
{
    Solution s;
    string result = s.reverseStr("abcdefg", 2);
    cout << result << endl;
    return 0;
}