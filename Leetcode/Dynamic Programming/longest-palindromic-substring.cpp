/*
  5. Longest Palindromic Substring
  https://leetcode.com/problems/longest-palindromic-substring/

  Brute Force
    TC: O(2^n), each time we take 2 calls if the chars are not same, where the size is decreased by 1
        = 2T(n-1)
    SC: O(n)
*/

class Solution {
public:
    
    // using bottom up
    string longestPalindromeTab(string& s) {
        if(s.empty())
            return "";
        
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), -1));
        string max_palin;
        int max_len = 0;
        
        // all single chars are palindromes
        for(int i = 0; i < s.size(); i++)
            dp[i][i] = 1;
        
        max_len = 1, max_palin = s[0];
        
        // find out if substrings are palindromic by checking lengthwise, 
        // starting 2 to N
        for(int l = 2; l <= s.size(); l++) {
            for(int i = 0; i <= s.size() - l; i++) {
                // substring end index
                int j = i + l - 1;
                // length 2 substrings
                if(l == 2) {
                    dp[i][j] = (s[i] == s[j]) ? 1 : 0;
                }
                else {
                    dp[i][j] = (s[i] == s[j]) && dp[i+1][j-1];
                }
                
                // update max length
                if(dp[i][j] == 1 && (max_len < j-i+1)) {
                    max_len = j-i+1;
                    max_palin = s.substr(i, j-i+1);;
                }
            }
        }
        return max_palin;
    }
    
    // using memoization
    int longestPalindromeMem(string& s, int i, int j, vector<vector<int>>& dp, 
                             int& max_len, string& max_palin) {
        // base cases
        // when out of bound
        if(j < 0 || i > s.size())
            return 0;
        
        // same char
        if(j == i) {
            return dp[i][j] = 1;
        }
        // length two
        if(j-i == 1) {
            // if they are palindromic 
            if(s[i] == s[j]) {
                dp[i][j] = 1;
                if(max_len < 2) {
                    max_len = 2;
                    max_palin = s.substr(i, 2);
                }
            }
            else
                dp[i][j] = 0;
            return dp[i][j];
        }
        
        if(i > j)
            return 0;
        
        if(dp[i][j] == -1) {
            // current range is palindromic iff  ith and jjth chars are same and substring[i+1:j-1] is also palindromic
            dp[i][j] = longestPalindromeMem(s, i+1, j-1, dp, max_len, max_palin)
                        && s[i] == s[j];
            
            // explore the other substrings
            longestPalindromeMem(s, i+1, j, dp, max_len, max_palin);
            longestPalindromeMem(s, i, j-1, dp, max_len, max_palin);
            
            // update max palindromic length
            if(dp[i][j] == 1) {
                if(max_len < j-i+1) {
                    max_len = j-i+1;
                    max_palin = s.substr(i, j-i+1);
                }
            }
        }
        
        return dp[i][j];
    }
    
    // driver function for memoization
    string longestPalindromeMemDriver(string& s) {
                vector<vector<int>> dp(s.size(), vector<int>(s.size(), -1));
        int max_len = 0;
        string max_palin;
        
        longestPalindromeMem(s, 0, s.size()-1, dp, max_len, max_palin);
        
        // if there are no multi char palindromes, then return the first char of length 1 as palindrome
        if(max_len == 0 && s.size() > 0) {
            max_palin = s[0];
        }
        return max_palin;
    }
    
    string longestPalindrome(string s) {
        // return longestPalindromeMemDriver(s);
        return longestPalindromeTab(s);
    }
};
