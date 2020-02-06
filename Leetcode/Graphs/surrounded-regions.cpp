/*
    https://leetcode.com/problems/surrounded-regions/
    
    TC: O(V^2)
*/
class Solution {
public:
    void DFS(vector<vector<char>>& board, int i, int j) {
        // boundary checking
        if(i < 0 || i >= board.size() || j < 0 || j >= board[0].size())
            return;
        // if already visited or X element
        if(board[i][j] == 'V' || board[i][j] == 'X')
            return;
        // mark it as visited
        board[i][j] = 'V';
        
        DFS(board, i+1, j);
        DFS(board, i-1, j);
        DFS(board, i, j+1);
        DFS(board, i, j-1);
    }
    
    void solve(vector<vector<char>>& board) {
        // Do DFS from each border O element, once all the 
        // components connected to boarder O have been visited,
        // remaining Os can be safely flipped to X, as they are
        // gauranteed to be covered by Xs.
        
        // We use V for marking a visited position
        for(int i = 0; i < board.size(); i++) {
            for(int j = 0; j < board[0].size(); j++) {
                // allow only boarder O elements
                if(i == 0 || i == board.size()-1 || j == 0 || j == board[0].size()-1)
                    if(board[i][j] != 'V' && board[i][j] == 'O')
                        DFS(board, i, j);
            }
        }
        
        // make all visited positions O and not visited X
        for(int i = 0; i < board.size(); i++)
            for(int j = 0; j < board[0].size(); j++)
                board[i][j] = (board[i][j] == 'V' ? 'O' : 'X');
    }
};
