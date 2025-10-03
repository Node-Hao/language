#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

class Solution {
public:
    bool isHappy(int n) {
        int cur = n;
        unordered_set<int> set;
        while (n != 1)
        {
            int tmp = 0;
            while (cur)
            {
                tmp += (cur % 10) * (cur % 10);
                cur /= 10;
            }
            n = tmp;
            cur = n;
            set.insert(n);
            if (set.find(n) != set.end()) return false;
        }
        return true;
    }
};

int main()
{
    Solution s;
    bool istrue = s.isHappy(19);

    return 0;
}