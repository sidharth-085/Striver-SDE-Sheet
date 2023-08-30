#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// Approach 1: Using Stringstream
// Time Complexity: O(N)
// Space Complexity: O(1)

int createAtoi(string str) {
    // step 1: remove the trail spaces from string str

    int i = 0;
    while (str[i] == ' ') {
        i++;
    }

    str = str.substr(i);

    // step 2: after removing spaces check is at first position any sign is present

    int size = str.size();

    char sign;
    if (str[0] == '-' || str[0] == '+') {
        sign = str[0];
        str = str.substr(1);
    }

    // step 3: now traverse the string till non integer found

    i = 0;
    while (i < size && str[i] >= '0' && str[i] <= '9') {
        i++;
    }

    // step 4: take only numeric part using substr function

    str = str.substr(0, i);

    // step 5: if string str is empty means only non integer character present, return
    // 0.

    if (str.empty()) {
        return 0;
    }

    // step 6: if there is negative sign, add the sign before str

    if (sign == '-') {
        str = sign + str;
    }
    
    // step 7: finally convert string str to integer using stringstream.

    stringstream ss(str);

    int finalAns;

    ss >> finalAns;

    return finalAns;
}

// Approach 2: Optimal Method
// Time Complexity: O(N)
// Space Complexity: O(1)

int createAtoi(string str) {
    // step 1: remove the spaces first

    int i = 0;
    while (str[i] == ' ') {
        i++;
    }

    // step 2: after removing spaces check is there first character is - or +

    bool positive = false;
    bool negative = false;

    if (str[i] == '+') {
        positive = true;
        i++;
    }

    if (str[i] == '-') {
        negative = true;
        i++;
    }

    // step 3: run the while loop and convert the given string into the number
    double ans = 0;
    // using ans as double to store long values, not using long long because giving
    // wrong answer

    while (i < str.size() && str[i] >= '0' && str[i] <= '9') {
        ans = ans * 10 + (str[i] - '0');
        i++;
    }

    // if ans is 0, means no number is there hence return 0.
    if (ans == 0) {
        return ans;
    }

    // if negative is true, means there is negative sign so add it to ans.
    if (negative == true) {
        ans = -ans;
    }

    // step 4: now check that is ans is bigger than INT_MAX or smaller than INT_MIN
    // if yes, replace the answer value to ans to INT_MAX and INT_MIN.

    if (ans > INT_MAX) {
        ans = INT_MAX;
    }

    if (ans < INT_MIN) {
        ans = INT_MIN;
    }

    return (int)(ans);
}