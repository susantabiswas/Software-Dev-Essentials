/*
    https://leetcode.com/problems/delete-and-earn/submissions/
    
    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        // The only thing stopping us from picking every number for
        // scoring is the adjacent number constraint, so we keep track of all the
        // possible number of elements with their total sum as seen in nums
        // Idea is for each number check if we can get more score by 
        // 1. picking that number + max value without the previous number 
        // 2. Not using current number and using the max seen till last number either
        // by using last or skipping last
        vector<int> num_sum(2001, 0);
        for(auto num: nums)
            num_sum[num] += num;
        
        // Max value when the last operation was using a number 
        int use_prev = 0;
        // Max value when last operation was skipping a number
        int skip_prev = 0;
        for(int i = 0; i < num_sum.size(); i++) {
            // Max value with operation of using a number
            int use = max(skip_prev + num_sum[i], use_prev);
            // Max value if current number is not used
            int skip = max(use_prev, skip_prev);
            
            skip_prev = skip;
            use_prev = use;
        }
        
        return max(use_prev, skip_prev);
    }
};
