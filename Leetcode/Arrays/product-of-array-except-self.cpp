/*
  https://leetcode.com/problems/product-of-array-except-self/
*/
class Solution {
public:
    // TC: O(N), SC: O(1)
    vector<int> productWithSpace(vector<int>& nums) {
        const int N = nums.size();
        vector<int> product(N, 1);
        
        // save the product of all numbers on left
        for(int i = 1; i < N; i++)
            product[i] = product[i-1] * nums[i-1];
        // update the saved multiplications of all left 
        // numbers with the right numbers
        int right_prod = 1;
        for(int i = N - 1; i >= 0; i--) {
            product[i] = product[i] * right_prod;
            right_prod *= nums[i];
        }
        return product;
    }
    
    vector<int> productExceptSelf(vector<int>& nums) {
        return productWithSpace(nums);
    }
};
