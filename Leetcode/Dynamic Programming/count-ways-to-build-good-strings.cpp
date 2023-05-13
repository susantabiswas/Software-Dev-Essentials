/*
    https://leetcode.com/problems/count-ways-to-build-good-strings/
    
    TC: O(high)
    SC: O(high)
    
    Idea is to try appending 0 'zero' times and 1 'one' times for a given string of length 'X'.
    Eg: zero: 1, one: 2, low = 2, high=3
    X=0, ""
    X=1, 
        with 1 zero: "" + 0
        with 2 one: not possible since 2 1s have to be appended and string len = 1
    X=2,
        with 1 zero: 0(X=1) + 0
        with 2 one: ""(X=0) + 11
    X=3
        with 1 zero: 00(X=2) + 0
                    11(X=2) + 0
        with 2 one: 0(X=1) + 11
        
    X=0: ""
    X=1: 0
    X=2: 00, 11
    X=3: 000, 110, 011
    
    Pick the strings with length >= 2 and <= 3
    Ans: 00, 11, 000, 110, 011
*/
class Solution {
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        vector<long> dp(high + 1, 0);
        const long MOD = pow(10, 9) + 7;
        
        // we can have 1 good string with 0 length string
        dp[0] = 1;
        
        // for each 'i' check how many strings can be formed by appending
        // 0 'zero' and 1 'one' no. of times respectively.
        for(int i = 1; i <= high; i++) {
            // try appending 0 'zero' no. of times such that
            // length of str is 'i'
            if(i - zero >= 0)
                dp[i] = (dp[i] + dp[i - zero]) % MOD;
                
            // try appending 1 'one' no. of times
            if(i - one >= 0)
                dp[i] = (dp[i] + dp[i - one]) % MOD;
        }
        
        long good_strings = 0;
        for(int i = low; i <= high; i++)
            good_strings = (good_strings + dp[i]) % MOD;
        return good_strings;
    }
};
