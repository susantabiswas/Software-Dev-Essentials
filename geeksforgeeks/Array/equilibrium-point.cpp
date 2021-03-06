/*
    https://practice.geeksforgeeks.org/problems/equilibrium-point/0
    
    Save the right side sum and after that do 
    a traversal from left to check.
    TC: O(N)
    SC: O(N)
*/
#include <bits/stdc++.h>
using namespace std;

int solve(vector<int> &nums) {
    // save the right hand side sum
    // +1 in size so that when we start traversal from
    // left side, we need the right side sum so for last
    // element we have 0 sum for its right side
    vector<long> right_sum(nums.size()+1, 0);
    int curr_sum = 0;
    
    for(int i = nums.size()-1; i >= 0; i--) {
        curr_sum += nums[i];
        right_sum[i] = curr_sum;
    }
    
    // We start traversal from left side
    curr_sum = 0;
    for(int i = 0; i < nums.size(); i++) {
        // check if the left hand and right sum match
        if(curr_sum == right_sum[i+1])
            return i + 1;
        curr_sum += nums[i];
    }
    return -1;        
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