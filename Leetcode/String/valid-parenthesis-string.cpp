/*
    https://leetcode.com/problems/valid-parenthesis-string/submissions/
    
    TC: O(N), SC: O(N)
    
    The idea is that ')' can be balanced by '(' or '*' whic has occurred before it 
    and '(' can be balanced only by ')' or '*' which has occurred after it. So we keep track of index of 
    '*' and '(' we encounter and using the above info check if a string is valid.
    
    We push '(' or '*' as their index in stack.
    We if we get ')' check if there is any of '(' or '*' before
    After traversal if we are keft with '(' in stack, check if there are '*' after it to balance it.
*/
class Solution {
public:
    bool checkValidString(string str) {
        stack<int> s;
        stack<int> special_char;
        
        for(int i = 0; i < str.size(); i++) {
            char c = str[i];
            if(c == '(') {
                s.emplace(i);
            }
            else if(c == '*')
                special_char.emplace(i);
            // if ) is encountered, there should be * or ( in the stack
            // before 
            else if(c == ')') {
                if(!s.empty() ||
                  !special_char.empty()) {
                    if(!s.empty())
                        s.pop();
                    else
                        special_char.pop();
                }
                // no chars to balance ')' found
                else
                    return false;
            }
            // any other character is not valid
            else
                return false;
        }
        
        // start popping the remaining stack elements '('
        while(!s.empty()) {
            // for every '(' left, we need a * char, which occurs after that
            // which can behave as ')' to balance it
            if(special_char.empty())
                return false;
            int left_bracket_idx = s.top();
            s.pop();
            int special_char_idx = special_char.top();
            special_char.pop();
            // if there is no '*' after current brace to balance, str is not valid
            if(special_char_idx < left_bracket_idx)
                return false;
        }
        return true;
    }
};
