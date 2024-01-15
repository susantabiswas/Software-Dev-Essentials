/*
    https://leetcode.com/problems/powx-n/
    TC: O(log2n)
*/
class Solution {
public:
    double myPow(double x, int n) {
        // base case
        // +ve power
        if(n == 0 || n == 1)
            return n == 0 ? 1 : x;
        // -ve power
        if(n == -1)
            return 1 / x;
        
        double power = myPow(x, n/2);
        // if power n is even
        if(n % 2 == 0)
            return power * power;
        // odd power
        else {
            return power * power * (n < 0 ? (1 / x) : x);
        }
    }
};


// Way 2
class Solution {
public:
    double myPow(double x, int n) {
        // base cases
        if(n == 0)
            return 1;
        
        if(abs(n) == 1)
            return n == 1 ? x : 1/x;
        
        double val = myPow(x, n/2);
        
        if(n % 2) // odd power
            return n > 0 ? x * val * val : 1/x * val * val;
        
        return val * val;
    }
};
