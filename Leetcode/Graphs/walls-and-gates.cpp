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
