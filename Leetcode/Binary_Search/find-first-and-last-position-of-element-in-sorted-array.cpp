/*
    First binary search is used to find the target, once it is found,
    then the starting and ending indices are searched by doing binary search
    in left and right directions.
    
    TC: O(logn)
    
    https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/submissions/
*/

class Solution {
public:
    
    /*
        Finds either the first or last occurrence of a target number.
        It uses binary search and searches for the target, once the target is found,
        then based on the value of direction variable left, we decide either to 
        go left and find the first occurrence of target or go right and find 
        the last occurrence of target.
        TC: O(logn)
    */
    void searchBound(vector<int>& arr, int& target, int& bound_idx,
                    bool left, int start, int end) {
        if(start > end)
            return;
        
        int middle_idx = start + (end - start) / 2;
        
        if(arr[middle_idx] == target) {
            // since the target is found, update the 
            // bound index 
            bound_idx = middle_idx;
            // based on whether we want to find the last or
            // first occurrence we go either left or right
            if(left)
                searchBound(arr, target, bound_idx, left, start, middle_idx - 1);
            else
                searchBound(arr, target, bound_idx, left, middle_idx + 1, end);
        }
        else if(arr[middle_idx] < target) {
            searchBound(arr, target, bound_idx, left, middle_idx + 1, end);
        }
        else {
            searchBound(arr, target, bound_idx, left, start, middle_idx - 1);
        }
    }
    
    /*
        Finds the upper and lower indices for the target number
        TC: O(logn)
    */
    void findRange(vector<int>& arr, int& target, vector<int>& result, 
                  int start, int end) {
        if(start > end)
            return;
        // find the mid point
        int middle_idx = start + (end - start) / 2;
        
        // when target is found, search for the lower and 
        // upper bound indices for the target
        if(arr[middle_idx] == target) {
            // search in left and right sides for starting and 
            // ending indices of target
            int lower = middle_idx, upper = middle_idx;
            searchBound(arr, target, lower, true, start, middle_idx - 1);
            searchBound(arr, target, upper, false, middle_idx + 1, end);
            
            // update the found indices 
            result.front() = lower;
            result.back() = upper;
        }
        else if(arr[middle_idx] < target) {
            findRange(arr, target, result, middle_idx + 1, end);
        }
        else {
            findRange(arr, target, result, start, middle_idx - 1);
        }
    }
    
    // driver function
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> result = {-1, -1};
        findRange(nums, target, result, 0, nums.size()-1);
        
        return result;
    }
};
