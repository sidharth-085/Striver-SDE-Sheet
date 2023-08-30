#include <iostream>
#include <unordered_set>
using namespace std;

// We have to return the count of distinct substrings of the given string word

// Approach 1: Using Brute Force (by generating all substrings and add in set)

// Time Complexity: O(N^3)
// There will be total O(N^2) time to generate all substrings & push in set take O(N) 
// time for every substring

// Space Complexity: O(N^2)

int distinctSubstring(string &word) {
    unordered_set<string> set;

    for (int i = 0; i < word.size(); i++) {
        for (int len = 1; len <= word.size(); len++) {
            string substr = word.substr(i, len);
            set.insert(substr);
        }
    }

    return set.size();
}

// Approach 2: Using Trie

/*
	
	Time complexity: O(N ^ 3)
	Space complexity: O(N ^ 2) 

	Where N represents the length of word.

*/

class TrieNode {
    public:

	TrieNode *childern[26];

	TrieNode() {
		for (int i = 0; i < 26; i++) {
			childern[i] = NULL;
		}
	}

	~TrieNode() {
        for (int i = 0; i < 26; i++) {
            if (childern[i] != NULL) {
                delete childern[i];
            }
        }
    }
};

class Trie {
    TrieNode *root;

    void countNodeInTrie(TrieNode *curr, int &countNodes) {
	    if (curr == NULL) {
		    return;
	    }

	    for (int i = 0; i < 26; i++) {
		    if (curr->childern[i] != NULL) {
			    countNodes++;
			    countNodeInTrie(curr->childern[i], countNodes);
		    }
	    }
    }

    public:

    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
    }

    void insert(string &str) {
	    TrieNode *curr = root;

	    for (int i = 0; i < str.length(); i++) {
		    int ind = str[i] - 'a';

		    if (curr->childern[ind] == NULL) {
			    curr->childern[ind] = new TrieNode();
		    }
		    curr = curr->childern[ind];
	    }
    }

    void countNodesInTrie(int &countNodes) {
        countNodeInTrie(root, countNodes);
    }
};

int distinctSubstring(string &word) {
    Trie trie;
	int countNodes = 0;

	// Iterate over the word and add it's substrings into the Trie.
	for (int i = 0; i < word.length(); i++) {
		string h = word.substr(i); // insert every substring in trie from 0 to i
		trie.insert(h);
	}

    trie.countNodesInTrie(countNodes);

	return countNodes;
}