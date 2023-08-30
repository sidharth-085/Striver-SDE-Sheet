#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

// Time Complexity : O(n^3) due to 3 nested loops
void setZeros(vector<vector<int>> &matrix) { // Brute Force Approach
	int n = matrix.size();
	int m = matrix[0].size();
	vector<vector<bool>> visited(n, vector<bool>(m, false));

	for (int i=0; i<n; i++) {
		for (int j=0; j<m; j++) {
			if (matrix[i][j] == 0 && !visited[i][j]) {
				// first do the row 
				for (int k=0; k<m; k++) {
					if (matrix[i][k] == 0) {
						continue;
					}
					matrix[i][k] = 0;
					visited[i][k] = true;
				}
				// secondly do the col
				for (int k=0; k<n; k++) {
					if (matrix[k][j] == 0) {
						continue;
					}
					matrix[k][j] = 0;
					visited[k][j] = true;
				}
			}
		}
	}
}

// Time Complexity : O(n*m)
void setZeros(vector<vector<int>> &matrix) { // Optimal Approach
    int n = matrix.size();
    int m = matrix[0].size();

    unordered_set<int> zeroRows;
    unordered_set<int> zeroCols;

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (matrix[i][j] == 0) {
                zeroRows.insert(i);
                zeroCols.insert(j);
            }
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (zeroRows.find(i) != zeroRows.end() || zeroCols.find(i) != zeroCols.end()) {
                matrix[i][j] = 0;
            }
        }
    }
}