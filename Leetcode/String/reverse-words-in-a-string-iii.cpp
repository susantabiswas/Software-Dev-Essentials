/*
    https://leetcode.com/problems/reverse-words-in-a-string-iii/
    
    TC: O(n)
    SC: O(1)
*/
class Solution {
public:
    string reverseWords(string s) {
        int end = 0;
        
        while(end < s.size()) {
            int start = end;
            
            while(end < s.size() && s[end] != ' ')
                ++end;
            
            reverse(s.begin() + start, s.begin() + end);
            ++end;
        }
        return s;
    }
};
