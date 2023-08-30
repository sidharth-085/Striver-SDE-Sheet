#include <iostream>
#include <stack>
#include <unordered_map>
using namespace std;

// Approach 1: Using Stack
// Time Complexity: O(N)
// Space Complexity: O(N)

bool isValidParenthesis(string str) {
    // check is given string is empty or not

    if (str.size() == 0) {
        return true;
    }

    // make a stack for storing opening brackets

    stack<int> stk;

    for (int i=0; i<str.size(); i++) {
        if (str[i] == '(' || str[i] == '{' || str[i] == '[') {
            // if opening brackets found, push it in the stack
            stk.push(str[i]);
        }
        else if (str[i] == ')') {
            if (!stk.empty() && stk.top() == '(') { 
                // if both open and close pair found, pop the stack
                stk.pop();
            }
            else { 
                // if not, we found incorrect pair return false
                return false;
            }
        }
        else if (str[i] == '}') {
            // if both open and close pair found, pop the stack
            if (!stk.empty() && stk.top() == '{') {
                stk.pop();
            }
            // if not, we found incorrect pair return false
            else {
                return false;
            }
        }
        else if (str[i] == ']') {
            // if both open and close pair found, pop the stack
            if (!stk.empty() && stk.top() == '[') {
                stk.pop();
            }
            // if not, we found incorrect pair return false
            else {
                return false;
            }
        }
    }

    if (stk.empty()) {
        return true;
    }
    return false;
}

// Approach 2: Using stack and hashmap for storing the open and close bracket pairs
// Time Complexity: O(N)
// Space Complexity: O(N)

bool isValidParenthesis(string str) {
    stack<char> stk;
    unordered_map<char, char> bracketMap = {{')', '('}, {'}', '{'}, {']', '['}};
    
    for (char ch : str) {
        if (ch == '(' || ch == '{' || ch == '[') {
            stk.push(ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (!stk.empty() && stk.top() == bracketMap[ch]) {
                stk.pop();  // Mismatched or no matching opening bracket
            }
            else {
                return false;
            }
            
        }
    }

    return stk.empty();  // Check if there are any unmatched opening brackets left
}