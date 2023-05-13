/*
    https://leetcode.com/problems/removing-stars-from-a-string/
    
    TC: O(n)
    SC: O(1)
    
    Idea is to use two pointers for finding the final string after applying
    the operations. The write ptr tracks the position where a char will be written.
    Whenever we get a *, we take a step back for the write ptr, so the next valid char
    will be written at the position before * char.
*/
class Solution {
public:
    string removeStars(string s) {
        // Position where the char will be written
        int write = 0;
        
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '*')
                --write;
            else
                s[write++] = s[i];
        }
        
        return s.substr(0, write);
    }
};
