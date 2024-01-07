/*
    https://leetcode.com/problems/subsets/
    
    Solution that works with duplicates as well.
	Note: Elements of a subset have their order maintained. Eg [1,2,3] => [3,2] is not possible
	
	Idea: The core idea is subsets can be formed starting with a smaller null set and slowly
	adding one element at a time to all existing subsets.
	The reason why this works is because we are essentially adding the current element to all the 
	subsets of varying lengths formed so far without this element.
	
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
    // Way 1: Using backtracking
    // TC: O(N * 2^N), SC:O(N), Worst case we go till length of array depth wise
    void generateSubsets1(vector<int>& nums, vector<int>& partial,
                    int i, vector<vector<int> >& result) {
        if(i == nums.size()) {
            result.emplace_back(partial);
            return;
        }    
        
        // for the current index, we can either include it or choose not to
        partial.emplace_back(nums[i]);
        generateSubsets1(nums, partial, i+1, result);
        partial.pop_back();
        generateSubsets1(nums, partial, i+1, result);
    }

	// Way 2: Backtracking, same complexity as previous
	// This mimics the iterative solution, here we add elements to the subset generate so far. 
    void sol2(int idx, vector<int>& subset, vector<int>& nums, vector<vector<int>>& result) {
        result.push_back(subset);
        
        for(int i = idx; i < nums.size(); i++) {
            subset.push_back(nums[i]);
            sol2(i+1, subset, nums, result);
            subset.pop_back();
    }
	
    // driver function for backtracking
    vector<vector<int>> subsetsBacktracking(vector<int>& nums) {
        vector<int> partial;
        vector<vector<int> > result;
		// way 1
        generateSubsets1(nums, partial, 0, result);

		// way2
		// sol2(0, partial, nums, result);
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
