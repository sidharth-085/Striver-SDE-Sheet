#include <iostream>
#include <stack>
using namespace std;

// A celebrity is a person who knows noone but everyone knows him/her.

bool knows(int a, int b) {
    // this function always given in the question that Is A knows B or not.
}

// Approach 1 using graph 
// Time complexity: O(N*N)
// Space complexity: O(N)

int findCelebrity(int n) {

    // Calculating indegree and outdegree of each nodes.
    vector<int> indegree(n), outdegree(n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(knows(i, j)) {
                indegree[j]++;
                outdegree[i]++;
            }
        }
    }

    // Finding Celebrity.
    int celebrity = -1;

    for(int i = 0; i < n; i++) {
        if(indegree[i] == n - 1 && outdegree[i] == 0) {
            celebrity = i;
            break;
        }
    }

    return celebrity;
}

// Approach 2: Brute Force 1
// Time Complexity: O(N^2)
// Space Complexity: O(1)

int findCelebrity(int n) {
    for (int i=0; i<n; i++) {
        int knownCount = 0;
        int unknownCount = 0;
        for (int j=0; j<n; j++) {
            if (i == j) {
                continue;
            }
            if (knows(i, j) == false) {
                unknownCount++;
            }
        }

        for (int j=0; j<n; j++) {
            if (i == j) {
                continue;
            }
            if (knows(j, i) == true) {
                knownCount++;
            }
        }

        if (knownCount == n-1 && unknownCount == n-1) {
            return i;
        }
    }
    return -1;
}

// Approach 3: Brute Force 2

int findCelebrity(int n) {
    
    int celebrity = -1;

    // Check one by one whether the person is a celebrity or not.
    for(int i = 0; i < n; i++) {
        bool knowAny = false, knownToAll = true;

        // Check whether perosn with id 'i' knows any other person.
        for(int j = 0; j < n; j++) {
            if(i != j && knows(i, j) == true) {
                knowAny = true;
                break;
            }
        }

        // Check whether perosn with id 'i' is known to all the other person.
        for(int j = 0; j < n; j++) {
            if(i != j and !knows(j, i)) {
                knownToAll = false;
                break;
            }
        }

        if(!knowAny && knownToAll) {
            celebrity = i;
            break;
        }
    }

    return celebrity;
}

// Approach 4 Using Stacks
// Time Complexity: O(N)

int findCelebrity(int n) {
    // step 1: add all persons in the stack

    stack<int> stk;
    for (int i=0; i<n; i++) {
        stk.push(i);
    }

    // step 2: take out 2 persons at a time till 1 person left in the stack & check the 
    // condition for celebrity.

    while (stk.size() > 1) {
        int person1 = stk.top();
        stk.pop();

        int person2 = stk.top();
        stk.pop();
        
        // if person1 knows person2 means person1 cannot be the celebrity, but person2 can be.
        if (knows(person1, person2)) { 
            stk.push(person2);
        }
        // if person2 knows person1 means person2 cannot be the celebrity, but person1 can be.
        else {
            stk.push(person1);
        }
    }

    // step 3: check the potential celebrity left in stack knows noone & everybody knows him.
    int potentialCelebrity = stk.top();
    stk.pop();

    for (int i=0; i<n; i++) {
        if (i != potentialCelebrity) {
            // it checks that if potentialCelebrity knows anyone & any person doesn't know
            // potential celebrity, it means potentialCelebrity cannot be the celebrity.
            if (knows(potentialCelebrity, i) || !knows(i, potentialCelebrity)) {
                return false;
            }
        }
    }
    return potentialCelebrity;
}

// Approach 5: Optimal Method using Two Pointer Approach

int findCelebrity(int n) {
    // keep two pointers
    int start = 0;
    int end = n-1;

    while (start < end) {
        if (knows(start, end)) {
            // it means start cannot be the celebrity
            start++;
        }
        else {
            // it means end cannot be the celebrity
            end--;
        }
    }

    int celebrity = start;
    bool knowAny = false, knownToAll = true;

    for (int i=0; i<n; i++) {
        if (knows(celebrity, i) && i != celebrity) {
            knowAny = true;
            break;
        }
    }

    for (int i=0; i<n; i++) {
        if (!knows(i, celebrity) && i != celebrity) {
            knownToAll = false;
            break;
        } 
    }

    if (knownToAll == true && knowAny == false) {
        return celebrity;
    }
    return -1;
}