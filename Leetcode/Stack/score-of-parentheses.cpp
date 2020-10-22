/*
    https://leetcode.com/problems/score-of-parentheses/submissions/
    
    Since the scoring happens based on the nested braces, we need a way
    to know the level of nested braces. To indicate each nested level we
    use 0 when a '(' is encountered. Then everytime we get a ')', we find 
    the total score between the start of the '(' and current ')', 
    use the rule 2 * A and push the result back.
    
    Eg: ()()
    ( Stack: 0,
    ) Stack: 1,
    ( Stack: 1, 0
    ) Stack: 1, 1
    
    Final: 1 + 1 = 2
    
    TC: O(N)
    SC: O(N)
*/

class Solution {
public:
    int scoreOfParentheses(string s) {
        int total = 0;
        int curr_score = 0;
        
        stack<int> vals;
        
        for(char &c: s) {
            // opening bracket
            if(c == '(') { 
                vals.emplace(0);
            }
            else {
                int curr_val = 0;
                // find the total sum
                while(vals.top() != 0) {
                    curr_val += vals.top();
                    vals.pop(); 
                }
                // remove score for the opening brace of current )
                vals.pop();
                // assign score based on whether the current 
                // closing brace has enclosed brace 
                curr_val = curr_val == 0 ? 1 : 2 * curr_val;
                vals.emplace(curr_val);
            }
        }
        // final score is sum of all remaining brace scores
        while(!vals.empty()) {
            total += vals.top();
            vals.pop();
        }
        return total;
    }
};
