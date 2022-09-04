/*
    https://leetcode.com/problems/number-of-ways-to-reach-a-position-after-exactly-k-steps/
    
    TC: O(NK)
    SC: O(NK)
    
    Idea is to find the ways to reach the start from the current position.
    dp[end] = F(end - 1) + F(end + 1)
    From each position we can either take either 1 step forward or backward.
    
    Using top down approach, we start with end pos and go towards the start.
*/
class Solution {
private:
    int MOD = pow(10, 9) + 7;
public:
    int mem(int start, int end, int curr, int k,
           unordered_map<int, unordered_map<int, int>>& dp) {
        // if the cmb is already present in cache
        if(dp.count(curr) && dp[curr].count(k))
            return dp[curr][k];
        // if from current position, no. of steps needed to reach start > k
        // we cant reach start
        if(abs(curr - start) > k)
            return 0;
        // If we have taken exactly k steps and are able to reach start
        if(k == 0)
            return dp[curr][k] = curr == start;
        // Can't take any more steps and havent reached start
        if(k < 0)
            return dp[curr][k] = 0;
        
        return dp[curr][k] =( mem(start, end, curr + 1, k - 1, dp) % MOD +
                            mem(start, end, curr - 1, k - 1, dp) % MOD) % MOD;
    }
    
    int numberOfWays(int startPos, int endPos, int k) {
        // <curr pos, <k, ways> >
        // dp[i][k] = no. of ways to reach ith position with k steps from start
        unordered_map<int, unordered_map<int, int>> dp;
        return mem(startPos, endPos, endPos, k, dp);
    }
};
