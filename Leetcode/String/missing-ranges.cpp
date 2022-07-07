/*
    https://leetcode.com/problems/missing-ranges/
    
    TC: O(N)
    SC: O(1)
    
    Just follow what is asked. Handle these 3 cases:
    1. Lower starts before the 1st element of nums
    2. Upper ends after the last element of nums
    3. Check if the range of missing elements is 1, then do "x" otherwise "x->y"
*/
class Solution {
public:
    // Builds the missing range according to the rules
    string missingRange(int start, int end) {
        string missing_range = (start == end) ? to_string(start) 
                                    : to_string(start) + "->" + to_string(end);
        return missing_range;
    }
    
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<string> range;
        
        // Edge case: Nums is empty
        if(nums.empty()) 
            return { missingRange(lower, upper) };
       
        // Missing [lower : nums[0] - 1]
        if(lower < nums.front()) {
            range.emplace_back(missingRange(lower, nums.front() - 1));
        }
        
        for(int i = 1; i < nums.size() && nums[i] <= upper; i++) {
            // missing number between last and current, check it's part of [lower:upper]
            if(nums[i] - nums[i-1] != 1) {
                int start = nums[i-1] + 1, end = nums[i] - 1;
                if(start < lower)
                    start = lower;
                
                range.emplace_back(missingRange(start, end));
            }
        }
        // Missing [nums[N-1] + 1: upper]
        if(upper > nums.back()) {
            range.emplace_back(missingRange(nums.back() + 1, upper));
        }
        
        return range;
    }
};
