#include <iostream>
#include <vector>
using namespace std;

// We are assuming the first node is 1 and their childs will be 2*i & 2*i + 1 for parent i.
// In heaps, we are starting with 0, so childs are 2*i + 1 & 2*i + 2 for parent i.

class SegmentTree {
    private:

    vector<int> tree;   
    int n;

    // Helper function to build the segment tree
    void buildTree(const vector<int> &nums, int node, int start, int end) {
        if (start == end) {
            tree[node] = nums[start];
        } 
        else {
            int mid = start + (end - start) / 2;
            buildTree(nums, 2 * node, start, mid); 
            buildTree(nums, 2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] + tree[2 * node + 1]; 
            // Sum operation, can be changed based on the requirement
        }
    }

    // Helper function to update a value in the segment tree
    void updateTree(int node, int start, int end, int index, int value) {
        if (start == end) {
            tree[node] = value;
        } 
        else {
            int mid = start + (end - start) / 2;
            if (index <= mid) {
                updateTree(2 * node, start, mid, index, value);
            } else {
                updateTree(2 * node + 1, mid + 1, end, index, value);
            }
            tree[node] = tree[2 * node] + tree[2 * node + 1]; 
            // Sum operation, can be changed based on the requirement
        }
    }

    // Helper function to perform a range sum query
    int queryTree(int node, int start, int end, int left, int right) {
        if (left > end || right < start) {
            return 0; // Neutral value for sum operation
        } 
        else if (left <= start && right >= end) {
            return tree[node];
        } 
        else {
            int mid = start + (end - start) / 2;
            int leftSum = queryTree(2 * node, start, mid, left, right);
            int rightSum = queryTree(2 * node + 1, mid + 1, end, left, right);
            return leftSum + rightSum; 
            // Sum operation, can be changed based on the requirement
        }
    }

    public:
    // Constructor to build the segment tree from a given array
    SegmentTree(const vector<int>& nums) {
        n = nums.size();
        tree.resize(4 * n); // Size of the segment tree will be 4 times the size of the input array in this case
        buildTree(nums, 1, 0, n - 1);
    }

    // Function to update a value in the segment tree
    void update(int index, int value) {
        updateTree(1, 0, n - 1, index, value);
    }

    // Function to perform a range sum query
    int query(int left, int right) {
        return queryTree(1, 0, n - 1, left, right);
    }
};

int main() {
    vector<int> nums = {1, 3, 5, 7, 9, 11};
    SegmentTree st(nums);

    // Example usage of segment tree
    int sum = st.query(1, 4); // Query the sum from index 1 to index 4 (inclusive)
    cout << "Sum from index 1 to index 4: " << sum << endl;

    st.update(2, 6); // Update the value at index 2 to 6
    sum = st.query(1, 4); // Query the updated sum from index 1 to index 4 (inclusive)
    cout << "Updated sum from index 1 to index 4: " << sum << endl;

    return 0;
}