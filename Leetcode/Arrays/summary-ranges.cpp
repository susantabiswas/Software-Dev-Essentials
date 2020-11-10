/*
    https://leetcode.com/problems/summary-ranges/submissions/
    
    TC: O(N)
    SC: O(1)
*/

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        // start: start of window, end: next index of window
        // [start, end)
        int start = 0, end = 1;
        vector<string> result;
        
        while(end <= nums.size()) {
            // find the window of consecutive numbers
            while(end < nums.size() && 
                  (long)nums[end] - nums[end-1] == 1)
                ++end;
            // add the interval
            if(nums[start] != nums[end-1])
                result.emplace_back(to_string(nums[start]) + "->" + to_string(nums[end-1]));
            // single element window
            else
                result.emplace_back(to_string(nums[start]));
            
            start = end;
            ++end;
        }
        
        return result;
    }
};
