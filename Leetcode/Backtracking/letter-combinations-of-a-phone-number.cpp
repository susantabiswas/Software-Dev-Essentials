/*
    https://leetcode.com/problems/letter-combinations-of-a-phone-number/
    
    TC: O(4^d), d= No. of digits in string
    
    Idea is simple, for each digit in string, we try out all possible 
    positional chars for that digit, and recurse further for d-1 remaining digits.
*/
class Solution {
public:
    void keypadCombinations(int curr, string &digits,
                           unordered_map<char, string> &keypad, string partial,
                            vector<string> &cmbs) {
        // All the digits covered, using move to skip copying letter by letter
        if(curr == digits.size()) {
            if (partial.empty() == false)
                cmbs.emplace_back(move(partial));
            return;
        }    
        // For the current position, try the different letters avail
        for(char &ch: keypad[digits[curr]]) {
            keypadCombinations(curr+1, digits, keypad, partial + ch, cmbs);
        }
    }
    
    vector<string> letterCombinations(string digits) {
        unordered_map<char, string> keypad = {{'2', "abc"}, {'3', "def"},
                                             {'4', "ghi"}, {'5', "jkl"},
                                             {'6', "mno"}, {'7', "pqrs"},
                                             {'8', "tuv"}, {'9', "wxyz"},};
        vector<string> cmbs;
        
        keypadCombinations(0, digits, keypad, "", cmbs);
        return cmbs;
    }
};
