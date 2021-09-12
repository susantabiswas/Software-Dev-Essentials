/*
    https://leetcode.com/problems/basic-calculator/
    
    The idea is to represent the expression as sum of numbers.
    Eg: 1 + (3 - 7) - 9 => 1 + (3 + (-7)) + (-9)
    
    Since we only have + or -, so they have same priority and should be 
    priortised fromleft to right, so we evaluate the expression and keep track
    of it. Once we encounter a (, we save the result of expression found so far and the
    sign just before this (. Then reset the expression value and start evaluation in a similar
    fashion untill we find ), once it's found we do:
        result_before_expression + (sign_before_opening_brace * result_inside_the_parenthesis )
    Continue doing this till the expression ends.
    
    TC: O(N)
    SC: O(N)
*/

class Solution {
public:
    int calculate(string s) {
        // Keeps track of net result of an expression for a given nested scope
        int result = 0;
        // Sign for the current operand value
        int sign = 1;
        // Used to save the expression result and the sign of a new nested ()
        // E.g: 2 +  (3 - 9) => stack: 2, 1 (+1 for +ve and -1 for negative) will be saved 
        stack<int> result_so_far;
        
        for(int i = 0; i < s.size(); i++) {
            // if a number is encountered
            if(isdigit(s[i])) {
                // If it's a multi digit number
                int num = 0;
                while(i < s.size() && isdigit(s[i])) {
                    num = num * 10 + (s[i] - '0');
                    ++i;
                }
                // Add the number to the result obtained so far
                result += sign * num;
            }
            // A nested section starts here, so save the result obtained so far along
            // with the sign just outside the brace
            if(s[i] == '(') {
                result_so_far.push(result);
                result_so_far.push(sign);
                // Reset the sign and result for the new nested section
                result = 0;
                sign = 1;
            }
            // Nested section ends here, add the result of nested section with the result
            // of outer enclosure
            if(s[i] == ')') {
                int outer_sign = result_so_far.top(); 
                result_so_far.pop();
                int prev_result = result_so_far.top();
                result_so_far.pop();
                result = outer_sign * result + prev_result;
                // reset the sign
                sign = 1;
            }
            if(s[i] == '+' || s[i] == '-')
                sign = s[i] == '+' ? 1 : -1;
        }
        return result;
    }
};
