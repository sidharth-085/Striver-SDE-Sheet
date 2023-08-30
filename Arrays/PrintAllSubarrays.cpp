#include <iostream>
#include <vector>
using namespace std;

vector< vector<int> > printAllSubarrays(vector<int> &arr, int n) {
    vector< vector<int> > ans;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            vector<int> subArr;
            for (int k = i; k <= j; k++) {
                subArr.push_back(arr[k]);
            }
            ans.push_back(subArr);
        }
    }
    return ans;
}