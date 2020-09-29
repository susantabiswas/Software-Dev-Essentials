/*
    https://leetcode.com/problems/subarray-product-less-than-k/
    
    We can use sliding window to find out all the valid windows that 
    have product < K. We compute the product in rolling manner for 
    each of the windows, we stop window expansion as soon as the window 
    product >= k, reduce the window size from front till it contains
    a valid product. 
    For a window of size n, there are n*(n-1)/2 subarrays.
    Since each window is compute in sequential manner
    so we can use each time add the length of the subarray to the final ans.
    
    TC: O(N)
    SC: O(1)
*/

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int K) {
        int subarrays = 0;
        long long prod = 1;
        
        int i = 0, j = 0;
        
        while(i < nums.size()) {
            // expand the window
            prod *= nums[i++];
            
            // if the product exceeded the limit
            while(prod >= K && j < i) {
                prod = prod / nums[j++];    
            }
            // window [j:i] is valid, and there are i - j subarrays
            subarrays += i - j;
        }
        return subarrays;
    }
};
