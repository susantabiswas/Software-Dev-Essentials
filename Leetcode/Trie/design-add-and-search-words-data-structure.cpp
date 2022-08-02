/*
    https://leetcode.com/problems/design-add-and-search-words-data-structure/
    
    Idea is to use a Trie for adding the words. Now since we have a special char '.'
    which can match any single char, so we need to look into all possible cmb from that point.
    We can use DFS for searching, when we get '.' we do DFS for all the leaves nodes for
    the current level of Trie and check any of the DFS is able to find the complete pattern
    sequence.
*/

class WordDictionary {
    struct TrieNode {
        unordered_map<char, TrieNode*> leaves;
        bool is_string = false;
    };
    
    TrieNode *root_ = nullptr;
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root_ = new TrieNode();
    }
    
    /** Adds a word into the data structure. */
    // TC: O(L)
    void addWord(string word) {
        TrieNode *root = root_;
        
        for(char &c: word) {
            // Create a node if it doesn't exists for current char
            if(root->leaves.count(c) == 0)
                root->leaves[c] = new TrieNode();
            root = root->leaves[c];
        }
        // mark the end of string
        root->is_string = true;
    }
    
    // Searches for a word in Trie
    // TC: O(n * L), L: length of longest word
    // Worst case: when all the chars are . and all words in Trie are of same length
    bool searchWord(int idx, TrieNode *root, string &word) {
        // all the chars coevered, check if the current node marks
        // string end
        if(idx == word.size())
            return root->is_string;
        
        // if . char, match with all available chars at the current level
        if(word[idx] == '.') {
            for(auto it = root->leaves.begin(); it != root->leaves.end(); it++) {
                if(searchWord(idx+1, it->second, word))
                    return true;
            }
        }
        else if(root->leaves.count(word[idx]))
                return searchWord(idx+1, root->leaves[word[idx]], word);
        
        return false;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return searchWord(0, root_, word);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
