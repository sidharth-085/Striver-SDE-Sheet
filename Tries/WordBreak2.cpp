#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

// Approach 1: Recursion
// Time Complexity: O(N * 2^(N - 1))
// Space Complexity: O(N * 2^(N - 1))

vector<string> wordBreakHelper(string &str, int si, unordered_set<string> &dictSet, int n) {
    // step 1: check is string is completed, if yes return empty string vector 
    
    if (si == n) {
        return {""};
    }

    // step 2: make some variables storing the current word from string str and two
    // vectors subList containing the answer from recursion and completeList for 
    // return as answer after appending the word at the starting

    string word = "";
    vector<string> subList;
    vector<string> completeList;

    // step 3: traverse the string str from starting index si

    for (int i=si; i<n; i++) {
        word.push_back(str[i]);
        // add the characters one by one to the word string

        if (dictSet.find(word) != dictSet.end()) {
            // once we find the word which exists in the dictionary set, we will do our
            // work

            subList = wordBreakHelper(str, i + 1, dictSet, n);
            // after getting the first word which is present in the dictSet, find
            // answer for remaining string by calling recursion and starting from i + 1

            for (int j=0; j<subList.size(); j++) {
                // if the jth string from recursion is non empty, add the word at the 
                // starting and update the subList with new string.

                if (subList[j].size() != 0) {
                    string temp = word;
                    temp.append(" ");
                    temp.append(subList[j]);

                    subList[j] = temp;
                }
                // and if the jth string is empty, append just the word which exists
                // in the map

                else {
                    subList[j] = word;
                }
            }

            // step 4: finally copy the subList into completeList and return the list

            for (int j=0; j<subList.size(); j++) {
                completeList.push_back(subList[j]);
            }
        }  
    }

    return completeList;
}

vector<string> wordBreak(string &str, vector<string> &dictionary) {
    int n = str.size();
    unordered_set<string> dictSet;

    // use the dictSet to check is current word exists in the dictionary or not.

    for (int i=0; i<dictionary.size(); i++) {
        dictSet.insert(dictionary[i]);
    }
    
    // call the helper function

    return wordBreakHelper(str, 0, dictSet, n);
}

// Approach 2: Memoization for Recursion
// Time Compelxity: O(N * 2^(N - 1))
// Space Compelxity: O(N * 2^(N - 1))

vector<string> wordBreakHelper(string &str, int si, unordered_set<string> &dictSet, unordered_map<int, vector<string>> &map, int n) {
    // step 1: check is string is completed, if yes return empty string vector 
    
    if (si == n) {
        return {""};
    }

    // check is current starting index have the vector of string or not, if have return
    // the vector without computing

    if (map.find(si) != map.end()) {
        return map[si];
    }

    // step 2: make some variables storing the current word from string str and two
    // vectors subList containing the answer from recursion and completeList for 
    // return as answer after appending the word at the starting

    string word = "";
    vector<string> subList;
    vector<string> completeList;

    // step 3: traverse the string str from starting index si

    for (int i=si; i<n; i++) {
        word.push_back(str[i]);
        // add the characters one by one to the word string

        if (dictSet.find(word) != dictSet.end()) {
            // once we find the word which exists in the dictionary set, we will do our
            // work

            subList = wordBreakHelper(str, i + 1, dictSet, map, n);
            // after getting the first word which is present in the dictSet, find
            // answer for remaining string by calling recursion and starting from i + 1

            for (int j=0; j<subList.size(); j++) {
                // if the jth string from recursion is non empty, add the word at the 
                // starting and update the subList with new string.

                if (subList[j].size() != 0) {
                    string temp = word;
                    temp.append(" ");
                    temp.append(subList[j]);

                    subList[j] = temp;
                }
                // and if the jth string is empty, append just the word which exists
                // in the map

                else {
                    subList[j] = word;
                }
            }

            // step 4: finally copy the subList into completeList and return the list

            for (int j=0; j<subList.size(); j++) {
                completeList.push_back(subList[j]);
            }
        }  
    }

    map[si] = completeList;
    // store the complete list in the map for future use if need.

    return completeList;
}

vector<string> wordBreak(string &str, vector<string> &dictionary) {
    int n = str.size();
    unordered_set<string> dictSet;

    // use the dictSet to check is current word exists in the dictionary or not.

    for (int i=0; i<dictionary.size(); i++) {
        dictSet.insert(dictionary[i]);
    }

    // map for memoization
    unordered_map<int, vector<string>> map;
    
    // call the helper function

    return wordBreakHelper(str, 0, dictSet, map, n);
}

// Approach 3: Using Trie
// Time Complexity: O(N * 2^(N-1))

class TrieNode {
    public: 
    TrieNode *children[26];
    bool isTerminal;

    TrieNode() {
        for (int i=0; i<26; i++) {
            children[i] = NULL;
        }
        isTerminal = false;
    }
};

class Trie {
    TrieNode *root;

    void searchHelper(string &str, int n, int si, string temp, vector<string> &result) {
        // make current pointer to traverse whole trie
        
        TrieNode *curr = root;

        for (int i=si; i<n; i++) {
            int index = str[i] - 'a';
            // make the index from ith character of string str
            
            // if the current character is not present in trie, just return without
            // doing anything

            if (curr->children[index] == NULL) {
                return;
            }

            // while traversing if we get the character at which we found the end means
            // this is the word exists in trie

            if (curr->children[index]->isTerminal == true) {
                string lastWord = temp;

                // add the word from si to current ith index which is present in trie
                // to the string lastWord

                lastWord.append(str.substr(si, i - si + 1));

                // if we reached to last character of string str means string str is 
                // completly traversed, so add the lastWord to the result.

                if (i == n - 1) {
                    result.push_back(lastWord);
                }

                // else we not reached to end of the string str, continue the traversal
                // and find answer for further string and append space to the lastWord

                else {
                    searchHelper(str, n, i + 1, lastWord + " ", result);
                }
            }

            curr = curr->children[index];
            // continue the traversal by shifting curr pointer to ahead
        }
    }

    public:

    // general function to insert the string in the trie
    void insert(string word) {
        TrieNode *temp = root;

        for (int i=0; i<word.size(); i++) {
            int index = word[i] - 'a';

            if (temp->children[index] == NULL) {
                TrieNode *newNode = new TrieNode();
                temp->children[index] = newNode;
            }

            temp = temp->children[index];
        }

        temp->isTerminal = true;
    }

    // search function to do the work on string str and return the result
    void search(string &str, vector<string> &result) {
        string temp;
        int n = str.size();

        searchHelper(str, n, 0, temp, result);
    }
};

vector<string> wordBreak(string &str, vector<string> &dictionary) {
    // step 1: create trie and insert all the words in dictionary to the trie

    Trie trie;

    for (int i=0; i<dictionary.size(); i++) {
        trie.insert(dictionary[i]);
    }

    // step 2: make the result vector and pass to the search function of the trie
    
    vector<string> result;

    trie.search(str, result);

    return result;
}