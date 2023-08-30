#include <vector>
using namespace std;

// Cuts Rods: Similar to Ways to make coin change problem && combinational sum 1 problem.

// Approach 1: Using Recursion (general)
// Time Complexity: O(2^N)
// Space Complexity: O(N)

void cutRodHelper(vector<int> &price, int size, int limit, int currProfit, int &maxProfit) {
	if (limit == 0) {
		maxProfit = max(currProfit, maxProfit);
		return;
	}
	
	if (size <= 0 || limit < 0) {
		return;
	}

	if (size <= limit) { // include
		cutRodHelper(price, size, limit - size, currProfit + price[size-1], maxProfit);
	}

	// exclude
	cutRodHelper(price, size-1, limit, currProfit, maxProfit);
}

int cutRod(vector<int> &price, int size) {
	int currProfit = 0;
	int limit = size;

	int maxProfit = 0;

	cutRodHelper(price, size, limit, currProfit, maxProfit);
	return maxProfit;
}

// Approach 2: Using Recursion but for memoization

// Time Complexity: O(2^N)
// Space Complexity: O(N)

int cutRodHelper(vector<int> &price, int size, int limit, int currProfit) {
	if (limit == 0) {
		return currProfit;
	}
	
	if (size <= 0 || limit < 0) {
		return 0;
	}

	int include = 0;

	if (size <= limit) { // include
		include = cutRodHelper(price, size, limit - size, currProfit + price[size-1]);
	}

	// exclude
	int exclude = cutRodHelper(price, size-1, limit, currProfit);

	return max(include, exclude);
}

int cutRod(vector<int> &price, int size) {
	int currProfit = 0;
	int limit = size;

	return cutRodHelper(price, size, limit, currProfit);
}

// Approach 3: Memoization Approach

// Time Complexity: O(N*N)
// Space Complexity: O(N*N)

int cutRodHelper(vector<int> &price, int size, int limit, vector<vector<int>> &ans) {
	if (limit <= 0 || size <= 0) {
		return 0;
	}

	if (ans[size][limit] != -1) {
		return ans[size][limit];
	}

	int include = 0;

	if (size <= limit) { // include
		include = price[size-1] + cutRodHelper(price, size, limit - size, ans);
	}

	// exclude
	int exclude = cutRodHelper(price, size-1, limit, ans);

	ans[size][limit] = max(include, exclude);
	return ans[size][limit];
}

int cutRod(vector<int> &price, int size) {
	int limit = size;

	vector<vector<int>> ans(size + 1, vector<int>(size + 1, -1));
	return cutRodHelper(price, size, limit, ans);
}

// Approach 4: Bottom Up DP approach

// Time Complexity: O(N*N)
// Space Complexity: O(N*N)

int cutRod(vector<int> &price, int size) {
	int limit = size;

	vector<vector<int>> ans(size + 1, vector<int>(size + 1));
	
	// base case: size = 0 || limit = 0 mark 0

	for (int i=0; i<=size; i++) {
		ans[0][i] = 0;
		ans[i][0] = 0;
	} 

	// do the recurrence part

	for (int i = 1; i <= size; i++) { // size
		for (int j = 1; j<= limit; j++) { // limit
			int include = 0;
			if (i <= j) {
				include = price[i-1] + ans[i][j - i];
			}
			int exclude = ans[i-1][j];

			ans[i][j] = max(include, exclude);
		}
	}

	return ans[size][limit];
}

// Approach 5: Bottom Up optimized Dp 

// Time Complexity: O(N*N)
// Space Complexity: O(N)

int cutRod(vector<int> &price, int n) {
    int cost[n + 1];
    cost[0] = 0; 
    int i, j;

    for (i = 1; i <= n; i++) {
        int maxCost = INT_MIN;

        // Build the table in bottom up manner.
        for (j = 0; j < i; j++) {
            maxCost = max(maxCost, price[j] + cost[i - j - 1]);
        }

        // Contains maximum cost obtained from the rod of length 'i'.
        cost[i] = maxCost;
    }

    // Last entry conatins maximum cost obtained from the rod of length 'n'.
    return cost[n];
}