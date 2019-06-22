/*
    807. Max Increase to Keep City Skyline
    https://leetcode.com/problems/max-increase-to-keep-city-skyline/
    
    We find the skyline from top and left side. The height increment for each building should
    be such that it doesnt cross the tallest building in its row and column, otherwise the skyline
    will change. So keeping that in mind we make it as large as possible with constraints:
        building(i, j) := min(left_skyline[i] - grid[i][j], top_skyline[j] - grid[i][j])
    TC: O(M*N)
*/

class Solution {
public:
	int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
		// get the row and column count
		const int M = grid.size();
		const int N = grid[0].size();

		vector<int> top_skyline(N, 0);
		vector<int> left_skyline(M, 0);

		long long extra = 0;

		// find the skyline for top and left view
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				left_skyline[i] = max(left_skyline[i], grid[i][j]);
				top_skyline[j] = max(top_skyline[j], grid[i][j]);
			}
		}

		// now we increase the height of each building by max possible length
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				extra += min(left_skyline[i] - grid[i][j], top_skyline[j] - grid[i][j]);
			}
		}
		return extra;
	}
};
