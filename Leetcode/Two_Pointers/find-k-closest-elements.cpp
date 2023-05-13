/*
    https://leetcode.com/problems/find-k-closest-elements/
    
    TC: O(logn + k)
    SC: O(1)
    
    Idea is to use binary search to find the position where the element should exist.
    Then from there we start looking for the k sized window that will have the closest 
    elements. Since the array is sorted, the k closest elements will be nearby to the
    position where x should exist.
    Each time we compare the left and right boundary elements to decide the one to move forward.
    
*/
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<int> closest;
        // Find the position where the element should exist using binary search
        auto it = lower_bound(arr.begin(), arr.end(), x);
        int idx = it - arr.begin();
        // In case the element should exist after the last element,
        // move the ptr to the last element
        idx = it == arr.end() ? --idx : idx;
        // Tracks the left and right bounds of k sized closest window
        // The valid interval will always be between [left + 1: right - 1]
        // since each closest element will move that side pointer by +1/-1
        int left = idx - 1, right = idx;
        
        // Since the array is sorted, k closest elements will be nearby contiguous
        // elements
        while(k--) {
            // Tracks the left and right border elements
            int left_num = INT_MAX, right_num = INT_MAX;
            
            // Only check the left if it is not out of bound
            if(left >= 0)
                left_num = abs(arr[left] - x);
            // Only check the right if it is not out of bound
            if(right < arr.size())
                right_num = abs(arr[right] - x);
            
            // For the same distance, the left side element is given priority
            // so even if dist is same, pick the left
            if(left_num <= right_num) 
                --left;
            else
                ++right;
        }
        
        for(int i = left + 1; i < right; i++)
            closest.emplace_back(arr[i]);
        return closest;
    }
};
