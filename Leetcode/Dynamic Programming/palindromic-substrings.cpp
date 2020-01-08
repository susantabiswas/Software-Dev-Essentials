/*
    https://leetcode.com/problems/palindromic-substrings/
    
    TC: O(N^2)
    SC: O(N^2)
*/
class Solution {
public:
    int countSubstrings(string s) {
        const int N = s.size();
        vector<vector<int> > dp(N, vector<int>(N, 0));
        
        // all single chars are palindromes
        for(int i = 0; i < N; i++)
            dp[i][i] = 1;
        
        // we check for each substring lengthwise and
        // determine they are palindromic or not based on 
        // whether the current boundary end chars are same and if they
        // are same, then is the [i+1 : j-i] substring also palindromic
        for(int l = 1; l < N; l++)
            // starting endpoint
            for(int i = 0; i < N - l; i++) {
                // closing endpoint
                int j = i + l;
                
                // if the chars are same, check if the inbetween substring is palindromic
                if(s[i] == s[j]) {
                    // strings of length 2 are palindromic if the end chars match
                    if(j - i + 1 == 2)
                        dp[i][j] = 1;
                    else
                        dp[i][j] = dp[i+1][j-1];
                }
                else    // if boundary chars are diff, no way they are palindromic
                    dp[i][j] = 0;
                    
            }
                
        // find the number of all substrings which are palindromic 
        int num_palindromes = 0;
        for(auto v: dp)
            num_palindromes += accumulate(v.begin(), v.end(), 0); 
        
        return num_palindromes;
    }
};
