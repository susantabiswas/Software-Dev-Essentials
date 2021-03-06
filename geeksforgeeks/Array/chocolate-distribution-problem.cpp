/*
    https://www.geeksforgeeks.org/chocolate-distribution-problem/
    
    Since the aim is to reduce the gap between the max and min, 
    we can sort the numbers and look for the 'm' sized window with
    min diff of max and min. In a sorted array, a window with min
    diff of left and right side element is the optimal one because
    any other element if is part of optimal sol and is not in the window,
    then it will either < left or > right, making the gap more.
    
    TC: O(nlogn)
*/

#include <bits/stdc++.h>
using namespace std;

int solve(vector<int>& nums, int &m) {
    sort(nums.begin(), nums.end());
    int min_diff = INT_MAX;
    
    // We look for the window with min(|max_num - min_num|) of
    // length m
    for(int i = 0; i < nums.size() - m + 1; i++) {
        min_diff = min(min_diff, abs(nums[i] - nums[i + m - 1]));
    }
    return min_diff;
}

int main()
{
    int t, n, m;
    cin >> t;
    while(t--) {
        cin >> n;
        vector<int> nums(n);
        
        for(int i = 0; i < n; i++)
            cin >> nums[i];
        cin >> m;
        cout << solve(nums, m) << endl;
    }
	return 0;
}