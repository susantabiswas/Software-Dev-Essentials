/*
    https://leetcode.com/problems/smallest-even-multiple/
    
    TC: O(log(max(2, n)))
    
    We basically need to find the LCM of 2 and n.
    LCM(a, b) = a * b / GCD(a, b)
*/
class Solution {
public:
    int smallestEvenMultiple(int n) {
        return (2 * n) / (__gcd(2, n));
    }
};
