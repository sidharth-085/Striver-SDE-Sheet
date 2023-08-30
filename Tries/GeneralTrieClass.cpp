#include <iostream>
#include <string>
using namespace std;

class TrieNode {
    public:
    char data;
    TrieNode **children;
    bool isTerminal;

    TrieNode(char data) {
        this->data  = data;
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
            child = new TrieNode(word[0]);
            root->children[index] = child;
        }
        else {
            // Node for the current character already exists, use it
            child = root->children[index];
        }

        // Recursively insert the remaining characters of the word
        insertWord(child, word.substr(1));
    }

    bool searchWord(TrieNode *root, string word) {
        if (word.empty()) {
            // Reached the end of the word, return whether the current node is terminal or not
            return root->isTerminal;
        }

        int index = word[0] - 'a';
        if (root->children[index] == NULL) {
            // Node for the current character doesn't exist, word is not present
            return false;
        }

        // Recursively search for the remaining characters of the word
        bool ans = searchWord(root->children[index], word.substr(1));
        return ans;
    }

    void removeWord(TrieNode *root, string word) {
        if (word.empty()) {
            // Reached the end of the word, mark the current node as non-terminal
            root->isTerminal = false;
            return;
        }

        int index = word[0] - 'a';
        TrieNode *child;
        if (root->children[index] == NULL) {
            // Node for the current character doesn't exist, nothing to remove
            return;
        }
        child = root->children[index];
        removeWord(child, word.substr(1));

        if (child->isTerminal == false) {
            // If the child node is not a terminal node, check if it has any non-null children
            for (int i = 0; i < 26; i++) {
                if (child->children[i] != NULL) {
                    // Child has non-null children, so it should not be removed
                    return;
                }
            }
            // Child node can be safely removed
            delete child;
            root->children[index] = NULL;
        }
    }   

    bool startsWithPrefix(TrieNode *root, string prefix) {
        if (prefix.empty()) {
           return true; 
        }

        int index = prefix[0] - 'a';
        if (root->children[index] == NULL) {
            return false;
        }
        TrieNode *child = root->children[index];
        return startsWithPrefix(child, prefix.substr(1));
    }

    public:

    Trie() {
        root = new TrieNode('\0');
    }

    void insert(string word) {
        insertWord(root, word);
    }

    bool search(string word) {
        bool ans = searchWord(root, word);
        return ans;
    }

    void remove(string word) {
        removeWord(root, word);
    }

    bool startWith(string prefix) {
        return startsWithPrefix(root, prefix);
    }
};