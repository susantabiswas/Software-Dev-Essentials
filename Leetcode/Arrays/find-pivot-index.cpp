/*
    https://leetcode.com/problems/find-pivot-index/
    
    TC: O(N)
    SC: O(N)
    
    - Precompute the cummulative sum from right to left
    - Then scan from left to right and for each position check if the right side sum equals the cummulative left side sum
    - Handle the last right most index separately
    
*/
class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        // find the right to left cummulative sum
        vector<long> left(nums.size(), 0);
        long sum = 0;
        for(int i = nums.size() - 1; i >= 0; i--) {
            sum += nums[i];
            left[i] = sum;
        }
        
        // check for pivot index in [0..N-2]
        sum = 0;
        for(int i = 0; i < nums.size() - 1; i++) {
            if(sum == left[i + 1])
                return i;
            sum += nums[i];
        }
        
        // check if rightmost index is pivot or not
        if(sum == 0)
            return nums.size() - 1;
        return -1;
    }
};
