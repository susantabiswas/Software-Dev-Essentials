/*
    https://leetcode.com/problems/prefix-and-suffix-search/submissions/
    
    We use a modified Trie, where each node also contains an index vector
    of the words whose chars reach till that node.
    Also we create two Tries, one for suffix and other for prefix.
    For suffix trie, we reverse the word during construction so that we can search it 
    from back side starting from root, also during search in suffix tree the word
    to be searched also needs to be reversed.
    
    Finally in the find function we get the indices for both suffix and prefix, we
    find the largest common index using a linear traversal.
*/
class Trie {
private:
    struct TrieNode {
        unordered_map<char, TrieNode*> leaves;
        bool is_string = false;
        vector<int> indices;
    };
    
    TrieNode *root_ = new TrieNode();

public:
    // Adds a word into Trie
    // TC: O(L)
    void addWord(string word, int &idx) {
        TrieNode *root = root_;
        
        for(char &c: word) {
            // Create a node if it doesn't exists for current char
            if(root->leaves.count(c) == 0)
                root->leaves[c] = new TrieNode();
            root = root->leaves[c];
            // save the index of the word which contributed the char
            root->indices.emplace_back(idx);
        }
        // mark the end of string
        root->is_string = true;
    }
    
    // Searches for a word in Trie
    // TC: O(L), L: length of longest word
    vector<int> searchWord(string &word) {
        TrieNode *root = root_;
        
        for(char &c: word) {
            if(root->leaves.count(c))
                root = root->leaves[c];
            else
                return {};
        }
        return root->indices;
    }
};

class WordFilter {
    Trie prefix_trie = Trie();
    Trie suffix_trie = Trie();
public:
    WordFilter(vector<string>& words) {
        // create prefix and suffix Trie
        for(int i = 0; i < words.size(); i++) {
            prefix_trie.addWord(words[i], i);
            // reverse the word
            reverse(words[i].begin(), words[i].end());
            suffix_trie.addWord(words[i], i);
        }
    }
    
    // TC: O(L + L + n + n) ~ O(L + n), n: total number of words
    // L: length of the longest word
    int f(string prefix, string suffix) {
        reverse(suffix.begin(), suffix.end());
        auto prefix_indices = prefix_trie.searchWord(prefix);
        auto suffix_indices = suffix_trie.searchWord(suffix);
        int match = -1;
        
        int i = prefix_indices.size() - 1, j = suffix_indices.size() - 1;
        // find the largest matching index
        while(i >= 0 && j >= 0) {
            if(prefix_indices[i] == suffix_indices[j]) {
                match = prefix_indices[i];
                break;
            }
            else if(prefix_indices[i] < suffix_indices[j])
                --j;
            else
                --i; 
        }
        return match;
    }
    
};

/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter* obj = new WordFilter(words);
 * int param_1 = obj->f(prefix,suffix);
 */
