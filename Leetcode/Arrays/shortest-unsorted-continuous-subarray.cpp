/*
    https://leetcode.com/problems/shortest-unsorted-continuous-subarray/
    TC: O(N), SC: O(1)
    
    Idea is to find an initial unsorted region and track the min and max elements in that
    region. Then look for first element that is bigger than the tracked smallest and last 
    element which is smaller than the tracked biggest.
*/
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int first = -1, second = -1;
        int min_len = 0;
        int range_min = INT_MAX, range_max = INT_MIN;

        for(int i = 0; i < nums.size() - 1; i++) {
            // find the term which doesnt follow the order
            if(nums[i] > nums[i+1]) {
                // if this is the first index that doesnt follow the order
                if(first == -1)
                    first = i;
                // update the last term not following the order
                second = i+1;
                range_min = min(range_min, nums[i+1]);
                range_max = max(range_max, nums[i]);
            }
        }
        // now we know the minimum range that needs to sorted,
        // we check if there is an element > min on left and element < max
        // on right

        // we check for the first element which is bigger as
        // all the numbers after that should be sorted
        for(int i = 0; i < first; i++) 
            if(nums[i] > range_min) {
                first = i;
                break;
            }

        // we check for the last element which is smaller as all the numbers
        // before it should be sorted
        for(int i = nums.size() - 1; i > second; i--) 
            if(nums[i] < range_max) {
                second = i;
                break;
            }
        
        if(first != -1)
            min_len = second - first + 1;
        return min_len;
    }
};
