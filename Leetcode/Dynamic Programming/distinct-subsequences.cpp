/*
    https://leetcode.com/problems/distinct-subsequences/
*/
class Solution {
public:
    int numDistinct(string s, string t) {
        const int N = s.size(), M = t.size();
        
        // dp(i, j): no. of unique subsequences matching T[:i] in s[:j] 
        vector<vector<long long> > dp(M+1, vector<long long>(N+1, 0));
        
        // empty target string can be made only once
        for(int i = 0; i <= N; i++)
            dp[0][i] = 1;
        // when string S is empty, target can't be reached except when target is empty
        for(int i = 1; i <= M; i++)
            dp[i][0] = 0;
        
        for(int i = 1; i <= M; i++)
            for(int j = 1; j <= N; j++) {
                // when the t[i-1] == s[j-1], means this can form strings in 
                // 1. no. of ways in which strings till t[:i-2] can be formed in s[:j-2],
                //    as it will just append to all those
                // 2. or whatever no. of times we see t[i-1] in string s[:j-2], that is exclude the 
                //    current char of s matching t[i-1]
                if(t[i-1] == s[j-1]) {
                    long long include_curr = dp[i-1][j-1];
                    long long exclude_curr = dp[i][j-1];
                    dp[i][j] = include_curr + exclude_curr;
                }
                else
                    // when the chars are different, then no. of ways is whatever can be formed by s[:j-2] for t[:i-1]
                    dp[i][j] = dp[i][j-1];
            }
        
        return dp[M][N];
    }
};
