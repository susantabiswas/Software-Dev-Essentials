/*
    https://leetcode.com/problems/interval-list-intersections/submissions/
*/
class Solution {
public:
    // Shorter version with same time complexity
    vector<vector<int>> findIntersections2(vector<vector<int>>& A,
                                         vector<vector<int>>& B) {
        vector<vector<int>> result;
        int i = 0, j = 0;
        
        // pick the current intervals from A and B, and check if they can
        // be merged, then move to the side of earlier end point
        while(i < A.size() && j < B.size()) {
            // check overlap: 
            int start_pt = max(A[i][0], B[j][0]);
            int end_pt = min(A[i][1], B[j][1]);
            
            // only when the the two intervals overlap, the
            // start pt is <= end pt
            if(start_pt <= end_pt)
                result.emplace_back(vector<int>{start_pt, end_pt});
            
            if(A[i][1] > B[j][1])
                ++j;
            else
                ++i;
        }
        return result;
    }
    
    // First version: much longer
    vector<vector<int>> findIntersections1(vector<vector<int>>& A,
                                         vector<vector<int>>& B) {
        vector<vector<int>> result;
        
        if(A.empty() || B.empty())
            return result;
        
        int i = 0, j = 0;
        // current interval
        vector<int> curr;
        // we start with the interval with earliest time
        if(A[0][0] < B[0][0]) {
            curr = A[0];
            ++i;
        }
        else {
            curr = B[0];
            ++j;
        }
        
        while(i < A.size() || j < B.size()) {
            // we check for intersection with the earliest interval 
            // out of A and B
            // If one of the interval list has finished we continue with the other list
            if((i < A.size() && j < B.size() && A[i][0] < B[j][0]) ||
               (i < A.size() && j >= B.size())) {
                // check if there is any overlap of interval
                // the endpt should be smaller than equal to that of current interval
                if(curr[1] >= A[i][0])
                    result.emplace_back(vector<int>{min(curr[1], A[i][0]),
                                                   min(curr[1], A[i][1])});
                // check if the interval's endpoint is greater than current interval, if
                // it is then make the interval as the current interval
                if(A[i][1] > curr[1])
                    curr = A[i];
                ++i;
            }
            else if(j < B.size()) {
                // check if there is any overlap of interval
                if(curr[1] >= B[j][0])
                    result.emplace_back(vector<int>{min(curr[1], B[j][0]),
                                                   min(curr[1], B[j][1])});
                // check if the interval's endpoint is greater than current interval, if
                // it is then make the interval as the current interval
                if(B[j][1] > curr[1])
                    curr = B[j];
                ++j;
            }
        }
        return result;
    }
    
    
    // TC: O(N), SC: O(1)
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A,
                                             vector<vector<int>>& B) {
        // return findIntersections1(A, B);
        return findIntersections2(A, B);
    }
};
