/*
    523. Continuous Subarray Sum
    https://leetcode.com/problems/continuous-subarray-sum/
*/
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        // stores the cummulative sum
        vector<int> dp(nums.size(), 0);
        
        long long sum = 0;
        for(int i=0; i < nums.size(); i++) {
            dp[i] = sum + nums[i];
            sum += nums[i];
        }
        
        // we consider all subarrays of least size 2,
        // if any subarray sum is multiple of target, return true
        for(int i = 0; i < nums.size(); i++) {
            for(int j = i+1; j < nums.size(); j++) {
               
                long long range_sum = (i-1) >= 0 ? dp[j] - dp[i-1]: dp[j];
                // when target is non-zero
                if(k && range_sum % k == 0)
                    return true;
                // when target is zero
                else if(!k && range_sum == 0)
                    return true;
            }
        }
        return false;
    }
};
