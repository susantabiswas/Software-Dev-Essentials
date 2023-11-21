/*
    https://leetcode.com/problems/valid-parenthesis-string/
    
    SOLUTION 1: 
    TC: O(n)
    SC: O(1)
    
    Idea is that for an opening brace (, we can balance with ) and * that appear after it
    Conversly, ) can be balanced with ( and *
    
    So the idea is to do a left to right sweep and cheeck if we encounter at any position a situation
    where the closing brace cannot be balanced with an opening brace or star.
    
    Similarly do from right to left and check if any time opening brace cannot be balanced with closing brace or star

    SOLUTION 2
    TC: O(N), SC: O(N)
    
    The idea is that ')' can be balanced by '(' or '*' whic has occurred before it 
    and '(' can be balanced only by ')' or '*' which has occurred after it. So we keep track of index of 
    '*' and '(' we encounter and using the above info check if a string is valid.
    
    We push '(' or '*' as their index in the stack.
    If we get ')' check if there is any of '(' or '*' before
    After traversal if we are left with '(' in the stack, check if there are '*' after it to balance it.
*/
class Solution {
public:
    // SOLUTION 1
    bool checkValidString1(string s) {
        int open = 0, close = 0, star = 0;
        
        // scan from left to right
        // Here we are trying to check if all the right braces can be 
        // balanced using left and stars before it
        for(auto ch: s) {
            if(ch == '(')
                ++open;
            else if (ch == '*')
                ++star;
            else
                ++close;
            
            if(close > open + star)
                return false;
        }
        
        
        open = 0, close = 0, star = 0;
        // scan from left to right, here we are trying to check if all the
        // left braces can be balanced with right and star braces that appeared after it
        for(int i = s.size() - 1; i >= 0; i--) {
            auto ch = s[i];
            if(ch == '(')
                ++open;
            else if (ch == '*')
                ++star;
            else
                ++close;
            
            if(open > close + star)
                return false;
        }
        
        return true;
    }
    
    // SOLUTION 2
    bool checkValidString(string s) {
        stack<int> left, star;
        
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '(')
                left.push(i);
            else if(s[i] == '*')
                star.push(i);
            else { // right brace
                
                if(left.empty() and star.empty())
                    return false;
                
                // for now just balance with the left brace
                if(!left.empty())
                    left.pop();
                else
                    star.pop();
            }
        }

        // keep balancing the left braces
        while(!left.empty() && !star.empty() && left.top() < star.top())
            left.pop(), star.pop();
        
        return left.empty();
    }
};
