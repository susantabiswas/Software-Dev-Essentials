/*
    https://leetcode.com/problems/subsets-ii/

    RECURSIVE SOLUTION
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


////////////////////// ITERATIVE SOLUTION
/*
    https://leetcode.com/problems/subsets-ii/
    
    TC: O(n * 2^n + nlogn) ~ O(n * 2^n)
    SC: O(n)
    
    Iterative Solution:
    When dealing with duplicates, important thing is to ensure that if we have
    formed subsets ending with 'x', then if we again add 'x' to all the previous subsets
    => there will be duplicate subsets.
    So we need to avoid using the same number with same subsets.
    e.g: (1,2,2)
    subset: (), (1)
    - {num will be appended with subsets from 0-1 i.e (), (1)} nums[1]: 2 => (), (1), | (2), (1,2)
    
    - {if this same num is again appended with subsets 0-1 then we will again get the previous subsets,
    instead we should only append current with the new subsets formed with previous number i.e from subsets[2:3]}
    nums[2]: 2 => (), (1), (2), (1,2) | (2,2), (1,2,2)
                           ^
                           |start from here
*/
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> subsets;
        
        if(nums.empty())
            return subsets;
        
        sort(nums.begin(), nums.end());
        
        // initial empty set
        subsets.push_back({});
        
        int end_idx = 0;
        
        for(int i = 0; i < nums.size(); i++) {
            // if the current element is the same as previous, then we only need to
            // add to subsets which had contribution from the previous element and not the
            // subsets that were used to form the subsets with previous element as doing so
            // will yield the same subsets again
            int start_idx = (i >= 1 && nums[i] == nums[i-1]) ? end_idx + 1 : 0;
            end_idx = subsets.size() - 1;
            
            for(int j = start_idx; j <= end_idx; j++) {
                subsets.push_back(subsets[j]);
                subsets.back().push_back(nums[i]);
            }
        }
        return subsets;
    }
};
