/*
    https://leetcode.com/problems/subsets-ii/
    
    TC: O(2^N)
    t(0) = 0
    t(1) = 1 (push 1 el to subset) + t(0)
    t(2) = 2 (push 2 elements, one at a time to subset) + t(1) + t(0)
    .....
    t(n-1) = n-1 + t(n-2) + t(n-3) +...+ t(1) + t(0)
    t(n) = n + t(n-1) + [t(n-2) + ...+ t(1) + t(0)]
         = n + t(n-1) + [t(n-2) + ...+ t(1) + t(0) + (n-1) - (n-1)
         = n + t(n-1) + [t(n-2) + ...+ t(1) + t(0) + (n-1)] - (n-1)  
         = n + t(n-1) + t(n-1) - (n-1) = 2t(n-1) + 1

    => t(n) = 2^n-1
    
    SC: O(n), max depth of recursive stack
    
    Idea is similar to subset problem, here we can add the subset at each instant, so that
    all possible subsets are captured.
*/
class Solution {
public:
    void subsets(int curr, vector<int>& nums, vector<int> subset,
                vector<vector<int>>& result) {
        // since we want to add all subsets, we add the subset we got so far to the result
        // before adding elements to it
        result.emplace_back(subset);
        
        if(curr == nums.size()) 
            return;
        
        // add each element with the current subset once
        for(int i = curr; i < nums.size(); i++) {
            if(i == curr || nums[i] != nums[i-1]) {
                subset.emplace_back(nums[i]);
                subsets(i+1, nums, subset, result);
                subset.pop_back();
            }
        }
    }
    
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        subsets(0, nums, vector<int>{}, result);
        return result;
    }
};
