/*
    338. Counting Bits
    https://leetcode.com/problems/counting-bits/
*/

class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> dp(num + 1, -1);
        // fill the first two entries
        if (num >= 0)
            dp[0] = 0;
        if(num >= 1)
            dp[1] = 1;
        
        // fill the first two answers
        vector<int> ans;
        for(int i = 0; i <= num && i <= 1; i++)
            ans.emplace_back(dp[i]);
        
        // for each number, we add its LSB and check the number of digits in
        // the number except for the LSB(right shifted by 1 number )
        for(int i = 2; i <= num; i++) {
            dp[i] = (i & 1) + dp[i >> 1];
            ans.emplace_back(dp[i]);
        }
        
        return ans;
    }
};
