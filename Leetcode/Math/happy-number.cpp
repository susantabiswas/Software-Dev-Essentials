/*
    https://leetcode.com/problems/happy-number/
    
    Incase of a happy number it reaches 1 and wont change to some other number and
    for unhappy numbers they repeat numbers after some time, forming a loop in a sense.
    So we can use toroise and hare algorithm for finding the loop.
    
    If the number where they meet is anything other than 1, it is not a happy number.
    
    TC:
    For sumSquare(n): It processes log10(n) digits ~ logn
                    Now it can produce a max number = 9^2 * log(n)
                    Where logn is no. of digits and if each digit is 9, then square of each will be 81
                    new_num = no. of digits * 81
                    
    Based on analysis on pen and paper, 999's next is 243. So for a 3 digit number max next is 243.
    For higher digits, 9999 is 324 etc. So when number gets higher the next actually starts falling.
    So this means for a higher number with many digits, it will fall to a number with smaller digits till
    it reaches 3 digit stage where the max is 243 as next state.
    After that it will be below 243.
    
    So for 3 digit number, it will take max 243 steps : O(243)
    for higher numbers, they will call sumSquare(n) few times till they get smaller and smaller.
    1st time: log(n), it will produce max 9^2 * log(n) ~ 81logn
    2nd time: log(81*logn), it will produce max 81 * (81 * logn)
    Without constants, logn + log(logn) + log(log(logn)) 
    
    Then it reaches under 243 stage
    Overall: O(243 + logn + loglogn + logloglogn)
    ~O(logn), since other terms are much smaller
    SC: O(1)
*/
class Solution {
public:
    int sumSquare(int n) {
        int sum = 0;
        while(n) {
            sum += (n % 10) * (n % 10);
            n /= 10;
        }
        return sum;
    }
    
    bool isHappy(int n) {
        int slow = n, fast = n;
        do {
            slow = sumSquare(slow);
            fast = sumSquare(sumSquare(fast));
        } while(slow != fast && slow != 1 && fast != 1);
        
        return slow == 1 || fast == 1;
    }
};
