#include <iostream>
using namespace std;

void prefixMax(int *arr, int size) {
    // prefix max array is the array in which each ith element contains maximum value from 0 to ith index.
    int *prefixMaxArray = new int[size];
    
    prefixMaxArray[0] = arr[0]; // start element is same as given array.
    for (int i=1; i<size; i++) {
        prefixMaxArray[i] = max(arr[i], prefixMaxArray[i-1]);
    }
}

void suffixMax(int *arr, int size) {
    // suffix max array is the array in which each ith element contains maximum value from ith to size-1 index.
    int *suffixMaxArray = new int[size];
    
    suffixMaxArray[size-1] = arr[size-1];
    for (int i = size-2; i>=0; i--) {
        suffixMaxArray[i] = max(suffixMaxArray[i+1], arr[i]);
    }
}

int main() {

}