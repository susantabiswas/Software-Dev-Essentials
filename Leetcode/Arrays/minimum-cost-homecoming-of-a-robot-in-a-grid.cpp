/*
    https://leetcode.com/problems/minimum-cost-homecoming-of-a-robot-in-a-grid/
    TC: O(M + N)
    
    Although the problem looks like a DFS problem, it can be solved with normal traversal.
    Thing to note is therte are no obstacles, hence the shortest path is to move diagonal, which in this
    scenario is not possible, so effective distance travelled is |dst_x - src_x| + |dst_y - src_y|
*/
class Solution {
public:
    int minCost(vector<int>& startPos, vector<int>& homePos, vector<int>& rowCosts, vector<int>& colCosts) {
        // Direection in which the axis traversal should happen
        int dx = startPos[0] <= homePos[0] ? 1  : -1;
        int dy = startPos[1] <= homePos[1] ? 1  : -1;
        
        long total_cost = 0;
        // Take the manhanttan style path
        for(int row = startPos[0]; row != homePos[0]; row += dx)
            total_cost += rowCosts[row + dx]; 
        
        for(int col = startPos[1]; col != homePos[1]; col += dy)
            total_cost += colCosts[col + dy]; 
            
        return total_cost;
    }
};
