/*
    https://leetcode.com/problems/detect-capital/
    
    TC: O(N)
*/

class Solution {
public:
    bool detectCapitalUse(string word) {
        int upper = 0;

        for(char &c: word)
            if(isupper(c))
                ++upper;
        // true when all upper, all lowercase or first char is only upper
        return word.size() == upper ||
            upper == 0 ||
            word.size() && isupper(word[0]) && upper == 1;
    }
};
