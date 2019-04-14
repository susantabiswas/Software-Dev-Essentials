/*
    978. Longest Turbulent Subarray
    https://leetcode.com/problems/longest-turbulent-subarray/submissions/
    
    Find the longest sequence of increasing-decreasing or vice-versa numbers
    
    We expand the window till the current element doesnt violate the constraint, now
    since the constraint is broken because of current index, so move the window start to 
    current index for trying next window.
    We try two things: assuming that odd positions > even positions and vice-versa and
    find the max length.
    
*/

class Solution {
public:
    int maxTurbulenceSize(vector<int>& arr) {
        if(arr.empty())
            return 0;
        
        int max_len = 1;
        int i = 0, j = 0;
        
        // case when odd position is greater than even
        while(i < arr.size() - 1) {
            ++i;
            // if current element violtates the constraint, then
            // current index will be the start for next window
            if((i % 2 == 0 && arr[i] >= arr[i-1]) ||
               (i % 2 != 0 && arr[i] <= arr[i-1]))
                j = i;
                
            max_len = max(max_len, i - j + 1);
        }
        
        // case when even position is greater than odd position
        i = 0, j = 0;
        while(i < arr.size() - 1) {
            ++i;
            // if current element violtates the constraint, then
            // current index will be the start for next window
            if((i % 2 == 0 && arr[i] <= arr[i-1]) ||
               (i % 2 != 0 && arr[i] >= arr[i-1]))
                j = i;
                
            max_len = max(max_len, i - j + 1);
        }
        
        return max_len;
    }
};
