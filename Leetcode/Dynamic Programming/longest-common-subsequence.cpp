/*
  https://leetcode.com/problems/longest-common-subsequence/
*/
class Solution {
public:
    // using memoization
    int lcsRec(vector<vector<int> >& dp, 
               string& a, string& b, int i, int j) {
        // base case
        if(i < 0 || j < 0)
            return 0;
        
        if(dp[i][j] == -1) {
            dp[i][j] = 0;
            // when the string characters are same, add 1 + the max in a[0:i-1] and b[0:j-1]
            if(a[i] == b[j])
                dp[i][j] = 1 + lcsRec(dp, a, b, i-1, j-1);
            else 
                // since the chars are different, take the max of
                // previous combination
                dp[i][j] = max(lcsRec(dp, a, b, i-1, j),
                               lcsRec(dp, a, b, i, j-1));
        }
        return dp[i][j];
    }
    
    int lcsRecDriver(string& a, string& b) {
        const int N = a.size(), M = b.size();
        // dp(i, j): length of longest common subsequence between A[0:i] and B[0:j]
        vector<vector<int> > dp(N, vector<int>(M, -1));
        return lcsRec(dp, a, b, N-1, M-1);
    }
    
    // Using Tabular approach 
    int longestCommonSubsequenceIter(string& a, string& b) {
        if(a.empty() || b.empty())
            return 0;
        const int N = a.size(), M = b.size();
        // dp(i, j): length of longest common subsequence between A[0:i] and B[0:j]
        vector<vector<int> > dp(N, vector<int>(M, 0));
        
        for(int i = 0; i < N; i++)
            for(int j = 0; j < M; j++) {
                if(a[i] == b[j])
                    dp[i][j] = 1 + ((i >= 1 && j >= 1) ? dp[i-1][j-1] : 0);
                else
				// since the chars are different, take the max of a[0 : i-1] and b[0 : j] or
				// a[0 : i] and b[0 : j-1]
                    dp[i][j] = max( (i >= 1) ? dp[i-1][j] : 0,
                                    (j >= 1) ? dp[i][j-1] : 0);
            }
        return dp[N-1][M-1];
    }
    
    int longestCommonSubsequence(string text1, string text2) {
        //return lcsRecDriver(text1, text2);
        return longestCommonSubsequenceIter(text1, text2);
    }
};
