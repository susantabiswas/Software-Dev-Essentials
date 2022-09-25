/*
    https://leetcode.com/problems/find-all-good-indices/
    
    Idea is to find the max length of non-increasing and non-decreasing subarray lengths
    for each of the elements. Then we just have to check if the indices in the good
    index range satisfy the condition, if they do add them to good list.
    
    TC: O(N)
    SC: O(N)
*/
class Solution {
public:
    vector<int> goodIndices(vector<int>& nums, int k) {
        int n = nums.size();
        // tracks the length of non-increasing and non-decreasing subarray lengths
        // just before / after ith element
        vector<int> non_incr(n, 0), non_decr(n, 0);
        int len = 0;
        
        // Find the max length of non-increasing subarray just before ith element
        for(int i = 1; i < n; i++) 
            non_incr[i] = i > 1 && nums[i-2] >= nums[i-1] ? non_incr[i-1] + 1 : 1;
        
        // Find the max length of non-decreasing subarray just after ith element
        for(int i = n-2; i >= 0; i--) 
            non_decr[i] = i < n-2 && nums[i+1] <= nums[i+2] ? non_decr[i+1] + 1 : 1;
        
        vector<int> good_idx;
        // Now good idx is in [k, n-k-1] range, check if the conditions are met for each of 
        // the indices
        for(int i = k; i < n - k; i++)
            if(min(non_incr[i], non_decr[i]) >= k)
                good_idx.emplace_back(i);
        
        return good_idx;
    }
};
