/*
    https://leetcode.com/problems/subsets/
    
    Solution that works with duplicates as well.

    NOTE: No set is used to ensure uniqueness of subsets, this is due
    to the reason that duplicate sets are formed only when we can have the 
    same value at a given position multiple times.
    Eg: [1, 1] => would create duplicate since for pos 0, we can have 
    1 twice.
    Since this problem has only unique nums, so we won't have same number at
    the same position multiple times and hence don't need a set.
*/

class Solution {
public:
    // Using backtracking
    // TC: O(N * 2^N), SC:O(2^N)
    void generateSubsets(vector<int>& nums, vector<int>& partial,
                    int i, vector<vector<int> >& result) {
        if(i == nums.size()) {
            result.emplace_back(partial);
            return;
        }    
        
        // for the current index, we can either include it or choose not to
        partial.emplace_back(nums[i]);
        generateSubsets(nums, partial, i+1, result);
        partial.pop_back();
        generateSubsets(nums, partial, i+1, result);
    }
    
    // driver function for backtracking
    vector<vector<int>> subsetsBacktracking(vector<int>& nums) {
        vector<int> partial;
        vector<vector<int> > result;
        generateSubsets(nums, partial, 0, result);
        
        return result;
    }
    
    // Using iterative method
    // TC: O(N * 2^N)
    vector<vector<int>> generateSubsetsIterative(vector<int>& nums) {
        vector<vector<int> > result = {{}};
        
        for(const int num: nums) {
            const int curr_len = result.size();
            for(int i = 0; i < curr_len; i++) {
                result.emplace_back(result[i]);
                result.back().emplace_back(num);
            }
        }
        return result;
    }
    
    
    vector<vector<int>> subsets(vector<int>& nums) {
        return subsetsBacktracking(nums);
        //return generateSubsetsIterative(nums);
    }
};