/*
    https://leetcode.com/problems/sum-of-prefix-scores-of-strings/
    
    TC: O(nL (Insertion) + nL (Search))
    n = no. of words
    L = Length of longest word
    
    SC: O(nL)
    
    We can use a modified Trie to solve this problem. Idea is to also save the no. of substrings that
    end at each of the Trie node. 
    This way we can quickly know for a prefix the no. of matching substrings.
    Once we have built a trie like this, next is score computation for each of the words.
    
    For each word, we incrementally add each char and this simulates incremental building of prefix string.
    Since we already saved the char count for each node, we can find in one traversal the overall score of
    word.
*/
class Solution {
public:
    struct TrieNode {
        unordered_map<char, TrieNode*> leaves;
        bool is_string = false;
        // Tracks how many substring chars end here
        int char_count = 0;
    };
    
    // Adds a word to Trie
    void addWord(TrieNode* root, string& word) {
        for(char ch: word) {
            if(root->leaves.count(ch) == 0)
                root->leaves[ch] = new TrieNode();
            // go to the next node and update's char count
            root = root->leaves[ch];
            ++root->char_count;
        }
        root->is_string = true;
    }
    
    int prefixScore(TrieNode* root, string& word) {
        int total = 0;
        for(auto ch: word) {
            // For each successful prefix match, add the count of no. of chars
            // substrings that have this prefix
            if(root->leaves.count(ch)) {
                root = root->leaves[ch];
                total += root->char_count;
            }
            else
                break;
        }
        return total;
    }
    
    vector<int> sumPrefixScores(vector<string>& words) {
        TrieNode* root = new TrieNode();
        // Add each word to Trie
        for(auto word: words)
            addWord(root, word);
        
        vector<int> score(words.size(), 0);
        for(int i = 0; i < words.size(); i++)
            score[i] = prefixScore(root, words[i]);
        return score;
    }
};
