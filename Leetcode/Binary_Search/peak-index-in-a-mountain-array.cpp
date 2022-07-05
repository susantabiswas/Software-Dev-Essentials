/*
    https://leetcode.com/problems/peak-index-in-a-mountain-array/
    
    Idea is to skip all the elements lesser than peak and making sure that one 
    of the limits always points to the greater element around mid.
    
    Here we use right index to make sure that it always points to the greatest.
    
*/
class Solution {
public:
    // TC: O(logN)
    int peakIndexInMountainArray(vector<int>& arr) {
        int left = 0, right = arr.size()-1;
        
        while(left + 1 <= right) {
            int mid = left + (right - left) / 2;
            // If we are on left side of peak
            if(arr[mid] < arr[mid+1])
                left = mid + 1;
            // We are on right side of peak
            else
                right = mid;
        }
        
        return right;
    }
};
