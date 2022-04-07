/*
    152. Maximum Product Subarray
    https://leetcode.com/problems/maximum-product-subarray/
    
    For getting the max product, we need to consider a contiguous array of elements. 
    Now if odd number of neg numbers exists in between, then product becomes negative. 
    Also if there are even number of negative terms, then entire product becomes +ve.
    We use two vars: one tracks the max product till current point and other min product.
    Also whenever we get a negative term, we swap the two vars.
    Since multiplying by -ve number makes current max smallest and current min largest.
*/

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        const int N = nums.size();
        int curr_max = nums.front();
        int curr_min = nums.front();
        int max_prod = nums.front();
        
        for(int i=1; i < N; i++) {
            // if negative term is encountered, swap the two vars
            if(nums[i] < 0)
                swap(curr_max, curr_min);
            
            // update max and min values
            curr_max = max(nums[i], nums[i] * curr_max);
            curr_min = min(nums[i], nums[i] * curr_min);
            
            // update global max value
            max_prod = max(max_prod, curr_max);
        }
        
        return max_prod;
    }
};
