/*
    https://leetcode.com/problems/flipping-an-image/submissions/
    
    TC: O(MN)
    SC: O(1)
*/
class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A) {
        // reverse and flip elements
        const int M = A.size(), N = A[0].size();
        
        for(int i = 0; i < M; i++) {
            int start = 0, end = N-1;
            // reverse elements pair wise and flip them
            while(start < end) {
                swap(A[i][start], A[i][end]);
                A[i][start] = !A[i][start];
                A[i][end] = !A[i][end];
                ++start, --end;
            }
            // flip the middle if odd number of columns
            if(start == end)
                A[i][start] = !A[i][start];
            
        }
        
        return A;
    }
};
