/*
    https://leetcode.com/problems/pacific-atlantic-water-flow/
    
    TC: O(MN)
    SC: O(MN)
    
    Idea is to find out the reachability of pacific and atlantic ocean water flow cells.
    These are the cells via which water can flow towards the ocean. We use dfs to figure out
    the reachability and once both the atlantic and pacific ocean reachability is figured out, we check for
    common cells via which water can flow towards both.
*/
class Solution {
public:
    void dfs(int i, int j, int prev_height, vector<vector<int>>& heights,
            vector<vector<bool>>& visited) {
        // out of bound and visited check
        if(i < 0 || i >= heights.size() || j < 0 || j >= heights[0].size()
          || visited[i][j] || heights[i][j] < prev_height)
            return;
        
        // mark visited
        visited[i][j] = true;
        
        // visit neighbors
        dfs(i+1, j, heights[i][j], heights, visited);
        dfs(i-1, j, heights[i][j], heights, visited);
        dfs(i, j+1, heights[i][j], heights, visited);
        dfs(i, j-1, heights[i][j], heights, visited);
    }
    
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        const int M = heights.size(), N = heights[0].size();
        // atlantic[i][j]: whether water can flow from here to atlantic ocean
        // pacific[i][j]: whether water can flow from here to atlantic ocean
        vector<vector<bool>> atlantic(M, vector<bool>(N, false));
        vector<vector<bool>> pacific(M, vector<bool>(N, false));
        
        // 1. DFS: reachability of pacific ocean from cells
        // top row
        for(int i = 0; i < N; i++)
            dfs(0, i, heights[0][i], heights, pacific);
        // left col
        for(int i = 0; i < M; i++)
            dfs(i, 0, heights[i][0], heights, pacific);
        
        // 2. DFS: reachability of atlantic ocean from cells
        // bottom row
        for(int i = 0; i < N; i++)
            dfs(M-1, i, heights[M-1][i], heights, atlantic);
        // right col
        for(int i = 0; i < M; i++)
            dfs(i, N-1, heights[i][N-1], heights, atlantic);
        
        // 3. Intersection of cells from where both atlantic and pacific can be reached
        vector<vector<int>> result;
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
                if(pacific[i][j] and atlantic[i][j])
                    result.emplace_back(vector<int>{i, j});
        
        return result;
    }
};
