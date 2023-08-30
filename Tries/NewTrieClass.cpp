#include <iostream>
using namespace std;

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

    bool startWith(string prefix) {
        TrieNode *temp = root;

        for (int i=0; i < prefix.size(); i++) {
            temp = temp->get(prefix[i]);
            if (temp == NULL) { 
                return false;
            }
        }
        return true;
    }
};