/*
    https://leetcode.com/problems/ransom-note/
*/
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> magazine_freq, ransom_freq;
        
        // store the frequency map of magazine
        for(const char& c: magazine)
            magazine_freq[c] += 1;
        // for each char in ransom note, if the freq of the char 
        // is more than what was found from magazine, then that means
        // ransom note cant be created
        for(const char& c: ransomNote) {
            ++ransom_freq[c];
            if(ransom_freq[c] > magazine_freq[c])
                return false;
        }
        
        return true;
    }
};
