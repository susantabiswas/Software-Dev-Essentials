/*
    https://leetcode.com/problems/cherry-pickup/
    
    TC: O(N^4)
    SC: O(N^4)
    Both can be reduced to O(N^3) using the fact that both the paths are moving in
    Manhanttan distance manner and thus x1 + y1 = x2 + y2, i.e the effective distance
    covered in both the paths is same.
    So if we know the values of any 3 vars, then the 4th var can be computed using the above
    formula and hence we can use a 3D vector to save DP state.
    
    The naive greedy way of picking the max cherry path forward and picking the path backwards
    with whatever is left doesn't work. This is because if we pick greedily in the forward path
    then we might isolate some cherries, basically breaking an effective path between them and in the way 
    backwards, due to these isolated cherry regions, we can pick only one of them. So the other is ignored
    and we end up with total cherries < global max.
    
    1110
    0011
    1010
    0011
    
    Greedy Pickup: forward => 
    111
      1
      1
      11
    
    backwards =>
    Option1:    0                    
                0
                1
                0000
    
    Option2: 0000
                1
                0
                0
    We can't pickup all the cherries on the way back due to the decision made in path forward.
    
    Optimal:
    Forward
    1
    0
    101
      11
    
    Backward
    011
      11
       0
       0
       
    Conclusion is both the paths are related and we need to consider the way path1 is picked
    also when deciding for path2. So we start the traversal for both the paths together from (0,0).
    At each position we compute the max cherries that can be picked from curr positions of both the 
    paths. The two path positions might converge if we dont take care, we need to specifically ensure
    that when the two positions are same, then we count the cherry for that pos only once, this
    would ensure that reward for staying on the same path is correct.
    
*/
class Solution {
public:
    
    long maxPath(int x1, int y1, int x2, int y2,
                vector<vector<int>>& grid, unordered_map<string, int>& dp) {
        // This key is used for hash table 
        string key = to_string(x1) + ',' + to_string(y1) + 
                    ',' + to_string(x2) + ',' + to_string(y2);
        
        // out of bound or the pos is blocked
        if(x1 >= grid.size() || x2 >= grid.size()
          || y1 >= grid.size() || y2 >= grid.size()
          || grid[x1][y1] == -1 || grid[x2][y2] == -1)
            return INT_MIN;
        
        // destination reached, this line is imp as without it we won't know whether
        // path is actually possible to the destination or not from top left
        // because of nature of movement i.e only forward either
        // right or down, the total effective distance (Manhattan Distance) travelled by both is same
        // and they both will reach the end at the same time
        if(x1 == grid.size()-1 && y1 == grid.size()-1)
           return dp[key] = grid[x1][y1];

        // Find the max path sum from current position to reach the target
        if(dp.count(key) == 0) {
            int total_cherries = 0;
            // if the two positions are diff, then we can pick the
            // cherries at both the places
            if (x1 == x2 && y1 == y2) 
                total_cherries = grid[x1][y1];
            else 
                total_cherries = grid[x1][y1] + grid[x2][y2];
            
            // Since we can move either right or down and we have to do this
            // for both the paths, we can have 4 cmb => RR, RD, DD, DR.
            // Pick the cmb whichever gives the max sum path
            dp[key] = total_cherries 
                    + max({maxPath(x1, y1+1, x2, y2+1, grid, dp), // RR
                           maxPath(x1, y1+1, x2+1, y2, grid, dp), // RD
                           maxPath(x1+1, y1, x2+1, y2, grid, dp), // DD
                           maxPath(x1+1, y1, x2, y2+1, grid, dp)}); // DR
        }
        return dp[key];
    }
    
    int cherryPickup(vector<vector<int>>& grid) {
        if(grid.empty())
            return 0;
        
        const int M = grid.size(), N = grid[0].size();
        // dp["x1,y1,x2,y2"] = max sum cherry path if started from (x1, y1) & (x2, y2)
        unordered_map<string, int> dp;
        // Find the max sum path to reach (n-1, n-1)
        int total_cherries = maxPath(0, 0, 0, 0, grid, dp);
        return total_cherries < 0 ? 0 : total_cherries;
    }
};