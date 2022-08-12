/*
    https://leetcode.com/problems/longest-word-with-all-prefixes/
    
    Idea is to create a Trie and add all the words to it.
    Modifying the normal search method a bit to check at each stage whether the prefix
    exists as word or not.
    Then for each word, check if all its prefix exists as words or not.
*/
class Solution {
public:
    struct TrieNode {
        unordered_map<char, TrieNode*> leaves;
        bool is_string = false;
    };
    
    // Adds word to Trie
    bool addWord(TrieNode* root, string& word) {
        for(auto ch: word) {
            if(root->leaves.count(ch) == 0)
                root->leaves[ch] = new TrieNode();
            root = root->leaves[ch];
        }    
        if(root->is_string == false)
            return root->is_string = true;
        return false;
    }
    
    // Checks if each prefix of a word exists in Trie
    bool searchPrefix(TrieNode* root, string word) {
        for(auto ch: word) {
            if(root->leaves.count(ch) == 0)
                return false;
            root = root->leaves[ch];
            // Check if current prefix exists as a word or not
            if(root->is_string == false)
                return false;
        }   
        return true;
    }
    
    // TC: O(wL + w*(L + L))
    // SC: O(wL)
    // w: no. of words, L = Length of longest word
    // Worst case scenario is when all the words have their prefix existing as words
    // and for this we traverse for its entire length in Trie and also compare with the
    // longest word found so far to see if this is lexographically smaller.
    string longestWord(vector<string>& words) {
        // Add each word to Trie
        int max_len = 0;
        // Root of Trie
        TrieNode* root = new TrieNode();
        string longest;
        
        // Add the words to Trie
        for(auto word: words) 
            addWord(root, word);
        
        
        // Look for the word with all prefixes present as word
        for(auto word: words) {
            if(searchPrefix(root, word)) {
                if(longest.size() < word.size() || 
                   (longest.size() == word.size() && word < longest))
                    longest = word;
            }
        }
        return longest;
    }
};
