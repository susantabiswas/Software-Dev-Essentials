/*
    https://leetcode.com/problems/minimum-deletions-to-make-array-divisible/
    
    Since we want to find the smallest number from nums that can divide all the nums in numsDivide, we need to
    find the smallest number also that divides all the numbers of numsDivide.
    So we use GCD (HCF) to find the smallest number that divides all of them.
    
    Then we use a set to save the numbers of nums with their frequency and iterate from smallest to largest.
    If a number doesnt divide the HCF, that will account towards delete operation, do till the first number that divides the HCF.
    
    TC: O(n * logm), n = no. of numbers, m = max number
    Finding the GCD of two numbers take log(max(a, b)) and we do this for all n numbers
    
    SC: O(unique_nums)
    
    
*/
class Solution {
public:
    int minOperations(vector<int>& nums, vector<int>& numsDivide) {
        // Find the HCF (GCD) of the numbers
        // This is the smallest number that can divide all the numbers
        int hcf = numsDivide[0];
        for(int i = 1; i < numsDivide.size(); i++)
            hcf = __gcd(hcf, numsDivide[i]);
        
        // Find the frequency count for each number
        // and store in height balanced tree 
        // <num, count>
        map<int, int> elements;
        for(auto num: nums)
            ++elements[num];
        
        // Iterate through the numbers in non-decreasing order
        // If a number can't divide the HCF, that needs to be deleted
        // If the number can divide the HCF, then that is the answer
        int ops = 0;
        for(auto [num, freq]: elements) {
            if(hcf % num == 0)
                return ops;
            ops += freq;
        }
        
        return -1;
    }
};
