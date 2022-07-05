/*
    https://leetcode.com/problems/count-words-obtained-after-adding-a-letter/
    
    Core idea is to save the frequency of chars of words somewhere and then use that to quickly
    look up if a word transformation is possible.
    
    Bitmask solution:
    We use bitmask to save the char mask of startWords in a set.
    Then for each word in targetWord, create a char mask with one char removed.
    Check if it exists in the startWords mask set, if it does then it is possible to create the targetWord.
*/
class Solution {
public:
    
    // SOLUTION 1
    // Note: TLE
    // TC: O(nL + m * n * L), m = no. of words in targetWords, n = no. of words in startWords
    int hashingSol(vector<string>& startWords, vector<string>& targetWords) {
        // freq for source words
        unordered_map<string, unordered_set<char>> freq;
        
        for(auto word: startWords)
            freq[word] = unordered_set<char>(word.begin(), word.end());
        
        int match = 0;
        
        for(auto dst_word: targetWords) {
            // The length of source words should be exactly len(targetWord)-1
            // this allows to do an Append operation and if needed do Rearrange
            
            // Whether possible to convert src word to destination word
            bool possible = false;
            for(auto src_word: startWords) {
                if(src_word.size() == dst_word.size()-1) {
                    possible = true;
                    
                    // Iterate through the char of target and ensure that all the 
                    // len-1 chars exist in the source word
                    int char_not_found = 0;
                    for(auto ch: dst_word) {
                        if(!freq[src_word].count(ch)) 
                            ++char_not_found;
                        if(char_not_found > 1) {
                            possible = false;
                            break;
                        }
                    }
                }
                // Possible to convert to current dst word, go to the next destination word
                if(possible) {++match;break;}
            }
        }
        return match;
    }
    
    // SOLUTION 2: Bitmasking
    // TC: O(nL + mL)
    // m = no. of words in targetWords, n = no. of words in startWords, L = max length of word
    // SC: O(m*26) ~ O(m)
    int bitmaskSol(vector<string>& startWords, vector<string>& targetWords) {
        const int N_BITS = 26;
        // save the bit masks of all the words of source
        unordered_set<bitset<N_BITS>> freq_mask_src;
        
        for(auto word: startWords) {
            bitset<N_BITS> mask;
            for(auto ch: word)
                mask |= (1 << (ch - 'a'));
            freq_mask_src.emplace(mask);
        }
          
        int match = 0;
        for(auto word: targetWords) {
            bool possible = false;
            bitset<N_BITS> mask;
            
            // get the bit mask of target word 
            for(int i = 0; i < word.size(); i++) 
                mask |= (1 << (word[i] - 'a'));
            
            // Remove the contribution of word[skip] char from the mask
            for(int skip = 0; skip < word.size(); skip++) {
                // char pos of the skipped char
                int char_pos = word[skip] - 'a';
                // save the current status of that position
                int bit_status = mask[char_pos];
                // set the bit to 0
                mask[char_pos] = 0;
                
                if(freq_mask_src.count(mask)) { 
                    possible = true;
                    break;
                }
                // revert the change
                mask[char_pos] = bit_status;
            }
                
            if(possible)
                ++match;            
        }
        return match;
    }
    
    
    int wordCount(vector<string>& startWords, vector<string>& targetWords) {
        // return hashingSol(startWords, targetWords);
        return bitmaskSol(startWords, targetWords);
    }
};
