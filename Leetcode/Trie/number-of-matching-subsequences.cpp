/*
    https://leetcode.com/problems/number-of-matching-subsequences/
    
    TC: O(s * (w * L)), w = no. of unique words, L = max length of word
    SC: O(26 * 26) ~ O(1)
    
    Brute Force: O(s * (A * L)), A = no. of words, L = max length of word
    
    There is improvement when we get repeated words or words with common prefix.
    
    To save the result of subsequence search, we use Trie. Each Trie node saves the index of the 
    char in the target node if it is present otherwise it mark dead_end = true.
    Next time when we get a string with some seen chars, we iterate over the common chars of the string
    without doing a search in the target (s) string. Also if encounter a seen char that is absent in the target string, then
    we will have a node in the trie that says dead_end and we can conclude the search there itself.
*/
class Solution {
private:
    class TrieNode {
    private:
        unordered_map<char, TrieNode*> leaves;
        int target_match_idx = 0;
        // It's a dead end for search if the current node char is not present in target string
        bool dead_end = false;
        char c = '#';
    public:
        TrieNode(int idx, char ch, bool dead_end): target_match_idx(idx), c(ch), dead_end(dead_end) {};
        TrieNode() {}
        
        bool insert(TrieNode* root, string src, string target) {
            int n = target.size();
            int start = 0;
            
            for(int idx = 0; idx < src.size(); idx++) {
                char ch = src[idx];
                // Check if the char is a dead end search or not
                if(root->leaves.count(ch) && (root->leaves[ch])->dead_end)
                    return false;
                // check if the char node exists, if not check if that is part of subsequence
                if(!root->leaves.count(ch)) {
                    // Move iterator in target string till the 1st matching char is found
                    while(start < n && target[start] != src[idx]) 
                        ++start;
                    
                    // check if same char was found in target string
                    if(start < n && target[start] == src[idx]) 
                        root->leaves[ch] = new TrieNode(start, ch, false);
                    else {
                        // Insert a node that signifies a dead end, so that we don't proceed with
                        // a search repeatedly for any another same word
                        root->leaves[ch] = new TrieNode(-1, ch, true);
                        return false;
                    }
                }
                root = root->leaves[ch];
                start = root->target_match_idx + 1;
            }
            
            return true;
        }
    };
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        TrieNode* root = new TrieNode();
        int subseq = 0;
        
        for(auto word: words)
            if(root->insert(root, word, s))
                ++subseq;
        return subseq;
    }
};
