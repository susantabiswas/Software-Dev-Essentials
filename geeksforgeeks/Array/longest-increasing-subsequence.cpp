/*
    https://practice.geeksforgeeks.org/problems/longest-increasing-subsequence/0
*/
#include <bits/stdc++.h>
using namespace std;

int solve(vector<int>& nums) {
    const int N = nums.size();
    // dp(i): length of longest increasing seq. ending at ith
    // elements as the last element
    vector<int> dp(N, 1);
    int ans = 1;
    
    for(int i = 1; i < N; i++)
        for(int j = 0; j < i; j++)
            if(nums[j] < nums[i]) {
                dp[i] = max(dp[i], 1 + dp[j]);
                ans = max(ans, dp[i]);
            }
    return ans;
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