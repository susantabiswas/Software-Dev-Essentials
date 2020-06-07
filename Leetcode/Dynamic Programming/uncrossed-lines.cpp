/*
    https://leetcode.com/problems/uncrossed-lines/
    
    If we look at the problem carefully, it is actually finding the longest common subsequence.
    Since we have to match the same numbers in both the arrays ensuring that we get the maximum
    length and also make sure that the lines dont overlap, that is basically saying find a
    subsequence in A that matches B. 
*/
class Solution {
public:
    
    // TC: O(N^2), SC:O(MN)
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
        const int M = A.size(), N = B.size();
		// dp(i, j): longest common subsequence with A[0:i-1] and B[0:j-1]
		// Initially the length is 0, which covers the cases when the length of A or B being 0.
        vector<vector<int>> dp(M+1, vector<int>(N+1, 0));
        
        // Now the aim is to find the longest common subsequence 
        for(int i = 1; i <= M; i++)
            for(int j = 1; j <= N; j++) {
                // if the chars are same
                if(A[i-1] == B[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else {
                    // when they are diff, try to find the max length with
                    // i-1 and j-1 chars separately
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
                
        return dp[M][N];
    }
};
