/*
    https://leetcode.com/problems/determine-if-two-strings-are-close/
    
    TC: O(n)
    SC: O(n)
    
    2 conditions:
    1. any position of char can be changed
    2. All instances of x can be interchanged with 'y', where 'x' and 'y' both exists in the string
    
    So it basically means as long as we have all the chars of word2 and we have same no. of all the unique
    char lengths required, we can use above ops to get word2 from word1
    
    So first find the char frequency of word1 and also find group the chars for each unique frequency.
    Whenever a char's frequency doesnt match that of word2, as long as there is a char in word1 with the same
    frequency that is required, we can interchange the chars to get the desired frequency for the current char ch.
    
*/
class Solution {
public:
    bool closeStrings(string word1, string word2) {
        if(word1.size() != word2.size())
            return false;
        
        unordered_map<char, int> freq, freq2;
        // no. of chars with length l
        unordered_map<int, int> len;
        
        // find the frequency map for each char
        for(auto ch: word1)
            ++freq[ch];
        
        // group the chars of the same length
        for(auto [ch, length]: freq)
            ++len[length];
        
        // find the frequency map of word2
        for(auto ch: word2)
            ++freq2[ch];
        
        for(auto [ch, l]: freq2) {
            // word1 can only be mapped to word2 if the char with the same
            // length is possible
            if(freq.count(ch) == 0 || len[l] == 0)
                return false;
            
            // if an exact match was not found, an op is required to replace all the
            // instances of this char with another char whose frequency is 'l'
            if(freq[ch] != l)
            {
                // so one of the chars of length 'l' is given the length of this char and 
                // this char is given length 'l'. Now since we are processing this char, means
                // there will be one less char with length 'l' now
                --len[l];
            }
            
            freq.erase(ch);
        }
        
        return true;
    }
};
