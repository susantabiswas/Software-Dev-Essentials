/*
    https://leetcode.com/problems/word-search/
    
    TC: O(m * n * 3^L)
    In the worst case, we end up making m*n calls to dfs(..).
    In DFS(), we make 4 calls in the beginning and then only make 3 calls (since we can't go back to the
    direction of parent) afterwards.
    
    Each call makes 3 more calls, so we form a 3-ary tree. So the total no. of paths = no. of leaf nodes in 3-ary tree
    i.e 3^L
    
    SC: O(L)
*/
class Solution {
public:
    bool dfs(int curr, int r, int c, vector<vector<char>>& board, string& word) {
        if(curr == word.size())
            return true;
        
        if(r < 0 || r >= board.size() || c < 0 || c >= board[0].size() || word[curr] != board[r][c])
            return false;
        
        // mark as visited
        char orig = board[r][c];
        board[r][c] = '#';
        
        bool possible = dfs(curr+1, r+1, c, board, word)
            || dfs(curr+1, r-1, c, board, word)
            || dfs(curr+1, r, c+1, board, word)
            || dfs(curr+1, r, c-1, board, word);
        
        board[r][c] = orig;
        return possible;
    }
    
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(), n = board[0].size();
        
        for(int r = 0; r < m; r++)
            for(int c = 0; c < n; c++)
                if(dfs(0, r, c, board, word))
                    return true;
        return false;
    }
};
