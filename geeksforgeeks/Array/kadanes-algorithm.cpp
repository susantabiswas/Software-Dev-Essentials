/*
    https://practice.geeksforgeeks.org/problems/kadanes-algorithm/0
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include <bits/stdc++.h>
using namespace std;

// Using Kadane's Algo
long long solve(vector<int>& nums) {
    long long max_sum = INT_MIN, curr_sum = 0;
    for(const long long &num: nums) {
        curr_sum += num;
        // handles the case of -ve nums and when the current
        // contiguous sum is lesser than current num
        curr_sum = max(curr_sum, num);
        max_sum = max(max_sum, curr_sum);
    }
    return max_sum;
}

int main()
{
    int t, n;
    cin >> t;
    while(t--) {
        cin >> n;
        vector<int> nums(n);
        
        for(int i = 0; i < n; i++)
            cin >> nums[i];
            
        cout << solve(nums) << endl;
    }
	return 0;
}