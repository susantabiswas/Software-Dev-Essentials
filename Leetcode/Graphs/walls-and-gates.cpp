/*
    663 · Walls and Gates
    https://www.lintcode.com/problem/663/

    TC: O(MNlog(MN))
    SC: O(MN)

    This is a classic djikstra problem, all the starting gates have dist = 0. This
    act as starting points, then from there we find the min dist for each of the 
    rooms.
*/
#include <bits/stdc++.h>

class Solution {
public:
    /**
     * @param rooms: m x n 2D grid
     * @return: nothing
     */
    void wallsAndGates(vector<vector<int>> &rooms) {
        const int M = rooms.size(), N = rooms[0].size();
        vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        auto comp = [&](const array<int, 3>& a, const array<int, 3>& b) { return a[0] >= b[0]; };
        // <dist, row, col>
        priority_queue<array<int, 3>, vector<array<int, 3>>, decltype(comp)> min_heap(comp);

        // Add all the gate positions as starting point
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
                if(rooms[i][j] == 0)
                    min_heap.push({0, i, j});

        while(!min_heap.empty()) {
            auto [dist, row, col] = min_heap.top();
            min_heap.pop();

            // if the curr dist is outdated, skip
            if(dist > rooms[row][col])
                continue;

            // process its neighbors
            for(auto dir: directions) {
                int r = row + dir[0], c = col + dir[1];
                // process the adj neighbor only if using the curr
                // room makes it's distance to a gate lesser
                if(r >= 0 && r < M && c >= 0 && c < N
                    && rooms[r][c] > dist + 1) {
                    rooms[r][c] = dist + 1;
                    min_heap.push({rooms[r][c], r, c});
                }
            }
        }
    }
}; 


/////////////////////////////////// DJIKSTRA 
/*
    https://leetcode.com/problems/walls-and-gates/
    
    TC: O(MNlogMN)
    SC: O(MN)
    
    We use djikstra's shortest path algorithm to find out the shortest path from gate to
    empty rooms. Idea is that each of the gates can act as a source for any of the rooms as
    long as it is the nearest one.
    We use a min heap for this, each time it will pick the cell with the shortest distance from
    any of the gates. Then just like BFS, add the neighbors's distance to heap and continue processing.
*/
class Solution {
private:
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1} };
public:
    // Valid, if the cell is in the grid and is empty
    bool isValid(int row, int col, int M, int N, vector<vector<int>>& rooms) {
        return row >= 0 && row < M && col >= 0 && col < N && rooms[row][col] == INT_MAX;
    }
    
    void wallsAndGates(vector<vector<int>>& rooms) {
        int m = rooms.size(), n = rooms[0].size();
        auto comp = [&](const array<int, 3>& a, const array<int, 3>& b) { return a[0] > b[0]; };
        // <distance to nearest gate, row, col>
        priority_queue<array<int, 3>, vector<array<int, 3> >, decltype(comp)> min_heap(comp);
        
        // Add all the source gates
        for(int r = 0; r < m; r++)
            for(int c = 0; c < n; c++)
                if(rooms[r][c] == 0)
                    min_heap.push({0, r, c});
        
        while(!min_heap.empty()) {
            auto [dist, row, col] = min_heap.top();
            min_heap.pop();
            
            // stale value
            if(rooms[row][col] < dist)
                continue;
            
            // Explore the unvisited neighbors
            for(auto [dx, dy]: directions) {
                int r = row + dx, c = col + dy;
                // Add if unvisited
                // since we are using a priority queue to get the cell based on the min distance
                // so the first time we see a cell, that will have the min distance
                // So we don't need to process a cell again if seen
                if(isValid(r, c, m, n, rooms)) {
                    rooms[r][c] = dist + 1;
                    min_heap.push({rooms[r][c], r, c});
                }
            }
        }
    }
};
