/*
    https://leetcode.com/problems/arithmetic-slices-ii-subsequence/
    
    TC:  O(N^2)
    SC: O(N * num_unique_diff)
*/

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        // dp[i] = Hash table of <diff, seq length ending at ith element>  
        vector<unordered_map<long, long>> dp(nums.size());
        long arithmetic_seq = 0;
        
        for(int i = 0; i < nums.size(); i++) {
            // for the current element, find all the 
            // longest arithmetic sequences that can end here for a given difference
            for(int j = 0; j < i; j++) {
                // Current diff with a number in [0:i) 
                long diff = (long) nums[i] - nums[j];
                // The current number can be appended at the end of all the 
                // sequences which were found till jth index for the given diff
                // Also the ith and jth number can also form a seq of length 2, hence the + 1
                long sequences_ending_here = dp[j].count(diff) ? dp[j][diff] + 1 : 1;
                                
                dp[i][diff] += sequences_ending_here;
                // Since (nums[i], nums[j]) have size of 2, so we remove it, hence -1
                arithmetic_seq += sequences_ending_here - 1;
            }
        }
        return arithmetic_seq;
    }
};
