/*
    https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/
    
    Solved using :  1. Top down
                    2. Bottom up
                    3. Using longest common substring
*/
class Solution {
public:
    
    // Tabular approach
    // TC: O(MN), SC: O(MN)
    int minDeleteSumTabular(string& s1, string& s2) {
        const int N = s1.size(), M = s2.size();
        vector<vector<int> > dp(N + 1, vector<int>(M + 1, 0)); 
        
        for(int i = 0; i <= N; i++) {
            for(int j = 0; j <= M; j++) {
                // if any of strings is empty, other non empty string should be deleted
                if(i == 0 || j ==0) {
                    if(i == 0 && j == 0)
                        dp[i][j] = 0;
                    else if(i == 0)
                        dp[i][j] = s2[j-1] + dp[i][j-1];
                    else if(j == 0)
                        dp[i][j] = s1[i-1] + dp[i-1][j];
                }        
                else {
                    // when chars are same, no need to delete
                    if(s1[i-1] == s2[j-1])
                        dp[i][j] = dp[i-1][j-1];
                    // when chars are different, pick the char which is smallest in value and delete
                    else
                        dp[i][j] = min(s1[i-1] + dp[i-1][j],
                                      s2[j-1] + dp[i][j-1]);
                }
            }
        }
        
        return dp[N][M];
    }
    
    // longest common substring sum
    int longestCommonSubsequenceIter(string& a, string& b) {
        if(a.empty() || b.empty())
            return 0;
        const int N = a.size(), M = b.size();
        // dp(i, j): sum of longest common subsequence between A[0:i] and B[0:j]
        vector<vector<int> > dp(N, vector<int>(M, 0));
        
        for(int i = 0; i < N; i++)
            for(int j = 0; j < M; j++) {
                if(a[i] == b[j])
                    dp[i][j] = a[i] + ((i >= 1 && j >= 1) ? dp[i-1][j-1] : 0);
                else
				// since the chars are different, take the max of a[0 : i-1] and b[0 : j] or
				// a[0 : i] and b[0 : j-1]
                    dp[i][j] = max( (i >= 1) ? dp[i-1][j] : 0,
                                    (j >= 1) ? dp[i][j-1] : 0);
            }
        return dp[N-1][M-1];
    }
    
    // The characters which are common need not be deleted, so
    // we find the longest common substring sum. Now find the sum value of 
    // both the strings, from there we need to delete everything other than LCS
    // Since LCS is there is both the strings, so we subtract lcs twice.
    int minDeleteSumLCS(string& s1, string& s2) {
        int lcs = longestCommonSubsequenceIter(s1, s2);
        int s1_sum = accumulate(s1.begin(), s1.end(), 0);
        int s2_sum = accumulate(s2.begin(), s2.end(), 0);
       
        return s1_sum + s2_sum - 2*lcs;
    }
    
        // Recursion using memoization
    // TC: O(MN), SC: O(MN)
    int minDeleteSumRec(vector<vector<int> >& dp, string& s1, string& s2,
                       int i, int j) {
        if(i == 0 && j == 0)
            return 0;
        // if any of strings is empty, other non empty string should be deleted
        if((!i && j) || (i && !j))
            return dp[i][j] = (i == 0 ?  s2[j-1] + minDeleteSumRec(dp, s1, s2, i, j-1): 
                                         s1[i-1] + minDeleteSumRec(dp, s1, s2, i-1, j));
        
        if(dp[i][j] == 0) {
            // if the chars are same, current chars are not deleted
            if(s1[i-1] == s2[j-1])
                dp[i][j] = minDeleteSumRec(dp, s1, s2, i-1, j-1);
            else {
                // pick and delete the smallest value char
                dp[i][j] += min(s1[i-1] + minDeleteSumRec(dp, s1, s2, i-1, j),
                              s2[j-1] + minDeleteSumRec(dp, s1, s2, i, j-1));
            }
        }
        return dp[i][j];
    }
    
    // Top-down driver
    int minDeleteSumRecDriver(string& s1, string& s2) {
        const int N = s1.size(), M = s2.size();
        // dp(i, j): sum of longest common subsequence between A[0:i] and B[0:j]
        vector<vector<int> > dp(N + 1, vector<int>(M + 1, 0)); 
        
        return minDeleteSumRec(dp, s1, s2, N, M);
    }

    
    int minimumDeleteSum(string s1, string s2) {
        return minDeleteSumTabular(s1, s2);
        //return minDeleteSumLCS(s1, s2);
        //return minDeleteSumRecDriver(s1, s2);
    }
};
