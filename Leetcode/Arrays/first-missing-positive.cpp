/*
    https://leetcode.com/problems/first-missing-positive/solution/
    
    The idea is to move each number to its correct 0-indexed position. Then traverse
    the array for the second time and the first index where the number doesn't match is
    the answer. If the array has everything in place, then N + 1 is the answer.
    The fact that the array size is N, so even if there are numbers greater than N,
    they need not be considered as the array that should be at that place can always be the
    answer even if all other numbers are present, so need to consider > N.
    
    TC: O(N)
    SC: O(1)
*/
/*
    https://leetcode.com/problems/first-missing-positive/solution/
    
    The idea is to move each number to its correct 0-indexed position. Then traverse
    the array for the second time and the first index where the number doesn't match is
    the answer. If the array has everything in place, then N + 1 is the answer.
    The fact that the array size is N, so even if there are numbers greater than N,
    they need not be considered as the array that should be at that place can always be the
    answer even if all other numbers are present, so need to consider > N.
    
    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        for(int i = 0; i < nums.size();) {
            // swap the current number to its correct position
            if(nums[i] >= 0 && nums[i] - 1 >= 0 && nums[i] - 1 < nums.size()) {
                swap(nums[nums[i]-1], nums[i]);
            }
            // if the current number is -ve, 0 or greater than array length or
            // the number is already at its correct position or the correct position
            // of the current number already has a duplicate of this, skip current number
            if(nums[i] <= 0 || nums[i] == i+1 || nums[i] > nums.size() ||
               nums[nums[i]-1] == nums[i])
                ++i;
        }
        
        // answer is the first position (1 based) that doesn't match the number there
        for(int i = 0; i < nums.size(); i++)
            if(nums[i] != i + 1)
                return i + 1;
        return nums.size() + 1;
    }
};
