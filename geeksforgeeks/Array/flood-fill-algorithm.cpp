/*
    https://practice.geeksforgeeks.org/problems/flood-fill-algorithm/0
*/
#include <bits/stdc++.h>
using namespace std;

void dfs(int i, int j, vector<vector<int>>& grid,
        int &color, int &src_color) {
    // out of bound check and check if already colored or not
    // and they are of the same color as that of source
    if(i < 0 || i >= grid.size() || j < 0 ||
        j >= grid[0].size() || grid[i][j] == color ||
        grid[i][j] != src_color)
        return;
        
    // color current
    grid[i][j] = color;
    // visit the neighbours
    dfs(i+1, j, grid, color, src_color);
    dfs(i-1, j, grid, color, src_color);
    dfs(i, j+1, grid, color, src_color);
    dfs(i, j-1, grid, color, src_color);
    
    return;
}

void solve(vector<vector<int>>& grid, int &color,
        int &x, int &y) {
    
    const int m = grid.size(), n = grid[0].size();
    // search for x,y
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            if(i == x && j == y) {
                int src_color = grid[i][j];
                dfs(i, j, grid, color, src_color);
                break;
            }
       
        
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++)
            cout << grid[i][j] << " ";
    }
}
        
int main()
{
    int t, m, n, color, x, y;
    cin >> t;
    while(t--) {
        cin >> m >> n;
        vector<vector<int>> grid(m, vector<int>(n, 0));
        
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                cin >> grid[i][j];
        
        cin >> x >> y >> color;
        solve(grid, color, x, y);
        cout << endl;
    }
	return 0;
}