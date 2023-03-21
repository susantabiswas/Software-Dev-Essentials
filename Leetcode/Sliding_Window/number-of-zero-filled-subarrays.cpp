/*
    https://leetcode.com/problems/number-of-zero-filled-subarrays/
    
    TC: O(N)
    SC: O(1)
    
    Sliding Window:
    
    This is similar to longest window satisfying a certain condition, but not exactly similar
    at the same time.
    
    First no. of subsets in a set of length n is
    1 + 2 + ... + n
    
    Now idea is to start a sliding window. Whenever the end position has a zero, we know
    that we have come across a valid window of 0s, so to get its size, move the start position
    to the first position with a 0.
    
    update total by adding the length of current window
    
    Now if the current end position is at a non 0 value, then invalidate the window by moving the start
    position to where end is right now.
*/
class Solution {
public:
    long long zeroFilledSubarray(vector<int>& nums) {
        long total = 0;
        
        int start = 0, end = 0;
        while (end < nums.size()) {
            // If the current ending is 0, then make sure that the start is also at 0.
            // If the current window's start is not zero, then shrink till
            // we reach a zero value. 
            while(start < end && end < nums.size() &&
                  nums[end] == 0 && nums[start] != 0) 
                ++start;
            
            // If the current window ends in a zero, above loop ensures that
            // the start is also 0, making the current window entirely full of zeros
            if(end < nums.size() && nums[end] == 0) 
                total += end - start + 1;
            
            // expand while valid
            ++end;
            
            // If the current window has become invalid due to a non zero at the end
            // position, reset the window by putting start at the current position, 
            // making the window size 0
            if(end < nums.size() && nums[end] != 0) {
                start = end;
            }
        }
        
        return total;
    }
};
