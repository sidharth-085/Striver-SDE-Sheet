#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// In this question, we find the width of a rectangle by looking the left and right
// smaller elements. The right smaller element is the boundary for the right and 
// left smaller element is the boundary for the left. The difference between both of 
// them is the width of particular height of rectangle. 

// Approach 1: Brute Force Solution
// Time Complexity: O(N^2)
// Space Complexity: O(1)

int largestRectangle(vector<int> &heights) {
    int n = heights.size();
    
    int maxArea = 0;
    
    // step 1: traverse the array and look for right smaller and left smaller 
    // individually by going left and right.

    for (int i=0; i<n; i++) {
        int currHeight = heights[i];
        // current element is the current height

        // step 2: start from one before of the current height and go until we get 
        // the smaller height than current height.

        int leftIndex = i - 1;
        while (leftIndex >= 0 && currHeight <= heights[leftIndex]) {
            leftIndex--;
        }

        // step 3: start from one ahead of the current height and go until we get
        // the smaller height than current height.

        int rightIndex = i + 1;
        while (rightIndex < n && currHeight <= heights[rightIndex]) {
            rightIndex++;
        }

        // step 4: calculate the current width and area

        int currWidth = rightIndex - leftIndex - 1;
        
        int currArea = currHeight * currWidth;

        // step 5: maximize the area

        maxArea = max(maxArea, currArea);
    }

    return maxArea;
}

// Approach 2: Optimal Solution (using Previous Smaller Element & Next Smaller Element)
// Time Complexity: O(N)
// Space Complexity: O(N)

int largestRectangle(vector<int> &heights) {
    int n = heights.size();

    stack<int> stk;
    // make stack for storing the left elements of current element in linearly
    // increasing order

    // previous smaller element indices
    vector<int> leftSmaller(n);

    for (int i=0; i<n; i++) {
        int currHeight = heights[i];

        // step 1: run the while loop till the stack becomes empty or top element of
        // stack is smaller than current element

        while (stk.empty() == false && heights[stk.top()] >= currHeight) {
            stk.pop();
        }

        // step 2: check is stack becomes empty or not, if it becomes empty means 
        // for current element there is no left smaller element so the left smaller
        // index will be -1.

        if (stk.empty()) {
            leftSmaller[i] = -1;
        }

        // step 3: if stack is not empty, and the top element of stack is smaller than
        // current element of heights array.

        else {
            leftSmaller[i] = stk.top();
        }

        // step 4: finally push the current element in stack for complete the traversal

        stk.push(i);
    }

    // step 5: remove all the elements from stack and make stack empty for using further
    // right smaller array calculation

    while (stk.empty() == false) {
        stk.pop();
    }

    // next smaller elements indices
    vector<int> rightSmaller(n);

    // step 6: traverse the heights array from backwards to get indices having right
    // smaller element location

    for (int i=n-1; i>=0; i--) {
        int currHeight = heights[i];

        // step 7: run the while loop till the stack becomes empty or top element of
        // stack is smaller than current element

        while (stk.empty() == false && heights[stk.top()] >= currHeight) {
            stk.pop();
        }

        // step 8: check is stack becomes empty or not, if it becomes empty means 
        // for current element there is no right smaller element so the right smaller
        // index will be n (right boundary)

        if (stk.empty()) {
            rightSmaller[i] = n;
        }

        // step 9: if stack is not empty, and the top element of stack is smaller than
        // current element of heights array.

        else {
            rightSmaller[i] = stk.top();
        }

        stk.push(i);
        // finally push the index to the stack for traversal
    } 

    int maxArea = -1;

    // step 10: now we get the leftSmaller array and rightSmaller array, hence we can
    // get the maximum area

    for (int i=0; i<n; i++) {
        int currHeight = heights[i];
        int currWidth = rightSmaller[i] - leftSmaller[i] - 1;
        // subtract both rightSmaller and lettSmaller indices and decrease 1 for width.

        int currArea = currHeight * currWidth;

        maxArea = max(maxArea, currArea);
    }

    return maxArea;
}

// Approach 3: Best optimal Solution using Single Traversal
// Time Complexity: O(N)
// Space Complexity: O(N)

// this solution is little complex than previous but effective

int largestRectangle(vector<int> &heights) {
    int n = heights.size();

    stack<int> stk;
    // in this method, we are using the stack to find left smaller and right smaller 
    // boundary for the elements present in the stack itself not heights array.

    int maxArea = -1;

    for (int i=0; i<=n; i++) {
        // step 1: run the while loop till stack becomes empty and if stack is not empty
        // run until top element of stack become smaller than current height element or
        // i becomes n + 1, we are running if i == n because there will be case when 
        // i becomes n but stack still contains some elements and we are using stack
        // for calculating the area by taking stack elements as heights

        while (stk.empty() == false && (i == n || heights[stk.top()] >= heights[i])) {
            int currHeight = heights[stk.top()];
            // take out the top element of stack which is bigger than the heights[i]
            // means for top element of stack, heights[i] is right smaller boundary

            stk.pop();
            // pop the element

            int currWidth = -1;

            // check whether stack becomes empty, if stack becomes empty, currWidth is 
            // ith index because there is not left boundary now only right boundary is
            // there which is heights[i].

            if (stk.empty()) {
                currWidth = i;
            }

            // if stack is not empty, means we have the left smaller element which is 
            // next top element after popping the stack. Hence, difference of both
            // left and right smaller element indices minus 1, will be the width

            else {
                int rightSmaller = i;
                int leftSmaller = stk.top();

                currWidth = rightSmaller - leftSmaller - 1;
            }

            // finally, find the area and maximize the area.

            int currArea = currHeight * currWidth;
            maxArea = max(maxArea, currArea);
        }

        // push the element in the stack for completing the traversal

        stk.push(i);
    }

    return maxArea;
}