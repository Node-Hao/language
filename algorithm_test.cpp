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








