#include <iostream>
#include <algorithm>
using namespace std;

// We have given queries having two integers Xi & Ai, we need to calculate the maximum 
// XOR of Xi with a number less than equal to Ai which is present in arr vector

// Approach 1: Brute Force Method
// Time Complexity: O(N*M)
// Space Complexity: O(1)

// N is size of arr && M is number of queries

vector<int> maxXorQueries(vector<int> &arr, vector<vector<int>> &queries) {
	int n = arr.size(); // num of elements in arr
	int m = queries.size(); // num of queries

	vector<int> ans(m, -1); // make the ans vector of size of queries and initially -1.

	for (int i=0; i<m; i++) { // traverse the complete queries
		int x = queries[i][0];
		int a = queries[i][1];

		int XOR = -1; 
		// take initially XOR as -1 because it is least value if no element found to 
		// take XOR with.

		for (int j=0; j < n; j++) {
			if (arr[j] <= a) { // if current element in arr is less than a, take Xor
				XOR = max(XOR, x ^ arr[j]);
			}
		}

		ans[i] = XOR; // finally store it in ans array
	}

	return ans;
}

// Approach 2: Using Trie & Bit Manupulation

// Step 1: Sort the queries on the basis of Ai && arr normally.
// Step 2: push only those elements in trie which is smaller than Ai
// Step 3: Check if at index is there any element which is less than Ai, if not add -1 to 
// position i
// Step 4: finally, take the maximum xor for each xi && return the answer

// Time Complexity: O(N*LogN + M*LogM) {sorting O(N*LogN), remaining all in O(N)}
// Space Complexity: O(N + M)

class TrieNode { // class for trie node
    TrieNode* children[2];

    public: 

    bool containsKey(int bit) {
        return children[bit] != NULL;
    }

    TrieNode* get(int bit) {
        return children[bit];
    } 

    void put(int bit) {
        children[bit] = new TrieNode();
    }
};

class Trie {
    TrieNode *root;

    public:

    Trie() {
        root = new TrieNode();
    }

    void insert(int num) { // insertion of every bit from left to right
        TrieNode *temp = root;
        for (int i=31; i>=0; i--) {
            int bit = (num >> i) & 1; // right shift the num to i bit with and 1 gives that bit
            if (temp->containsKey(bit) == false) { // if bit is not present make a new node there
                temp->put(bit);
            }
            temp = temp->get(bit); // update the temp with current bit
        }
    }

    int max_xor(int num) {
        TrieNode *temp = root;
        int ans = 0;

        for (int i=31; i>=0; i--) {
            int bit = (num >> i) & 1; // get the bit again
            if (temp->containsKey(!bit) == true) { 
				// check for opposite bit, because for XOR operation we get 1 only if 
				// there is 1 zero present, then if we have 0 we need 1 & vice versa, so 
				// find the oposite bit 
                
				ans = ans | (1 << i); // if opposite bit is there, update the ith bit of ans with 1
                temp = temp->get(!bit); // and update temp to opposite bit
            }
            else {
                temp = temp->get(bit); // if it does not have opposite bit, update temp with current bit. 
            }
        }

        return ans; // finally return the answer
    }

};

vector<int> maxXorQueries(vector<int> &arr, vector<vector<int>> &queries) {
	// Step 1: sort array and queries

	sort(arr.begin(), arr.end());

	int size = queries.size();

	vector<pair<int, pair<int, int>>> q(size);

	for (int i=0; i<size; i++) {
		q[i].first = queries[i][1];
		q[i].second.first = queries[i][0];
		q[i].second.second = i;
	}

	sort(q.begin(), q.end());

	// Step 2: Make trie and start with queries

	Trie trie;

	vector<int> ans(size, 0);

	int index = 0; // index for current track of arr

	for (int j = 0; j < size; j++) {
		pair<int, pair<int, int>> query = q[j]; // take ith query
		int ai = query.first;
		int xi = query.second.first;
		int i = query.second.second; // index at which the answer will be inserted

		while(index < arr.size() && arr[index] <= ai) {
			trie.insert(arr[index]); // insert the element from arr till we found higher element
			index++;
		}

		if (index == 0) { 
			// if index is still 0 means there is every elenebt bigger than ai in arr, 
			// in this case put -1 at ith index of ans
			
			ans[i] = -1;
		}
		else {
			int maximumXor = trie.max_xor(xi);
			ans[i] = maximumXor;
		}
	}

	return ans;
}