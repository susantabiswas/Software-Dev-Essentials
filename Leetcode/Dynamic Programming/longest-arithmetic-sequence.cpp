/*
    https://leetcode.com/problems/longest-arithmetic-sequence/
    
    It is very similar to LIS problem, but the catch is here we have more constraints 
    than LIS, we can just add a term to be part of a series like LIS, here it can
    only be part of a series when it also shares the common diff that is there in the series.
    
    Now we just track the max length series diff for each term, then also it wont work, since
    there might be a term later on which completes a longer series if it gets a few more sequences.
    
    EG: 1,2,4,6,8
    for 4, if we save only diff 3 {1,4}, then it wont make the longest length with {2,4,6,8} with 
    diff 2, so we save the max length ending at each term for all the differences encountered.
    with the previous terms.
    
    We save info like: for 4: (3,2){with 1}, (2,2){with2}
    So for 6, we can just see if there was a series with diff=2 ending at 4, that gives
    us dp[indexof(4)][2] = 2, so dp[indexof(6)] = 2 + 1
    
    TC: O(N^2)
    SC: O(N*diff), diff: max unique number of differences between any two terms of array, which can be N-1
*/

class Solution {
public:
    int longestArithSeqLength(vector<int>& arr) {
        if(arr.size() <= 1)
        return arr.size();
        
        int max_len = 0;
        // dp(i): dict of (diff, length) for ith index 
        vector<unordered_map<int, int>> dp(arr.size());

        for(int i = 1; i < arr.size(); i++)
            // check with the previous terms the if there is a series
            // with diff (a[i] - a[j])
            for(int j = 0; j < i; j++) {
                int diff = (arr[i] - arr[j]);
                // check if there is an AP ending before ith term
                // with the same diff and include the current term
                int max_ap_len = 1 + (dp[j].count(diff) ? dp[j][diff] : 0);
                // max length AP found ending with current ith term so far,
                // if this is the first time then it makes the length 2 using {a[i], a[j]}
                int max_len_ending_here = dp[i].count(diff) ? dp[i][diff] : 2;

                dp[i][diff] = max(max_len_ending_here, max_ap_len);
                max_len = max(max_len, dp[i][diff]);
            } 
        return max_len;
    }
};

