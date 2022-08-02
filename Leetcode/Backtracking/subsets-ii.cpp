/*
    https://leetcode.com/problems/subsets-ii/
    
    TC: O(N * 2^N)
    There will be 2^N subsets. Power set of N numbers/bits is 2^N.

    Also each time we add subset to the result, this can get length of N
    
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
