/*
    https://leetcode.com/problems/move-zeroes/
    
    TC: O(N)
*/
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int write_idx = 0;
        for(int i = 0; i < nums.size(); i++)
            if(nums[i] != 0)
                swap(nums[write_idx++], nums[i]);
    }
};
