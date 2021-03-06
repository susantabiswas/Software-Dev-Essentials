/*
    https://leetcode.com/problems/valid-parentheses/submissions/
    
    TC: O(N)
    SC: O(N)
*/
class Solution {
public:
    bool isValid(string str) {
        stack<char> s;
        for(const char &c: str) {
            // if the current bracket is right sided, check
            // if the last seen opening is of the same type
            // or if there is no left sym then also invalid
            if(c == ')' || c == '}' || c == ']') {
                if(s.empty())
                    return false;
                if((c == ')' && s.top() != '(') ||
                  (c == ']' && s.top() != '[') ||
                  (c == '}' && s.top() != '{'))
                    return false;
                // remove the matching opening bracket
                s.pop();
            }
            else
                s.emplace(c);
        }
        
        // there should be no remaining brackets if in case of a valid cmb
        return s.empty();
    }
};
