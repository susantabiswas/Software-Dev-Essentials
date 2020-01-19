/*
        https://leetcode.com/problems/string-to-integer-atoi/
        
        TC: O(n), SC: O(1)
*/
class Solution {
public:
    int myAtoi(string str) {
        if(str.empty())
            return 0;
        
        // remove whitespaces
        int i = 0; 
        while(i < str.size() && str[i] == ' ')
            ++i;
        
        // after whitespace removal if the first character is anything 
        // other than +,-,[0-9]
        char first_char = str[i++];
        bool negative = false;
        int result = 0;
        
        if(first_char != '-' && first_char != '+' &&
           ((first_char - '0') < 0  || (first_char - '0') > 9) )
            return 0;
        
        // set sign
        negative = first_char == '-' ? true : false;
        // if first char is a digit instead of sign
        result = ((first_char - '0') >= 0  && (first_char - '0') <= 9) ? (first_char - '0') : 0;
        
        // construct the remaining number using chars
        // if the final number is negative then each time we add negative digits
        // this makes it possible to save it in 32-bit int otherwise overflow occurs
        while(i < str.size() && isdigit(str[i])) {
            int curr_digit = str[i] - '0';
            
            // check if the number goees beyond negative LIMIT
            if(negative && (result < (INT_MIN + curr_digit) / 10))
                return INT_MIN;
            // check if the number goees beyond positive LIMIT
            else if(!negative && (result > (INT_MAX - curr_digit)/10))
                return INT_MAX;
            
            // make the current digit negative in case of negative number is final result
            if(negative)
                curr_digit *= -1;
            result = result*10 + curr_digit;
            ++i;
        }
        return result;
    }
};
