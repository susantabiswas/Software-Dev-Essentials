/*
    https://leetcode.com/problems/remove-outermost-parentheses/
    
    Two Pointers Solution:
    Since the string is a valid bracket string, we know for a fact that there will
    always be '(' to start a group of 0 or more nested brackets. So we set one pointer
    at the beginning of such a group and then we traverse forward till we find its 
    closing bracket. We use the depth information to keep track of balancing of
    inner brackets. '(' will have depth = 1 at the start and its closing bracket will have 0.
    In general, for any intermediate '(' with depth = x, its closing will have x-1 depth.
    
    TC: O(N)
    SC: O(1)
*/

class Solution {
public:
    string removeOuterParentheses(string S) {
        string result;
        int i = 0, j = 0;
        
        for(; i < S.size(); ) {
            int depth = 0;
            // opening start of a balanced group
            if(S[i] == '(') {
                ++depth;
                j = i + 1;
                // traverse till the closing is found for the current balanced group
                for(; j < S.size() && depth > 0; j++) {
                    depth = depth + (S[j] == '(' ? 1 : -1);
                }
                // end of a balanced group
                // if there was atleast one more balanced pair
                if(j - (i + 1) > 1) 
                    result += S.substr(i + 1, j - (i + 1) - 1);
            }
            i = j;
        }
        return result;
    }
};
