/*
    https://leetcode.com/problems/count-sorted-vowel-strings/
    
    TC: O(n)
    SC: O(n)
    
    Note: [Optimization], space can be further optimized. We only need to track the
        values for last length and current, so instead of dp(nx5), we can create a dp(2x5),
        but leaving that part here.
        
    Idea is if we know all the valid strs with length ending each of the chars, we can just use
    that info to find the no. of valid strs possible ending with length 'l' and one of the vowels.
    
    e.g, 
        dp[2][e] = we can add 'e' with all len=1 strs ending with a, e.
*/
class Solution {
public:
    int countVowelStrings(int n) {
        // a - 0, e - 1, i - 2, o - 3, u - 4
        // dp[l][i] = no. of strs of length 'l' ending with ith vowel
        vector<vector<int>> dp(n+1, vector<int>(5, 0));
        
        // each single letter is a valid string of len 1
        // with l = 1, 'a', 'e', 'i', 'o', 'u'
        for(int i = 0; i < 5; i++)
            dp[1][i] = 1;
        
        // for length 'l', we can add each of chars from ('a', 'e', 'i', 'o', 'u')
        // with a str with l-1
        for(int l = 1; l <= n; l++)
            for(int i = 0; i < 5; i++)
                // i-th char can only be added with all the 
                // chars from 0-i to maintain the lexographic order
                for(int j = i; j >= 0; j--)
                    dp[l][i] += dp[l-1][j];
        
        return accumulate(dp[n].begin(), dp[n].end(), 0);
    }
};
