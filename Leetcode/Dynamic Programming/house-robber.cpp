/*
    198. House Robber
    https://leetcode.com/problems/house-robber/
    
    Logic:
        max value for ith house: max(value_curr_robbed, value_curr_not_robbed)
        value_curr_robbed = value_curr + value_prev_not_robbed
        value_curr_not_robbed = max(value_prev_robbed, value_prev_not_robbed)
*/

class Solution {
public:
    int maxRob(int curr, vector<int>& nums, vector<int>& dp,
              int& inc_curr, int& exc_curr) {
        // last house
        if(curr < 0) {
            return 0;
        }
        
        if(dp[curr] == 0) {
            int rob_curr = 0, dont_rob = 0;
            maxRob(curr-1, nums, dp, rob_curr, dont_rob);
            
            // update the values
            inc_curr = nums[curr] + dont_rob;
            exc_curr = max(rob_curr, dont_rob);
            
            dp[curr] = max(inc_curr, exc_curr);
        }
        return dp[curr];
    }
    
    // using memoization
    int maxRobMem(vector<int>& nums) {
        vector<int> dp(nums.size(), 0);
        int inc_curr = 0, exc_curr = 0;
        
        maxRob(nums.size()-1, nums, dp, inc_curr, exc_curr);
        return max(inc_curr, exc_curr);
    }
    
    // using tabular approach
    int maxRobTab(vector<int>& nums) {
        if(nums.empty())
            return 0;
        
        // max value without robbing / robbing previous house
        int exc_prev = 0, inc_prev = nums[0];
        // max value robbing / not robbing current house
        int inc_curr = 0, exc_curr = 0;
        
        for(int i = 1; i < nums.size(); i++) {
            // if current is not robbed
            exc_curr = max(inc_prev, exc_prev);
            // if current is robbed
            inc_curr = nums[i] + exc_prev;
            
            inc_prev = inc_curr;
            exc_prev = exc_curr;
        }
        return max(inc_prev, exc_prev);
    }
    
    int rob(vector<int>& nums) {
        //return maxRobMem(nums);
        
        return maxRobTab(nums);
    }
};
