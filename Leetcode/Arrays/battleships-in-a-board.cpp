/*
    https://leetcode.com/problems/battleships-in-a-board/
    
    TC: O(MN)
    SC: O(1)
    
    The idea is to find the start of a ship array. We can increment the ship counter
    if we are sure that the ship is the 1st ship in either horizontal or vertical ship array.
    We do traversal column wise, for each element check if it is part of a vertical or horizontal
    ship array, if it is not, then ++ships.
*/
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        int M = board.size(), N = board[0].size();
        
        int ships = 0;
        // start traversal column wise
        for(int col = 0; col < N; col++)
            for(int row = 0; row < M; row++) {
                if(board[row][col] == 'X') {
                    // if it is part of a horizontal ship array 
                    if(col - 1 >= 0 && board[row][col-1] == 'X')
                        continue;
                    // if current ship is part of vertical ship array
                    if(row - 1 >= 0 && board[row-1][col] == 'X')
                        continue;
                    // start of a new ship array, either vertical or horizontal
                    ++ships;
                }        
            }
        
        return ships;
    }
};
