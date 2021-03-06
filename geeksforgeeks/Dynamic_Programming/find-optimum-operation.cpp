/*
    https://practice.geeksforgeeks.org/problems/find-optimum-operation/0
*/
#include <bits/stdc++.h>
using namespace std;

int solve(int &n) {
    // dp(i): min ops to make number i
    vector<int> dp(n+1, 0);
    
    for(int i = 1; i <= n; i++)
        // Each number can be made by either +1 or *2
        // So pick the min ops required for the nums from
        // which current num can be created.
        // Multiplication works only for even numbers, so +INF for odd nums
        dp[i] = 1 + min(dp[i-1], i % 2 ? INT_MAX : dp[i/2]);
    return dp[n];
}

int main()
{
    int t, n;
    cin >> t;
    while(t--) {
        cin >> n;
        cout << solve(n) << endl;
    }
	return 0;
}