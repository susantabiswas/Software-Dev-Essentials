/*
    https://leetcode.com/problems/reverse-only-letters/submissions/
    
    We use two pointers, one in begining and one at end.
    Skip all the characters other than letters and move the ptrs 
    till they reach a letter, then swap the letters and continue.
*/
class Solution {
public:
    string reverseOnlyLetters(string s) {
        int i = 0, j = s.size()-1;
        
        while(i < j) {
            // skip non alphabets
            while(i < s.size() && !isalpha(s[i]))
                ++i;
            while(j >= 0 && !isalpha(s[j]))
                --j;
            
            // swap the chars
            if(i < j)
                swap(s[i++], s[j--]);
        }
        return s;
    }
};
