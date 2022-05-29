/*
    https://leetcode.com/problems/maximum-number-of-points-with-cost/
    
    We process row by row:
        for each position 'j' in curr row, we need to know the max effective value from prev
        row for this pos 'j'.
        We track the max from left to right and update the max value seen for each col position,
        to account for |ci - cj|, we can just subtract 1 from max value seen so far when we iterate 
        forward each time.
        Repeat the process for right to left, for each pos pick the highest value.
        Finally add the repsective points value for each col position of curr row.
*/

class Solution {
public:
    // TC: O(MN)
    long long maxPoints(vector<vector<int>>& points) {
        if(points.empty())
            return 0;
        
        const int M = points.size(), N = points[0].size();
        // prev[j] = max point path till col j of previous row
        vector<long long> prev (N, 0);
        // curr[j] = max point path till col j of curr row
        vector<long long> curr(N, 0);
        
        for(int i = 0; i < M; i++) {
            // for the current row, find out the max value (accounting for |ci - cj| as well)
            // for each of the positions
            long long max_so_far = prev[0]; 
            // left to right scan
            for(int j = 0; j < N; j++) {
                // when the max is chosen for current, its value is again decreased by 1
                max_so_far = max(max_so_far-1, prev[j]);
                curr[j] = max_so_far;
            }
            // right to left scan
            max_so_far = prev[N-1];
            for(int j = N-1; j >= 0; j--) {
                max_so_far = max(max_so_far-1, curr[j]);
                curr[j] = max(curr[j], max_so_far);
            }
            
            // Now that we know about the max effective element for each position,
            // update the path value for current row
            for(int j = 0; j < N; j++)
                curr[j] += points[i][j];
            
            swap(prev, curr);
        }
                    
        return *max_element(prev.begin(), prev.end());
    }
};
