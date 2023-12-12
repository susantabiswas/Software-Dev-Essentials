/*
    https://leetcode.com/problems/longest-palindromic-subsequence/

    Brute Force
    TC: O(2^n), each time we take 2 calls if the chars are not same, where the size is decreased by 1
        = 2T(n-1)
    SC: O(n)
*/
class Solution {
public:
    // Bottom-up approach
    // TC: O(N*N), SC: O(N*N)
    int longestPalindromeSubseqTabular(string& s) {
        if(s.empty())
            return 0;
        
        const int N = s.size();
        // dp(i, j): length of longest palindromic substring in s[i:j]
        vector<vector<int> > dp(N, vector<int>(N, 0));
        
        // all single chars are palindromic
        for(int i = 0; i < N; i++)
            dp[i][i] = 1;
        
        for(int l = 1; l < N; l++) {
            // starting index of window
            for(int i = 0; i < N - l; i++) {
                // ending index of window
                int j = i + l;
                
                // if there are only two chars
                if((j - i + 1) == 2) {
                    // if the chars are same, then that contributes 2, otherwise since
                    // individually they are palindromic so max length 1
                    dp[i][j] = 1 + (s[i] == s[j]);
                }
                else {
                    // for s[i:j]:
                    // longest palindrome length in s[i+1 : j-1] and +1 if s[i] == s[j]
                    // if s[i] != s[j], longest length palindrome = Max of longest palin in s[i:j-1] and s[i+1:j]
                    if(s[i] == s[j])
                        dp[i][j] = dp[i+1][j-1] + 2;
                    else
                        dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                }
            }
        }
        return dp[0][N-1];
    }
    
    // Using memoization
    // TC: O(N*N), SC: O(N*N)
    int longestPalindSubseqRec(vector<vector<int> >& dp, string& s, int i, int j) {
        if(i > j)
            return 0;
        // when one char
        if(i == j)
            return dp[i][j] = 1;
        
        if(dp[i][j] == -1) {
            if(s[i] == s[j])
                dp[i][j] = 2 + longestPalindSubseqRec(dp, s, i+1, j-1);
            else
                dp[i][j] = max(longestPalindSubseqRec(dp, s, i+1, j),
                               longestPalindSubseqRec(dp, s, i, j-1));
        }
        return dp[i][j];
    }
    
    // Recursive driver
    int longestPalindSubseqRecDriver(string& s) {
        if(s.empty())
                return 0;

        const int N = s.size();
        // dp(i, j): length of longest palindromic substring in s[i:j]
        vector<vector<int> > dp(N, vector<int>(N, -1)); 
        
        return longestPalindSubseqRec(dp, s, 0, N-1);
    }
    
    int longestPalindromeSubseq(string s) {
        return longestPalindSubseqRecDriver(s);
        //return longestPalindromeSubseqTabular(s);
    }
};
