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
            // if nexxt element is smaller, then go to
            // left side but keep the mid as right as that might 
            // be the answer
            if(nums[mid] > nums[mid + 1])
                right = mid;
            // if th next element is greater, that means go in right direction in hope of finding a biger element, since mid is smaller than the next so we can update left as the next element
            else
                left = mid + 1;
        }
        return left;
    }
    
    int findPeakElement(vector<int>& nums) {
        return findPeakBinarySearch(nums);
    }
};
