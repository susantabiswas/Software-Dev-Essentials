/*
    https://leetcode.com/problems/regular-expression-matching/
    Solutions:
    1. Memoization
    2. Tabular
*/
class Solution {
public:
    // Using Memoization
    // TC: O(MN), SC: O(MN)
    int regexMatch(vector<vector<int>>& dp, string& s, string& p, 
                   int i, int j) {
        if(i == 0 && j == 0)
            return dp[i][j] = 1;
        // if the length of any string has become 0
        // then it is not a match except if the char in pattern is *
        if(i == 0 && j != 0)
            return dp[i][j] = p[j-1] == '*' && regexMatch(dp, s, p, i, j-2);
        // pattern has finished but not the source
        if(i != 0 && j == 0)
            return dp[i][j] = 0;
        
        if(dp[i][j] == -1) {
            // initially mark it true
            dp[i][j] = 1;
            // if the chars are same
            if(s[i-1] == p[j-1])
                dp[i][j] = regexMatch(dp, s, p, i-1, j-1);
            else {
                // when chars are different, then only if the pattern contains '.'
                // or '*' matching the string s then it is valid
                if(p[j-1] == '.')
                    dp[i][j] = regexMatch(dp, s, p, i-1, j-1);
                else if(p[j-1] == '*') {
                    // With * we can either try using it or not use it 
                    int with_star = 0, without_star = 0;
                    // USE *
                    // if the pattern char match the * char of string source
                    // check for the previous char of source
                    if(s[i-1] == p[j-2] || p[j-2] == '.')
                        with_star = regexMatch(dp, s, p, i-1, j);
                    
                    // DON'T USE * 
                    // also covers the case when current pattern char is wildcard * and doesn't match
                    // the char of source, try the char before '*' of pattern
                    without_star = regexMatch(dp, s, p, i, j-2);
                    dp[i][j] = with_star || without_star;
                }
                // chars don't match
                else 
                    dp[i][j] = 0;
            }
        }
        
        return dp[i][j];
    }
    
    // driver memoization function
    bool regexMatchDriver(string& s, string& p) {
        vector<vector<int>> dp(s.size() + 1, vector<int>(p.size() + 1, -1));
        regexMatch(dp, s, p, s.size(), p.size());
        return dp[s.size()][p.size()];
    }
    
    // Tabular driver
    // TC: O(MN), SC: O(MN)
    bool regexMatchTabular(string& s, string& p) {
        vector<vector<int>> dp(s.size() + 1, vector<int>(p.size() + 1, 1));
        
        // when source string is zero, pattern is only allowed to have *
        for(int i = 1; i <= p.size(); i++)
            dp[0][i] = p[i-1] == '*' && i-2 >= 0 ? dp[0][i-2] : 0;
        // when pattern length is zero
        for(int i = 1; i <= s.size(); i++)
            dp[i][0] = 0;
        
        for(int i = 1; i <= s.size(); i++) {
            for(int j = 1; j <= p.size(); j++) {
                // if the chars are same 
                if(s[i-1] == p[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else {
                    // different chars are allowed only incase of wilcard chars
                    if(p[j-1] == '.')
                        dp[i][j] = dp[i-1][j-1];
                    // when *
                    else if(p[j-1] == '*') {
                        // we have two choices, either use * or don't use
                        int with_star = (j - 2 >= 0) ? (p[j-2] == '.' || s[i-1] == p[j-2]) && dp[i-1][j] : 0;
                        int without_star = (j - 2 >= 0) ? dp[i][j-2] : 0;
                        dp[i][j] = with_star || without_star;
                    }
                    // when chars are diff
                    else
                        dp[i][j] = 0;
                }
            }
        }
        return dp[s.size()][p.size()];
    } 
    
    
    bool isMatch(string s, string p) {
        //return regexMatchDriver(s, p);
        return regexMatchTabular(s, p);
    }
};
