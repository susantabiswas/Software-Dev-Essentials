/*
    Instead of sorting the combined array, we make use of the sorted nature 
    of the arrays. We find the sorted element till total_elements/2.
    Also keep track of previous element in sorted order in case there are even number 
    of elements.
    TC: O(n + m)
    
    https://leetcode.com/problems/median-of-two-sorted-arrays/submissions/
*/

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // when one is empty and other has 1 element
        if((nums1.empty() && nums2.size() == 1) || 
           nums2.empty() && nums1.size() == 1)
            return nums1.empty() ? nums2.front() : nums1.front();
            
        int i = 0, j = 0;
        int median_idx = (nums1.size() + nums2.size()) / 2;
        float median_val = 0;
        float prev = 0;
        bool odd = (nums1.size() + nums2.size()) % 2 == 0 ? false : true;
            
        for(int k = 0; k <= median_idx; k++) {
            prev = median_val;
            if(i < nums1.size() && j < nums2.size())
                median_val = nums1[i] < nums2[j] ? nums1[i++] : nums2[j++];
            else {
               median_val = i < nums1.size() ? nums1[i++] : nums2[j++];
            }
        }
        
        return odd ? median_val : (prev + median_val) / 2;
    }
};
