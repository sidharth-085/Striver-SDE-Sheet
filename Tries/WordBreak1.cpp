#include <vector>
#include <string>
using namespace std;

// Approach using Tries
// Time complexity: High due to searchin in tries everytime

// Time Complexity: O(M^3)
// where M is sum of lengths of all word 

class TrieNode { // new way of implementing Trie.
    public:
    TrieNode* children[26];
    bool isTerminated = false;

    bool isPresent(char ch) {
        return children[ch - 'a'] != NULL;
    }

    TrieNode* get(char ch) {
        return children[ch - 'a'];
    }

    void put(char ch) {
        children[ch - 'a'] = new TrieNode();
    }

    void setEnd() {
        isTerminated = true;
    }

    bool isEnd() {
        return isTerminated;
    }
};

class Trie {
    public:
    TrieNode *root;
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) { // insert word function.
        TrieNode *temp = root;
        for (int i=0; i<word.size(); i++) {
            if (!temp->isPresent(word[i])) {
                temp->put(word[i]);
            }
            temp = temp->get(word[i]);
        }
        temp->setEnd();
    }

    bool search(string word) { // search word function.
        TrieNode *temp = root;
        for (int i=0; i<word.size(); i++) {
            temp = temp->get(word[i]);
            if (temp == NULL) { 
                return false;
            }
        }
        return temp->isEnd();
    }
};

bool wordBreak(vector<string> &arr, int n, string &target) {
    Trie trie;
    for (int i=0; i<n; i++) {
        trie.insert(arr[i]); // push everything
    }

    string temp = target;

    while (temp.size() != 0) {
        for (int len = 1; len<=temp.size(); len++) {
            string s = temp.substr(0, len); // search every substring from 0
            if (trie.search(s) == true) { // if found move the temp to forward
                temp = temp.substr(len);
                break;
            }
        }
        if (temp.size() == target.size()) { 
            // if we dont found any substring in words dictionary
            break;
        }
    }

    if (temp.size() != 0) { // if temp is completely found return true
        return false;
    }
    return true;
}