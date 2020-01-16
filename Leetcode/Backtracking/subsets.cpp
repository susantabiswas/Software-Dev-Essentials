/*
    https://leetcode.com/problems/subsets/
    
    Solution that works with duplicates as well.
*/

class Solution {
public:
    // Using backtracking
    // TC: O(N * 2^N), SC:O(2^N)
    void generateSubsets(vector<int>& nums, vector<int>& partial,
                    int i, set<vector<int> >& s, vector<vector<int> >& result) {
        if(i == nums.size()) {
            if(s.find(partial) == s.end()) {
                s.emplace(partial);
                result.emplace_back(partial);
                return;
            }
        }    
        
        // for the current index, we can either include it or choose not to
        partial.emplace_back(nums[i]);
        generateSubsets(nums, partial, i+1, s, result);
        partial.pop_back();
        generateSubsets(nums, partial, i+1, s, result);
    }
    
    // driver function for backtracking
    vector<vector<int>> subsetsBacktracking(vector<int>& nums) {
        // set for unique subsets
        set<vector<int> > s;
        vector<int> partial;
        vector<vector<int> > result;
        generateSubsets(nums, partial, 0, s, result);
        
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
        //return subsetsBacktracking(nums);
        return generateSubsetsIterative(nums);
    }
};
