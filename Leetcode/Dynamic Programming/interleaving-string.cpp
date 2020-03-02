/*
    https://leetcode.com/problems/interleaving-string/submissions/
    
    Solutions:
    1. Top-down, TC: O(MN)
    2. Bottom-up, TC: O(MN)
*/

class Solution {
public:
    // Checks if interleaves using top-down DP
    /*
        If the string interleaves, then that means the entire s1 and s2 will be used 
        for making s3. So len(s1) + len(s2) = len(s3).
        So till any pos. k in s3, we would have used i of s1 and j of s2.
        So we track if string till (i + j) interleaves with s3[i+j-1]
        
        TC: O(MN)
    */
    bool isInterleaveMem(int i, int j, int k, string& s1, string& s2, string& s3,
                        vector<vector<int>>& dp) {
        // when the total char length is zero
        // also check if s1 and s2 has ended as well
        if(k == 0)
            return (i || j) ? false : true;
        
        if(dp[i][j] == -1) {
            // do dfs with the string whose current char matches s3
            dp[i][j] = (i-1) >= 0 && s1[i-1] == s3[k-1] && isInterleaveMem(i-1, j, k-1, s1, s2, s3, dp) ||
                        (j-1) >= 0 && s2[j-1] == s3[k-1] && isInterleaveMem(i, j-1, k-1, s1, s2, s3, dp);
        }
        return dp[i][j];
    }
    
    bool isInterleaveMemDriver(string& s1, string& s2, string& s3) {
        int M = s1.size(), N = s2.size(), K = s3.size();
        // the strings interleaves only if the sum of string lengths match
        if(M + N != K)
            return false;
        
        // dp(i, j): if string till s[i+j-1] interleaves till s1[i] and s2[j]  
        vector<vector<int>> dp(M + 1, vector<int>(N + 1, -1));
        return isInterleaveMem(M, N, K, s1, s2, s3, dp);
    }
    
    // Checks if interleaves using bottom-up DP
    /*
        If the string interleaves, then that means the entire s1 and s2 will be used 
        for making s3. So len(s1) + len(s2) = len(s3).
        So till any pos. k in s3, we would have used i of s1 and j of s2.
        So we track if string till (i + j) interleaves with s3[i+j-1]
        
        TC: O(MN)
    */
    bool isInterleaveTab(string& s1, string& s2, string& s3) {
        const int M = s1.size(), N = s2.size();
        // the strings interleaves only if the sum of string lengths match
        if(M + N != s3.size())
            return false;
        
        // dp(i, j): if string till s[i+j-1] interleaves till s1[i] and s2[j]  
        vector<vector<bool>> dp(M + 1, vector<bool>(N + 1, false));
        // when s1, s2 and s3 are empty
        dp[0][0] = true;
        // when s2 is empty
        for(int i = 1; i <= M; i++)
            dp[i][0] = dp[i-1][0] && s3[i-1] == s1[i-1];
        // when s1 is empty
        for(int i = 1; i <= N; i++)
            dp[0][i] = dp[0][i-1] && s3[i-1] == s2[i-1];
    
        for(int i = 1; i <= M; i++)
            for(int j = 1; j <= N; j++)
                // s3 interleaves if till the current length it was interleaving and one of chars from
                // s1 or s2 match the current position in s3
                dp[i][j] = (s1[i-1] == s3[i+j-1] && dp[i-1][j]) ||
                            (s2[j-1] == s3[i+j-1] && dp[i][j-1]);
        
        return dp[M][N];
    }
    
    bool isInterleave(string s1, string s2, string s3) {
        //return isInterleaveTab(s1, s2, s3);
         return isInterleaveMemDriver(s1, s2, s3);
    }
};
