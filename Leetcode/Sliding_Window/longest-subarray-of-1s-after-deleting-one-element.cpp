/*
    https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/
    
    TC: O(n)
    SC: O(1)
    
    Idea is to find the longest window of 1s such that there is atmost 1 zero in it.
*/
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int max_len = 0;
        int start = 0, end = 0;
        
        int zero = 0;
        
        int n = nums.size();
        
        // find the max length window with atmost 1 zero
        while(end < n) {
            // expand the window
            if(!nums[end++])
                ++zero;
            
            // shrink the window till we have <= 1 zero in the window
            while(zero > 1) {
                if(!nums[start++])
                    --zero;
            }
            
            max_len = max(max_len, end - start);
        }
        
        // -1 to account for the included 0
        return max_len - 1;
    }
};
