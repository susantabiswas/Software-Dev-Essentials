/*
    https://leetcode.com/problems/game-of-life/
*/
class Solution {
public:
    // finds the number of ones in neighbourhood
    int findOnes(vector<vector<int>>& board, const int& M, const int& N,
                int i, int j) {
        int num_ones = ((j-1 >= 0) ? board[i][j-1] > 0 : 0) +
                        ((j+1 < N) ? board[i][j+1] > 0 : 0) +
                        ((i-1 >= 0) ? board[i-1][j] > 0 : 0) +
                        ((i+1 < M) ? board[i+1][j] > 0 : 0) + 
                        ((i+1 < M && j-1 >= 0) ? board[i+1][j-1] > 0 : 0) +
                        ((i+1 < M && j+1 < N) ? board[i+1][j+1] > 0 : 0) +
                        ((i-1 >= 0 && j-1 >= 0) ? board[i-1][j-1] > 0 : 0) +
                        ((i-1 >= 0 && j+1 < N) ? board[i-1][j+1] > 0 : 0);
        
        return num_ones;
    }
    
    void gameOfLife(vector<vector<int>>& board) {
        const int M = board.size(), N = board[0].size();
        // find the state information of neighbours and save the next state info
        // for each cell in encoded form.
        // If current cell has 1, denote with +ve
        //            cell has 0, denote with -ve
        // If the current cell will stay 1 in next state: denote with 2
        //                 cell will become 0 in next state: denote with 3
        // Using the combination of above two we can save the current as well as next state info
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++) {
                int curr_state = board[i][j];
                int num_ones = findOnes(board, M, N, i, j);
                // rule 4
                if(board[i][j] == 0)
                    board[i][j] = num_ones == 3 ? 2 : 3;
                else { // remaining rules
                    board[i][j] = num_ones < 2 ? 3 : (num_ones <= 3 ? 2 : 3);
                }
                // save the current state info
                board[i][j] = (curr_state == 0 ? -1 : 1) * board[i][j];
            }
        
        // fill the next state using the information
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++) 
                board[i][j] = abs(board[i][j]) == 2 ? 1 : 0;
    }
};
