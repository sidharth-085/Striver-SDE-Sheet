#include <iostream>
using namespace std;

// Knapsack problem helper function
int knapsackHelper1(int *weights, int *values, int n, int maxWeight, int knapsackValue, int knapsackWeight, int startIndex) {
    // Base case: if all items have been considered or knapsack weight exceeds the maximum weight
    if (startIndex == n || knapsackWeight >= maxWeight) {
        return knapsackValue; // Return the current knapsack value
    }

    // Option 1: Include the current item in the knapsack if its weight does not exceed the maximum weight
    int option1 = 0;
    if (knapsackWeight + weights[startIndex] <= maxWeight) {
        option1 = knapsackHelper1(weights, values, n, maxWeight, knapsackValue + values[startIndex], knapsackWeight + weights[startIndex], startIndex + 1);
    }

    // Option 2: Exclude the current item from the knapsack
    int option2 = knapsackHelper1(weights, values, n, maxWeight, knapsackValue, knapsackWeight, startIndex + 1);

    // Return the maximum value between option 1 and option 2
    return max(option1, option2);
}

int knapsackHelper2(int *weights, int *values, int n, int maxWeight, int knapsackValue, int knapsackWeight, int startIndex) {
    // Base case: if all items have been considered
    if (startIndex == n) {
        // Check if the knapsack weight does not exceed the maximum weight
        if (knapsackWeight <= maxWeight) {
            return knapsackValue; // Return the current knapsack value
        }
        return 0; // Return 0 if the knapsack weight exceeds the maximum weight
    }

    // Option 1: Include the current item in the knapsack if its weight does not exceed the maximum weight
    int option1 = knapsackHelper2(weights, values, n, maxWeight, knapsackValue + values[startIndex], knapsackWeight + weights[startIndex], startIndex + 1);

    // Option 2: Exclude the current item from the knapsack
    int option2 = knapsackHelper2(weights, values, n, maxWeight, knapsackValue, knapsackWeight, startIndex + 1);

    // Return the maximum value between option 1 and option 2
    return max(option1, option2);
}

void knapsackHelper3(int *weights, int *values, int n, int maxWeight, int startIndex, int knapsackWeight, int knapsackValue, int &maxValue) {
    if (startIndex == n) {
        // Check if the knapsack weight does not exceed the maximum weight
        if (knapsackWeight <= maxWeight) {
            maxValue = max(maxValue, knapsackValue);
        }
        return; // Return if the knapsack weight exceeds the maximum weight
    }

    knapsackHelper3(weights, values, n, maxWeight, startIndex+1, knapsackWeight + weights[startIndex], knapsackValue + values[startIndex], maxValue);
    // include the weight & call to get max value for this case.
    knapsackHelper3(weights, values, n, maxWeight, startIndex+1, knapsackWeight, knapsackValue, maxValue);
    // dont inclue the weight & call to get max value for this case.

}

// Knapsack problem main function

int knapsack3(int *weights, int *values, int n, int maxWeight) { // BRUTE FORCE 3: Backtracking
    int maxValue = 0;
    knapsackHelper3(weights, values, n, maxWeight, 0, 0, 0, maxValue);
    return maxValue;
}

int knapsack2(int *weights, int *values, int n, int maxWeight) { // BRUTE FORCE 2
    // Call the helper function to solve the knapsack problem
    return knapsackHelper2(weights, values, n, maxWeight, 0, 0, 0);
}

int knapsack1(int *weights, int *values, int n, int maxWeight) { // BRUTE FORCE 1
    // Call the helper function to solve the knapsack problem
    return knapsackHelper1(weights, values, n, maxWeight, 0, 0, 0);
}

// Knapsack Problem solution without helper functions

int knapsack(int *weights, int *values, int n, int maxWeight) {
    if (n == 0 || maxWeight == 0) {
        return 0;
    }

    if (weights[0] > maxWeight) {
        return knapsack(weights+1, values+1, n-1, maxWeight);
    }

    int option1 = knapsack(weights+1, values+1, n-1, maxWeight - weights[0]) + values[0];
    int option2 = knapsack(weights+1, values+1, n-1, maxWeight);

    return max(option1, option2);
}

int knapsackUsingMemoizationHelper(int *weights, int *values, int n, int maxWeight, vector<vector<int>> &ans) {
    // Base case: If there are no items left (n == 0) or maximum weight is 0, return 0.
    if (n == 0 || maxWeight == 0) {
        return 0;
    }

    // If the value for the current state is already calculated, return it from the memoization table.
    if (ans[maxWeight][n] != -1) {
        return ans[maxWeight][n];
    }

    // Check if the weight of the first item exceeds the maximum weight.
    // In that case, exclude the first item and recursively call the function on the remaining items.
    // if (weights[0] > maxWeight) {
    //     return knapsackUsingMemoizationHelper(weights + 1, values + 1, n - 1, maxWeight, ans);
    // }

    // int option1 = values[0] + knapsackUsingMemoizationHelper(weights + 1, values + 1, n - 1, maxWeight - weights[0], ans);
    // int option2 = knapsackUsingMemoizationHelper(weights + 1, values + 1, n - 1, maxWeight, ans);

    // alternatively, we can exclude last element and do calculations on remaining part.
    if (weights[n-1] > maxWeight) {
        return knapsackUsingMemoizationHelper(weights, values, n-1, maxWeight, ans);
    }
    // Option 1: Include the first item and recursively call the function on the remaining items with reduced weight.
    int option1 = values[n-1] + knapsackUsingMemoizationHelper(weights, values, n-1, maxWeight - weights[n-1], ans);

    // Option 2: Exclude the first item and recursively call the function on the remaining items.
    int option2 = knapsackUsingMemoizationHelper(weights, values, n-1, maxWeight, ans);

    // Store the maximum value between option 1 and option 2 for the current state in the memoization table.
    ans[maxWeight][n] = max(option1, option2);

    // Return the maximum value between option 1 and option 2.
    return max(option1, option2);
}

int knapsackUsingMemoization(int *weights, int *values, int n, int maxWeight) {
    // Create a memoization table with dimensions (maxWeight+1) x (n+1) and initialize with -1.
    vector<vector<int>> ans(maxWeight + 1, vector<int>(n + 1, -1));
    return knapsackUsingMemoizationHelper(weights, values, n, maxWeight, ans);
}

int knapsackUsingDP(int *weights, int *values, int n, int maxWeight) {
    vector<vector<int>> ans(maxWeight + 1, vector<int>(n + 1, 0));
    
    for (int i=1; i<maxWeight+1; i++) {
        for (int j=1; j<n+1; j++) {
            if (weights[j-1] > i) {
                ans[i][j] = ans[i][j-1];
            }
            else {
                int option1 = values[j-1] + ans[i-weights[j-1]][j-1];
                int option2 = ans[i][j-1];
                ans[i][j] = max(option1, option2);
            }
        }
    }
    return ans[maxWeight][n];
}