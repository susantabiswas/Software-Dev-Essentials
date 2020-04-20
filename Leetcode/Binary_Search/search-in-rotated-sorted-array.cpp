/*
    https://leetcode.com/problems/search-in-rotated-sorted-array/
    TC: O(logN)
    
    Idea is to find the position where the first element of rotated subarray is.
    Then do binary search on whichever side the target lies.
*/
class Solution {
public:
    // binary search
    // TC: O(logN)
    int bSearch(vector<int>& nums, int left, int right, int target) {
        while(left <= right) {
            int mid = left + (right - left) / 2;
            
            if(nums[mid] == target)
                return mid;
            else if(nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1;
    }
    
    
    // TC: O(logN), SC: O(1)
    int search(vector<int>& nums, int target) {
        if(nums.empty())
            return -1;
        
        // search for the pivot index, then from there search in the 
        // left and right subarrays
        int left = 0, right = nums.size()-1;
        int pivot = nums.size() - 1;
        
        while(left <= right) {
            int mid = left + (right - left) / 2;
            
            // check if pivot
            if(mid-1 >= 0 && nums[mid-1] > nums[mid]) {
                pivot = mid;
                break;
            }
            if(nums[mid] > nums[right])
                left = mid + 1;
            else
                right = mid - 1;
        }
       
        // based on pivot value, then do binary search on whichever
        // side is applicable
        // [0...pivot...M]
        if(nums[0] <= target && pivot-1 >= 0 && target <= nums[pivot-1])
            return bSearch(nums, 0, pivot, target);
        else
            return bSearch(nums, pivot, nums.size()-1, target);
    }
};
