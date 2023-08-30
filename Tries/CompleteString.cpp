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

    // this search function checks that is every prefix of a word is present or not.

    bool search(string word) { // search word function.
        TrieNode *temp = root;
        for (int i=0; i<word.size(); i++) {
            temp = temp->get(word[i]);
            if (!temp->isEnd() || temp == NULL) { 
                // in this step it goes to every char in given string & check is it have 
                // isTerminated false, if yes it means that word is not exists in trie. 
                // Hence return false.
                return false;
            }
        }
        return true;
    }
};

string completeString(int n, vector<string> &words){
    Trie *trie = new Trie();
    
    int size = words.size();
    for (int i=0; i<size; i++) {
        trie->insert(words[i]);
    }

    string maxString;
    for (int i=0; i<size; i++) {
        if (trie->search(words[i])) {
            if (maxString.size() < words[i].size()) {
                maxString = words[i];
            }
            else if (maxString.size() == words[i].size()) {
                if (words[i] < maxString) {
                    maxString = words[i];
                }
            }
        }
    }
    if (maxString.size() == 0) {
        return "None";
    }
    return maxString;
}