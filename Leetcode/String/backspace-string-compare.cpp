/*
    https://leetcode.com/problems/backspace-string-compare/
    TC: O(m+n), SC: O(m + n)
*/
class Solution {
public:
    string useBackspace(string& s) {
        int i = s.size() - 1;
        string result;
        int backspace = 0;
        
        while(i >= 0) {
            if(s[i] == '#')
                ++backspace;
            else {
                // when it is valid character 
                if(backspace == 0)
                    result += s[i];
                // when we have backspace, skip the char
                else
                    --backspace;
            }    
            --i;
        }
        return result;
    }
    
    bool backspaceCompare(string S, string T) {
        // create a string using backspace
        string s = useBackspace(S);
        string t = useBackspace(T);
        
        return s == t;
    }
};
