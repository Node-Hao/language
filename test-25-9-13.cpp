#include<iostream>
#include<vector>
using namespace std;

int main()
{
    vector<int> arr;
    vector<vector<int>> mat;
    vector<int> arr = {1,32};
    vector<vector<int>> mat = {
        {1, 2, 3},
        {2, 3, 4}
    };
    vector<int> arr(10, 0);
    vector<vector<int>> mat(10, vector<int>(10, 0));
    cout << "Hello";
    return 0;
}