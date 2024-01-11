/*
    https://leetcode.com/problems/count-vowels-permutation/
    
    TC: O(n)
    SC: O(n)
    
    Idea is very simple:
    For an ith length string, find all the ways to create strings of length 'i' that end with each vowel.
    We try to add the valid vowels with i-1th length string and make it end with a vowel.
    The rules are already present that defines which vowel can follow which letter.
    
    eg for string of length 2, find all ways to create strings that end with each of the vowels (a, e, i, o, u)
    vowel 'e' can only be added with a string (len=n-1) that has ended with vowel 'a' or 'i'
    dp[n]['e'] = dp[n-1]['a'] + dp[n-1]['i']
    
    dp[n]['e'] = no. of ways in which we can create a n length string that ends with 'e'
    
*/
class Solution {
public:
    int countVowelPermutation(int n) {
        if(n == 0)
            return 0;
        
        const int MOD = pow(10, 9) + 7;
        
        vector<unordered_map<char, long long>> dp(n+1);
        
        dp[1]['a'] = dp[1]['e'] = dp[1]['i'] = dp[1]['o'] = dp[1]['u'] = 1;
        
        for(int i = 2; i <= n; i++) {
            dp[i]['a'] = ((dp[i-1]['e'] + dp[i-1]['u']) % MOD + dp[i-1]['i']) % MOD;
            dp[i]['e'] = (dp[i-1]['a'] + dp[i-1]['i']) % MOD;
            dp[i]['i'] = (dp[i-1]['e'] + dp[i-1]['o']) % MOD;
            dp[i]['o'] = dp[i-1]['i'] % MOD;
            dp[i]['u'] = (dp[i-1]['o'] + dp[i-1]['i']) % MOD;
        }
        
        long long count = 0;
        
        for(auto [_, v]: dp[n])
            count = (count + v) % MOD;
        
        return count; 
    }
};
