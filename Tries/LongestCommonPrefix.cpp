#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Brute Force Solution: Compare each and every character of first string with every string.
// Time Complexity: O(N^2)

string longestCommonPrefix(vector<string> &arr, int n) {
    string ans;

    for (int i = 0; i < arr[0].size(); i++) {
        char ch = arr[0][i]; // take the ith character of first string
        bool match = true;

        for (int j = 1; j < n; j++) {
            if (ch != arr[j][i] || arr[j].size() < i) { 
                // if the character not matching or size of jth string is less than i
                // break the loop and mark match doesn't found.
                match = false;
                break;
            }
        }

        if (match == false) { // if match is false break the loop, else push character in ans.
            break;
        }
        else {
            ans.push_back(ch);
        }
    }
    return ans;
}

// Approach using Tries:

class TrieNode {
    public:

    TrieNode **children;
    bool isTerminal;
    int childCount = 0;
    
    TrieNode() {
        children = new TrieNode*[26];
        for (int i=0; i<26; i++) {
            children[i] = NULL;
        }
        isTerminal = false;
    }

    bool containsKey(char ch) {
        return children[ch - 'a'] != NULL;
    }

    void put(char ch) {
        children[ch - 'a'] = new TrieNode();
    }

    TrieNode* get(char ch) {
        return children[ch - 'a'];
    }

    void setEnd() {
        isTerminal = true;
    }

    bool isEnd() {
        return isTerminal;
    }
};

class Trie {
    TrieNode *root;

    public:

    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode *temp = root;
        for (int i=0; i<word.size(); i++) {
            if (!temp->get(word[i])) {
                temp->put(word[i]);
                temp->childCount++;
            }
            temp = temp->get(word[i]);
        }
        temp->setEnd();
    }

    void lcp(string str, string &ans) {
        TrieNode *temp = root;
        for (int i=0; i<str.size(); i++) {
            char ch = str[i];
            if (temp->childCount == 1) {
                ans.push_back(ch);
                temp = temp->get(ch);
            }
            else {
                break;
            }

            if (temp->isEnd()) {
                break;
            }
        }
    }
};

string longestCommonPrefix(vector<string> &arr, int n) {
    Trie trie;
    for (int i=0; i<n; i++) {
        trie.insert(arr[i]);
    }

    string ans;
    trie.lcp(arr[0], ans);
    return ans;
}

/* General Trie Class Solution: Recursively

class TrieNode {
    public:
    TrieNode **children;
    bool isTerminal;
    int childCount = 0;

    TrieNode() {
        children = new TrieNode*[26];
        for (int i=0; i<26; i++) {
            children[i] = NULL;
        }
        isTerminal = false;
    }
};

class Trie {
    TrieNode *root;

    void insertWord(TrieNode *root, string word) { // helper function
        if (word.empty()) {
            // Reached the end of the word, mark the current node as terminal
            root->isTerminal = true;
            return;
        }

        int index = word[0] - 'a';
        TrieNode *child;
        if (root->children[index] == NULL) {
            // Create a new node for the current character if it doesn't exist
            child = new TrieNode();
            root->childCount++;
            root->children[index] = child;
        }
        else {
            // Node for the current character already exists, use it
            child = root->children[index];
        }

        // Recursively insert the remaining characters of the word
        insertWord(child, word.substr(1));
    }

    void lcpHelper(TrieNode *root, string str, string &ans) {
        if (str.empty() || root->isTerminal || root->childCount != 1) {
            return;
        }

        int index = str[0] - 'a';
        if (root->childCount == 1) {
            ans.push_back(str[0]);
        }
        lcpHelper(root->children[index], str.substr(1), ans);
    }

    public:

    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        insertWord(root, word);
    }

    void lcp(string str, string &ans) {
        lcpHelper(root, str, ans);
    }
};

string longestCommonPrefix(vector<string> &arr, int n) {
    Trie trie;
    for (int i=0; i<n; i++) {
        trie.insert(arr[i]);
    }
    
    string ans;
    trie.lcp(arr[0], ans);
    return ans;
}

*/