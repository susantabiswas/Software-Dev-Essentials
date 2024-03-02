/*
    https://leetcode.com/problems/remove-element/
    
    TC: O(n)
    SC: O(1)
*/
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int write = 0;
        
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] != val)
                nums[write++] = nums[i];
        }
        return write;
    }
};
