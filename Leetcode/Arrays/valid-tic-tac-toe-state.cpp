/*
    https://leetcode.com/problems/valid-tic-tac-toe-state/
    
    TC: O(N*N)
    
    Idea is simple, since X starts first, no. of X should either be equal or +1 than no. of O.
    We check for this scenario and few others. If a strike (continuous 3X or 3O) is completed, then
    based on which symbol completed, the no. of X and O is different.
    Check the state of Xs and Os after these scenarios:
    1. Horizontal Strike
    2. Vertical Strike 
    3. Right Diagonal
    4. Left Diagonal
*/
class Solution {
public:
    // Checks if the strike is valid or not based on the no. of Xs and Os.
    // Returns true if the continuous line of 0s or Xs is valid based on the config of board
    bool validStrike(int nX, int nO, int n, int total_x, int total_o) {
        if(nX == n or nO == n) {
            // Since X makes the 1st move, if it completes a strike, nO should always be 1 less
            if(nX == n && (total_o >= total_x))
                return false;
            // Since O makes the 2nd move, if it completes a strike, it should be equal to X
            if(nO == n && (total_o != total_x))
                return false;
        }
        return true;
    }
    
    bool validTicTacToe(vector<string>& board) {
        // n(x) == n(O) or x(X) == n(O) + 1
        // no moves after straight 3 Os or Xs => 3X (nX = nO + 1), 3O (nX = nO) 
        int total_x = 0, total_o = 0;
        int n = board.size();
        // <char=[X, O], no. of chars>
        // Used just to make the code cleaner
        unordered_map<char, int> freq;
        
        // calculate total X and O
        for(int r = 0; r < n; r++)
            for(int c = 0; c < n; c++)
                ++freq[board[r][c]];
        
        total_x = freq['X'], total_o = freq['O'];
        // Since X starts first, no. of X should either be equal or +1 than no. of O
        if(total_x != total_o + 1 && total_x != total_o)
            return false; 
        
        // check for 3 Xs or Os: Horizontally 
        for(int r = 0; r < n; r++) {
            freq.clear();
            for(int c = 0; c < n; c++)
                ++freq[board[r][c]];
            // Found a horizontal strike
            if(!validStrike(freq['X'], freq['O'], n, total_x, total_o))
                return false;
        }
        
        // check for 3 Xs or Os: Vertically 
        for(int c = 0; c < n; c++) {
            freq.clear();
            for(int r = 0; r < n; r++)
                ++freq[board[r][c]];
            // Found a vertical strike
            if(!validStrike(freq['X'], freq['O'], n, total_x, total_o))
                return false;
        }
        
        freq.clear();
        // check for a diagonal strike: Right upwards diagonal
        int r = 0, c = n-1;
        while(r < n && c >= 0) {
            ++freq[board[r][c]];
            ++r, --c;
        }
        // Found a diagonal strike
        if(!validStrike(freq['X'], freq['O'], n, total_x, total_o))
            return false;

        freq.clear();
        // check for a diagonal strike: Left downwards diagonal
        r = 0, c = 0;
        while(r < n && c < n) {
            ++freq[board[r][c]];   
            ++r, ++c;
        }
        // Found a diagonal strike
        if(!validStrike(freq['X'], freq['O'], n, total_x, total_o))
            return false;
        return true;
    }
};
