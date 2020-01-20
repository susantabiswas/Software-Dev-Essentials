/*
    https://leetcode.com/problems/implement-trie-prefix-tree/submissions/
*/
class Trie {
private:
    struct TrieNode {
        // for keeping track of character child nodes
        unordered_map<char, unique_ptr<TrieNode>> leaves;
        // marks end of string
        bool is_string = false;
    };  
    unique_ptr<TrieNode> root_ = nullptr;
public:
    
    /** Initialize your data structure here. */
    Trie() {
        // create the root
        root_ = make_unique<TrieNode>(TrieNode());
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* root = root_.get();
        for(const char c: word) {
            // if current char is not there as a leaf, create
            if(root->leaves.find(c) == root->leaves.end())
                root->leaves[c] = make_unique<TrieNode>(TrieNode());
            // go to next node
            root = root->leaves[c].get();
        }
        // mark the end of current string
        root->is_string = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* curr = root_.get();
        // if at any char, we don't find a node for that, means not found
        for(const char& c: word) {
            if(curr->leaves.find(c) == curr->leaves.end())
                return false;
            curr = curr->leaves[c].get();
        }
        // check if string ending here is a a complete word or not
        return curr->is_string;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* curr = root_.get();
        for(const char& c: prefix) {
            if(curr->leaves.find(c) == curr->leaves.end())
                return false;
            curr = curr->leaves[c].get();
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
