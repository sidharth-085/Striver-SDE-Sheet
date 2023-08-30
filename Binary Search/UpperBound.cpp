#include <iostream>
using namespace std;

// Upper bound is the implementaion in which we have to return the index at which
// arr[i] > target.
int upperBound(int *arr, int size, int target) {
    int ans = -1;
    int low = 0;
    int high = size-1;

    while (low <= high) {
        int mid = (low + high)/2;

        if (arr[mid] > target) {
            ans = mid;
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return ans;
}

int main() {

}