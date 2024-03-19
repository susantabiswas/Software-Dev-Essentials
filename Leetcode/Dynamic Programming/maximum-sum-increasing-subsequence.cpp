/*
	https://www.codingninjas.com/studio/problems/1112624

	Maximum Sum Increasing Subsequence 

	TC: O(n^2)

	Similar to LIS, instead of tracking the count of chain, we just save the max value of increasing chain

*/
#include <bits/stdc++.h> 
int maxIncreasingDumbbellsSum(vector<int> &rack, int n)
{
	// Write your code here
	vector<int> dp(n, 0);
	int max_wt = 0;

	for(int i = 0; i < n; i++) {
		dp[i] = rack[i];

		for (int j = 0; j < i; j++) {
			if(rack[j] < rack[i])
				dp[i] = max(dp[i], rack[i] + dp[j]);
		}
		max_wt = max(max_wt, dp[i]);
	}

    return max_wt;
}
