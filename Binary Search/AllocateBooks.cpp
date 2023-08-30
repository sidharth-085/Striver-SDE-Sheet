#include <iostream>
#include <vector>
using namespace std;

// So, we are given N books and M number of students. We have to allocate the N books 
// to M students, and below conditions are satisfied:

// 1. Each student gets atleast one book.
// 2. Each book can only allocate to one student.
// 3. Book allocation should be in contagious manner

// such that the maximum number of pages one student have is minimum.

// Approach 1: Brute Force Linear search solution
// Time Complexity: O((sum - max + 1)*N)
// Space Complexity: O(1)

// N is number of books given

int countStudents(vector<int> &books, int numBooks, int pages) {
    int requiredStudents = 1;
    
    int currPages = 0;

    for (int i=0; i<numBooks; i++) {
        if (currPages + books[i] <= pages) {
            currPages = currPages + books[i];
        }
        else {
            requiredStudents++;
            currPages = books[i];
        }
    }
    
    return requiredStudents;
}

int findPages(vector<int>& books, int numBooks, int students) {
    // step 1: check is students is more than number of books

    if (students > numBooks) {
        return -1;
    }

    // step 2: find the maximum pages of the books given && total sum of the pages
    // of books

    int maxPages = books[0];
    int totalSum = 0;
    
    for (int i=0; i<numBooks; i++) {
        maxPages = max(maxPages, books[i]);
        totalSum = totalSum + books[i];
    }

    // step 3: traverse from maxPages to totalSum by Linear Search

    for (int pages = maxPages; pages <= totalSum; pages++) {
        int requiredStudents = countStudents(books, numBooks, pages);

        if (requiredStudents > students) { 
            // if requiredStudents exceeds the given students, skip the pages
            continue;
        }
        else { // if found correct requiredStudents return the pages as ans
            return pages;
        }
    }

    return -1;
}

// Approach 2: Binary Search 
// Time Complexity: O(N*Log(sum-max+1))
// Space Complexity: O(1)

int countStudents(vector<int> &books, int numBooks, int pages) {
    int requiredStudents = 1;
    
    int currPages = 0;

    for (int i=0; i<numBooks; i++) {
        if (currPages + books[i] <= pages) {
            currPages = currPages + books[i];
        }
        else {
            requiredStudents++;
            currPages = books[i];
        }
    }
    
    return requiredStudents;
}

int findPages(vector<int>& books, int numBooks, int students) {
    // step 1: check is students is more than number of books

    if (students > numBooks) {
        return -1;
    }

    // step 2: find the maximum pages of the books given && total sum of the pages

    int maxPages = books[0];
    int totalSum = 0;
    
    for (int i=0; i<numBooks; i++) {
        maxPages = max(maxPages, books[i]);
        totalSum = totalSum + books[i];
    }

    int low = maxPages;
    int high = totalSum;

    // step 3: traverse from maxPages to totalSum by Binary Search

    while (low <= high) {
        int mid = low + (high - low)/2;

        int requiredStudents = countStudents(books, numBooks, mid);

        if (requiredStudents > students) {
            // if requiredStudents exceeds the given students, move right to decrease count
            low = mid + 1;
        }
        else { // if requiredStudents becomes less than the given students move left
            high = mid - 1;
        }
    }

    return low;
}