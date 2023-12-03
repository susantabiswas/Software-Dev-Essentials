/*
    https://leetcode.com/problems/fibonacci-number/
    
    TC: O(n)
    SC: O(1)
    
    Keep track of last two terms in the sequence and use them to get the
    current ith term, then update the second and first previous terms.
*/
class Solution {
public:
    int fib(int n) {
        if(n <= 1)
            return n;
        
        int first = 0, second = 1, third = 0;
        
        for(int i = 2; i <= n; i++) {
            third = first + second;
            first = second;
            second = third;
        }
        return third;
    }
};
