/*
    https://leetcode.com/problems/find-numbers-with-even-number-of-digits/
*/

class Solution {
public:
    // Solution 1
    int findNumbers(vector<int>& nums) {
        int even_digit_nums = 0;
        // starting limits
        const int TWO_DIGITS = 10, THREE_DIGITS = 100, FOUR_DIGITS = 1000,
                    FIVE_DIGITS = 10000, SIX_DIGITS = 100000;
        
        // even no. of digits are possible in [10:99], [1000:9999], [100000]
        for(const int& num: nums) {
            if((num >= TWO_DIGITS && num < THREE_DIGITS) ||
               (num >= FOUR_DIGITS && num < FIVE_DIGITS) ||
               num >= SIX_DIGITS)
                even_digit_nums += 1;
        }
        return even_digit_nums;
    }
    
    
    /*
    Solution 2
    int numDigits(int num) {
        int n_digits = 0;
        while(num) {
            n_digits += 1;
            num /= 10;
        } 
        return n_digits;
    }
    
    int findNumbers(vector<int>& nums) {
        int even_digit_nums = 0;
        for(const int& num: nums)
            if(numDigits(num) % 2 == 0)
                ++even_digit_nums;
        
        return even_digit_nums;
    }
    */
};
