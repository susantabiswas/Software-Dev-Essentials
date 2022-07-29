/*
    https://leetcode.com/problems/word-search-ii/
    TC: O(WL) + O((MN) * 4 * 3^L-1), 
        W: no. of words, L: max length of word
        O(WL) for inserting all the words in Trie
        O((MN) * 4 * 3^L-1): 
        We start DFS from each position of matrix(M x N).
        Now at the initial starting point in grid, we have 4 directions to explore with L-1
        remaining length, then the next time we have 3 directional positions for traversal
        (3 because we reached current cell from 1 one of the directions so it is already visited).
        So 4 (initially) * 3^L-1(remaining L-1 will each time have worst case 3 possible unvisited directions)
                            
    The idea is to create a Trie of the words to find, then for each position of grid
    check if the current char is in Trie and go further, we stop when there is no node in Trie
    for current char as that means there is anyways will be no such word to search.
*/

class Solution {
    struct TrieNode {
        unordered_map<char, TrieNode*> leaves;
        bool is_string = false;
    };
    
    class Trie {
    public:
        bool insert(TrieNode* root, string& word) {
            for(auto ch: word) {
                if(root->leaves.count(ch) == 0) 
                    root->leaves[ch] = new TrieNode();
                root = root->leaves[ch];
            }    
            // Whether we are inserting this string or not depends
            // on whether it was already added or not
            if(root->is_string)
                return false;
            return root->is_string = true;
        }    
        
        
    };
    
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
public:
    bool isValid(int row, int col, int M, int N) {
        return row >= 0 && row < M && col >= 0 && col < N;
    }
    
    void backtrack(int row, int col, string partial, TrieNode* root, 
                   vector<string>& result, vector<vector<char>>& board) {
        char ch = board[row][col];
        partial += ch;
        // mark the position as visited
        board[row][col] = '#';
        
        // base case, when seq is a string
        if(root->is_string) {
            result.emplace_back(partial);
            // Marking as false so that this same word is never picked again
            root->is_string = false;
        }
        
        for(auto [dx, dy]: directions) {
            int r = row + dx, c = col + dy;
            // Only take the step if that char is present in trie
            // and the cell is a valid unvisited cell 
            if(isValid(r, c, board.size(), board[0].size()) &&
               board[r][c] != '#' && root->leaves.count(board[r][c])) 
                backtrack(r, c, partial, root->leaves[board[r][c]], result, board);
        }
        // backtrack by reverting the change
        board[row][col] = ch;
    }
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode* root = new TrieNode();
        Trie* trie = new Trie();
        // Add the words to Trie
        for(auto word: words)
            trie->insert(root, word);
        
        vector<string> result;
        // From each cell, try looking for words
        for(int row = 0; row < board.size(); row++)
            for(int col = 0; col < board[0].size(); col++)
                // Only take the step if char is present
                if(root->leaves.count(board[row][col]))
                    backtrack(row, col, "",
                              root->leaves[board[row][col]], result, board);
        
        return result;
    }
};

///////////////////////////////////////
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
                    vector<string>& result, string partial, TrieNode* root) {
        
        // if the current position has already been visited
        if(board[i][j] == '#')
            return;
        
        partial += board[i][j];
        
        // check if the current char in board ends a string or not
        // If it does, then mark the flag as false, so that the same word
        // if found is not inserted again
        if(root->is_string) 
            result.emplace_back(partial), root->is_string = false;
        
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
        
        vector<string> result;
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
        
        return result;
    }
};
