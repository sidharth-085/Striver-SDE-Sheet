#include <vector>
using namespace std;

/* Pascals Triangle
            1 
           1 1 
          1 2 1 
         1 3 3 1 
        1 4 6 4 1     
*/

vector<vector<long long int>> printPascal(int n) {
  vector<vector<long long int>> ans;

  for (int i=0; i<n; i++) {
    vector<long long int> temp;
    for (int j=0; j<i+1; j++) {
      temp.push_back(1);
    }
    ans.push_back(temp);
  }

  for (int i=2; i<n; i++) {
    for (int j=0; j<i+1; j++) {
      if (j == 0 || j == i) {
        continue;
      }
      ans[i][j] = ans[i-1][j-1] + ans[i-1][j];
    } 
  }
  return ans;
}