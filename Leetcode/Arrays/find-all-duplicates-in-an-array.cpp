/*
    https://leetcode.com/problems/find-all-duplicates-in-an-array/submissions/
    
    TC: O(N)
    SC: O(1)
*/

class Solution {
public:
    // TC: O(N)
    // SC: O(1)
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> result;
        
        // put the numbers at their correct position
        // Swapping involves at max N-1 moves, hence O(N)
        for(int i = 0; i < nums.size(); i++) {
            // it is important to make sure that the current position number
            // is put at its correct pos., this is for the case when a number 
            // which should exists at a later gets moved to the current position
            // and hence will be skipped if not taken care now
            // eg: 2,5,4,5,3 --> 5,2,5,4,3 (normal single swapping) this will fail unless
            // current pos. number is taken care of.
            while(nums[nums[i] - 1] != nums[i])
                swap(nums[nums[i] - 1], nums[i]);
        }
        
        for(int i = 0; i < nums.size(); i++) {
            // check if the current number already
            // exists at the position index equal to current num-1 (1based --> 0 based)
            if(i != nums[i] - 1 && nums[nums[i] - 1] == nums[i])
                result.emplace_back(nums[i]);
        }
        return result;
    }
};
