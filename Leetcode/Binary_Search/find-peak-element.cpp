/*
    https://leetcode.com/problems/find-peak-element/
    
    Since the objective is not to find the global peak
    element but rather a local peak element, so
    using binary search we can find a local element which is 
    greater than its neighbours
    The Idea is to go towards the direction of larger element
    
*/
class Solution {
public:
    // Finds the peak element using binary search
    // TC: O(logN)
    int findPeakBinarySearch(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        
        while(left < right) {
            int mid = left + (right - left) / 2;
            
            // if the next element is greater, that means go in right direction
            // in hope of finding a bigger element, since mid is smaller than the next so we can update left as the next element
            if(nums[mid] < nums[mid + 1])
                left = mid + 1;
            // the next element is not strictly greater so ignore the elements on right and update the
            // right index as the potential peak element index
            else
                right = mid;
        }
        return left;
    }
    
    int findPeakElement(vector<int>& nums) {
        return findPeakBinarySearch(nums);
    }
};

////////////////////////////////////// Template : left + 1 < right
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int low = 0, high = arr.size() - 1;
        
        while(low + 1 < high) {
            int mid = low + (high - low) / 2;
            
            if(arr[mid] > arr[mid-1] && arr[mid] > arr[mid+1])
                return mid;
            else if(arr[mid] > arr[mid-1])
                low = mid;
            else
                high = mid;
        }
        
        return -1;
    }
};
