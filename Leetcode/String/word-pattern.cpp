/*
https://leetcode.com/problems/word-pattern/description/

For each char in pattern, check if it is possible to map one unique word to
each unique char.

TC: O(N)
*/
class Solution {
public:
    bool wordPattern(string pattern, string s) {
        unordered_map<char, string> char_word;
        unordered_map<string, char> word_char;

        string word;
        istringstream ss(s);
        int idx = 0;

        while(getline(ss, word, ' ')) {
            if((word_char.count(word) && word_char[word] != pattern[idx]) ||
                (char_word.count(pattern[idx]) && char_word[pattern[idx]] != word))
                return false;
            else if (word_char.count(word) == 0){
                word_char[word] = pattern[idx];
                char_word[pattern[idx]] = word;
            }

            ++idx;
        }

        if (idx < pattern.size())
            return false;
        return true;
    }
};
