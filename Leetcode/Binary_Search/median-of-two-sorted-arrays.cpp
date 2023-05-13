/*
    https://leetcode.com/problems/median-of-two-sorted-arrays/
    
    TC: O(min(logm, logn))
    SC: O(1)
    
    We want to find the median in the final merged sorted array. Since we have two arrays,
    we can think of this as finding positions in both the arrays such that left sides of both
    the arrays contribute the elements on left of median and right sides contribute to the elements
    on right side of median.
    
    nums1: [         |     ]
    nums2: [      |                ]
    | = partition position
    The ideal partition position is such that total elements on left side = total elements on right sum
    The partition position in both are arrays are such that elements on left will all go to the left side in the
    final merged array.
    The condition to check if the partition is reached:
    nums1: [0: partition1-1], [partition1: M-1]
    nums2: [0: partition2-1], [partition2: N-1]
    
    Ideal partition will satisfy the following:
    nums1[partition1 - 1] <= nums2[partition2]
    nums2[partition2 - 1] <= nums1[partition2]
    
    Boundary element(s) near median: 
    When total is even:
        max(maxLeft1, maxLeft2)
        min(minRight1, minRight2)
    When total is odd
        max(maxLeft1, maxLeft2)
    
    We use the smaller array to find the partition1.
    Since we know that left side should have (m + n) / 2 elements, so we can do
    partition2 = (m + n) / 2 - partition1 
*/
class Solution {
public:
    double binarySearchSol(vector<int>& nums1, vector<int>& nums2) {
        // Ensure that array 1 is smaller in length
        if(nums2.size() < nums1.size())
            return binarySearchSol(nums2, nums1);
        
        // Left and right boundaries for nums 1, this is used for finding 
        // the partition position using binary search
        int low = 0, high = nums1.size();
        
        // Look for the ideal partition position using nums1
        while(low <= high) {
            // Length of left side of partition made in nums1
            int partition1 = low + (high - low) / 2;
            // Length of left side of partition made in nums2. We want to ensure 
            // that combined number of elements on left side of both nums1 and nums2 is
            // equal to right side
            // (nums1.size() + nums2.size() + 1) / 2 = No. of elements that will be there on left
            // side in the final sorted array. If total elements is odd then left side will have 1 extra element
            int partition2 = (nums1.size() + nums2.size() + 1) / 2 - partition1;
            
            // nums1 will be partitioned in two parts: [0: partition1-1], [partition1: M-1]
            // Since we want to ensure equal number of elements on both sides in final array,
            // If nums1's left side has more elements then nums2's left will have less elements to
            // ensure that equal number of elements are there on both sides.
            
            // Left side might have no elements, so we set it to -INF, this will make sure that
            // max of left side of nums2 will be picked up
            // Similarly if right side has no elements, then we set the min as INF so that the other right
            // side's min will be picked up
            int max_left1 = partition1 == 0 ? INT_MIN : nums1[partition1 - 1];
            int min_right1 = partition1 == nums1.size() ? INT_MAX : nums1[partition1];
            
            // nums2: [0: partition2-1], [partition2: N-1]
            int max_left2 = partition2 == 0 ? INT_MIN : nums2[partition2 - 1];
            int min_right2 = partition2 == nums2.size() ? INT_MAX : nums2[partition2];
            
            // Ideal partition found
            if(max_left1 <= min_right2 && max_left2 <= min_right1) {
                // If the merged array length is even
                if((nums1.size() + nums2.size()) % 2 == 0)
                    return (double)(max(max_left1, max_left2) + 
                                    min(min_right1, min_right2)) / 2;
                // If merged array length is odd
                else
                    return max(max_left1, max_left2);
            }
            // Since max of left side is greater than min of right side, that means
            // we should move towards left to find the partition position so that max (left) is smaller than min(right)
            else if(max_left1 > min_right2)
                high = partition1 - 1;
            // max_left2 > min_right2, that means we need to move partition2 towards left =>partition1 needs to move right
            else 
                low = partition1 + 1;
        }
        return -1;
    }
    
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        return binarySearchSol(nums1, nums2);
    }
};