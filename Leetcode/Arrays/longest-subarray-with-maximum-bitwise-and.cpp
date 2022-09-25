/*
    https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and/
    
    This is very similar to Kadane's max sum subarray problem.
    Here we track the max AND subarray. For the current element,
    we check whether it is better to have the element alone or 
    with the subarray. 
    
    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        if(nums.empty())
            return 0;
        
        int max_len = 1, max_and = nums[0];
        int start = 0, end = 1, n = nums.size();
        int sub_and = nums[0];
        
        while(end < n) {
            // check if the current element alone is greater than the
            // subarray and or not. If it is, then update the start of current window
            if(nums[end] > (sub_and & nums[end])) {
                sub_and = nums[end];
                start = end;
            }
            else 
                sub_and = sub_and & nums[end];
            
            // Update max if the current AND subarray is > AND subarray found so far or
            // if it has a longer length with max AND value
            if(max_and < sub_and || (max_and == sub_and && (end - start + 1) > max_len)) {
                max_and = sub_and;
                max_len = end - start + 1;
            }
            ++end;
        }
        return max_len;
    }
};
