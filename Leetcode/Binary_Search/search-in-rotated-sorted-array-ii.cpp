/*
    https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
    
    TC: O(n) in worst case all the elements are same, we will just be moving left and right by 1 step
        O(logn) in best case
    SC: O(1)
    
    This problem although looks very similar to search in rotated array 1, but there is a subtle and imp
    difference and that is presence of duplicates.
    
    When there are duplicates, then we can have a situation where mid, low and high all are same, in this situation we
    don't have clarity to decide on which side to go. Binary search can only be used when one side of array fulfills a condition
    that the other side cannot, but here both sides will fullfil the case: nums[mid] <= nums[high]
    
    To counter this, we can just check if we have encountered this scenario or not using this
    if(nums[low] == nums[mid] && nums[mid] == nums[high])
                ++low, --high;
                
    If currently we are not in above scenario then we just check on side of pivot we currently are:
    pivot: 1st smallest element
    [low......>=..pivot.<=..mid..<= high]
    
    if we are on the right side, then we check if:
        we are on right or left side of mid on this side of pivot 
    else if on right of pivot:
        again check if we are on left or right of mid on this side of pivot
*/
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1;
        
        while(low <= high) {
            int mid = low + (high - low) / 2;
            
            if(nums[mid] == target)
                return true;
            
            // duplicate case where mid, low and high all are same, skip them since we cant decide
            if(nums[low] == nums[mid] && nums[mid] == nums[high])
                ++low, --high;
            // Once we know that we are not dealing with duplicate scenario, we can decide
            // accurately on which side of pivot we are right now and update the window
            // accordingly
            
            // if we are on left of pivot
            // [low...<=.mid..<=..pivot..>=..high]
            else if(nums[mid] >= nums[low]) {
                if(target < nums[mid] && target >= nums[low])
                    high = mid - 1;
                else
                    low = mid + 1;
            }
            // if we are on right of pivot
            // [low......>=..pivot.<=..mid..<= high]
            else if(nums[mid] <= nums[low]) {
                if(target > nums[mid] && target <= nums[high])
                    low = mid + 1;
                else
                    high = mid - 1;
            }
        }
        
        return false;
    }
};
