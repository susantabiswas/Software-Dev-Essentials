/*
    https://leetcode.com/problems/word-search-ii/submissions/
    TC: O(WL) + O((MN) ^ 4), 
        W: no. of words, L: max length of word
        O(WL) for inserting all the words in Trie
        O((MN) ^ 4): We start DFS from each position of matrix(M x N) and also
                    in worst case, it can traverse the entrie grid (MN)
    
    The idea is to create a Trie of the words to find, then for each position of grid
    check if the current char is in Trie and go further, we stop when there is no node in Trie
    for current char as that means there is anyways will be no such word to search.
*/


class Solution {
public:
    struct TrieNode {
        unordered_map<char, unique_ptr<TrieNode> > leaves;
        bool is_string = false; 
    };
    // Trie class
    class Trie {
        private:
            unique_ptr<TrieNode> root_ = make_unique<TrieNode>(TrieNode());
        
        public:
            // inserts word in Trie
            bool Insert(const string& word) {
                TrieNode* root = root_.get();
                for(const char& c: word) {
                    if(root->leaves.find(c) == root->leaves.end())
                        root->leaves[c] = make_unique<TrieNode>(TrieNode());
                    root = root->leaves[c].get();
                }
                // mark the current word as a complete string
                if(root->is_string == false)
                    return root->is_string = true;
                // indicates that this word has not been inserted again
                return false;
            }
        
            TrieNode* getRoot() {
                return root_.get();
            }
    };
    
    // boundary checking
    bool isValid(int i, int j, int M, int N) {
        return i >= 0 && i < M && j >= 0 && j < N;
    }
    
    void DFS(vector<vector<char> >& board, int i, int j, 
                    unordered_set<string>& result, string partial, TrieNode* root) {
        
        // if the current position has already been visited
        if(board[i][j] == '#')
            return;
        
        partial += board[i][j];
        
        // check if the current char in board ends a string or not
        if(root->is_string) 
            result.insert(partial);
        
        // mark it visited
        char curr_char = board[i][j];
        board[i][j] = '#';
        
        // traverse in 4 directions, we only travese if the next char is there in the Trie
        int row = i + 1, col = j;
        if(isValid(row, col, board.size(), board[0].size()) &&
           root->leaves.find(board[row][col]) != root->leaves.end()) {

            DFS(board, row, col, result, partial, root->leaves[board[row][col]].get());
        }
        
        row = i, col = j - 1;
        if(isValid(row, col, board.size(), board[0].size()) &&
           root->leaves.find(board[row][col]) != root->leaves.end()) {

            DFS(board, row, col, result, partial, root->leaves[board[row][col]].get());
        }
        
        row = i - 1, col = j;
        if(isValid(row, col, board.size(), board[0].size()) &&
           root->leaves.find(board[row][col]) != root->leaves.end()) {

            DFS(board, row, col, result, partial, root->leaves[board[row][col]].get());
        }
        
        row = i, col = j + 1;
        if(isValid(row, col, board.size(), board[0].size()) &&
           root->leaves.find(board[row][col]) != root->leaves.end()) {

            DFS(board, row, col, result, partial, root->leaves[board[row][col]].get());
        }
        // mark it unvisited 
        board[i][j] = curr_char;
    }
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        // Idea is to create a Trie with the words to search, instead of creating the words
        // when doing DFS of matrix, that will create a lot of unecessary words(a lot!) in avg cases
        Trie obj = Trie();
        for(const string& word: words)
            obj.Insert(word);
        
        unordered_set<string> result;
        const int M = board.size(), N = board[0].size();
        
        // get the root of Trie
        TrieNode *root = obj.getRoot();
        string partial;
        
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
                // start traversal only if char is in Trie
                if(root->leaves.find(board[i][j]) != root->leaves.end()) {
                   DFS(board, i, j, result, partial, root->leaves[board[i][j]].get());
                }
        
        return vector<string>{result.begin(), result.end()};
    }
};
