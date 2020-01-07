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
    // TC : O(n)
    // SC: O(1)
    int robTabular(vector<int>& nums) {
        if(nums.empty())
            return 0;
        
        const int N = nums.size();
        // max value gained if the previous house was robbed and not robbed
        int robbed_prev = 0, not_robbed_prev = 0;
        // max value gaine if current house is robbed and not robbed
        int robbed_curr = 0, not_robbed_curr = 0;
        
        for(int i = 0; i < N; i++) {
            // if current house is robbed, then max value is 
            // whatever gained till the previous house 
            // by not robbing it + current house value
            robbed_curr = nums[i] + not_robbed_prev;
            // if current house is not robbed, max value is whichever
            // is max out of robbing or not robbing the previous house
            not_robbed_curr = max(not_robbed_prev, robbed_prev);
            
            // make the current values as previous for the next house
            robbed_prev = robbed_curr, not_robbed_prev = not_robbed_curr;
        }
        return max(robbed_prev, not_robbed_prev);
    }
    
    
    // Using DP
    // TC: O(N), SC:O(N)
    int robTabular(vector<int>& nums) {
        if(nums.empty())
            return 0;
        
        const int N = nums.size();
        vector<int> robbed(N, 0);
        vector<int> not_robbed(N, 0);
        
        for(int i = 0; i < N; i++) {
            // if the current house is robbed
            robbed[i] = nums[i] + ((i >= 1) ? not_robbed[i-1] : 0);
            // if the current house is not robbed
            not_robbed[i] = (i >= 1) ? max(not_robbed[i-1], robbed[i-1]) : 0;
        }
        return max(robbed[N-1], not_robbed[N-1]);
    }
    
    
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
