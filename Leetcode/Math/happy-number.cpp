/*
    https://leetcode.com/problems/happy-number/submissions/
    
    Incase of a happy number it reaches 1 and wont change to some other number and
    for unhappy numbers they repeat numbers after some time, forming a loop in a sense.
    So we can use toroise and hare algorithm for finding the loop.
    
    If the number where they meet is anything other than 1, it is not a happy number.
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
