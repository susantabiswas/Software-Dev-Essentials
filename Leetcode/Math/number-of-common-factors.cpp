/*
    https://leetcode.com/problems/number-of-common-factors/
    
    TC: O(log(max(a, b)) + O(min(a, b)))
    Worst case: When a == b or one can divide the other, there
    we iterate till that number.
    
    Idea is simple, we need to find the max common factor, then iterate from 1 till that
    and check all the numbers that can divide both a and b.
*/
class Solution {
public:
    int commonFactors(int a, int b) {
        // Find the max common factor
        int lcm = (a * b) / (__gcd(a, b));
        int common = 0;
        
        // Now starting from 1 to max common factor, check 
        // which numbers can divide both
        for(int num = 1; num <= lcm; num++)
            if(!(a % num) && !(b % num))
                ++common;
        return common;
    }
};
