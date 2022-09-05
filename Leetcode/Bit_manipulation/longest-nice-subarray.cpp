/*
    https://leetcode.com/problems/longest-nice-subarray/
    
    TC: O(N)
    SC: O(1)
    
    Intuition:
    A window is nice if each of the numbers there have unique set bits positions.
    Eg: [2,3,1]
    2 = 010, 3 = 011, 1 = 001
    Nice => [2,1] 010 & 001 => 000
    Whereas [3,1] 011 & 001 => 001
    
    Since any pair within that subarray should be nice as well, that means overall
    all the numbers should have unique set bit positions, hence we can just track
    whether the subarray is nice or not using a single variable which has OR of all the
    nums in that subarray.
    
    Using sliding window we expand the window and then shrink the window when the window becomes invalid.
    To take away the contribution of previous number from the subarray we can use XOR, as XOR of same bits is 0.
    So XOR of same number with the window_and will reset the contribution of that number.
    
    Usually in a max len sliding window, we do expansion and then shrink, but here it might get tricky to do that.
    So we first ensure that the window is safe to add the current number by shrinking and then add the current number.
*/
class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int start = 0, end = 0;
        int max_len = 0;
        int n = nums.size(), window_nums = 0;
        
        while(end < n) {
            // Check if adding the current number makes the 
            // window not nice or not
            // A window will be nice, if each of the set bits 
            // of all the numbers are mutually exclusive and when
            // that happens the window AND num = 0
            while(window_nums & nums[end]) {
                // Unset the bits of left side number and shrink the
                // window further
                window_nums ^= nums[start];
                ++start;
            }
            // expand the window by adding the current number to the window
            // We add the set bits of current number by doing the OR operation
            window_nums |= nums[end++];
            
            max_len = max(max_len, end - start);
        }
        return max_len;
    }
};
