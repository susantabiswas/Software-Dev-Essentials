/*
    https://leetcode.com/problems/length-of-the-longest-alphabetical-continuous-substring/
    
    TC: O(N)
    SC: O(1)
    
    Idea is to simply expand the current window of consecutive chars until we no longer can.
    Then check if max length is reached or not. Then again repeat the process by making
    the next char as the start of window. 
*/
class Solution {
public:
    int longestContinuousSubstring(string s) {
        int start = 0, end = 0;
        int max_len = 0, n = s.size();
        
        while(end < n) {
            // While the window has consecutive chars, traverse further
            while(end + 1 < n && (s[end + 1] - s[end]) == 1) 
                ++end;
            // Either all chars have finished or the window can't be expanded
            max_len = max(max_len, end - start + 1);
            // Since next s[end+1] violates the consecutive chars criteria, we 
            // can directly make that the start of the window
            start = end + 1;
            end = end + 1;
        }
        return max_len;
    }
};
