/*
    https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
    
    TC: O(logn)
    
    Two binary search solutions, each uses a different variant of binary search 
*/
class Solution {
public:
    // Uses the classic variant 
    int bSearch1(vector<int>& nums) {
        int low = 0, high = nums.size() - 1;
        int pivot = 0;
        
        while(low <= high) {
            int mid = low + (high - low) / 2;
            
            // check if the mid is the pivot element
            if(mid - 1 >= 0 && nums[mid-1] > nums[mid]) {
                pivot = mid;
                break;
            }
            // Since we have low <= high condition and if to check for the
            // pivot, we don't need to track the last closest answer and rather
            // can move past the mid with either +1/-1
            if(nums[mid] > nums[high])
                low = mid + 1;
            else
                high = mid - 1;
        }
        
        return nums[pivot];
    }
    
    // This uses variant that keeps atleast 2 elements
    int bSearch2(vector<int>& nums) {
        int low = 0, high = nums.size() - 1;
        int pivot = 0;
        
        while(low < high) {
            int mid = low + (high - low) / 2;
            
            // since we are looking for the smallest pivot (smallest in array),
            // we compare mid with the rightmost limit, if mid is smaller then move 
            // towards left to get to even smaller number.
            // We are in the smaller range 
            // [[Greater Elements], Pivot, [Smaller Elements]]
            if(nums[mid] < nums[high])
                high = mid;
            // mid is greater than right limit, means we are in the greater array,
            // so need to move right to get to smaller array
            // [[Greater Elements], Pivot, [Smaller Elements]]
            else
                low = mid + 1;
        }
        
        return nums[high];
        
    }
    
    int findMin(vector<int>& nums) {
        // return bSearch1(nums);
        return bSearch2(nums);
    }
};
