/*
    https://leetcode.com/problems/sort-array-by-parity/
    
    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int even = 0;
        
        for(int curr = 0; curr < nums.size(); curr++)
            if(nums[curr] % 2 == 0)
                swap(nums[even++], nums[curr]);
        return nums;
    }
};
