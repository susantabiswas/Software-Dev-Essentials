/*
   
    https://leetcode.com/problems/minimum-score-triangulation-of-polygon/submissions/
    
    The idea is to  take each pair of vertices possible and then with those fixed, find 
    a vertex in between such that the polygon on left and right side of it are of min score.
    
*/

class Solution {
public:
    // Tabular Sol: Style 1
    // TC: O(N^3)
    // SC: O(N^2)
    int minScoreTriangulationTabular(vector<int>& arr) {
        if(arr.empty())
            return 0;
        
        const int N = arr.size();
        // dp(i, j): min triangulation score of polygon with vertices 
        // starting from i..j and there is an edge between i and j
        vector<vector<int> > dp(N, vector<int>(N, 0));
        
        // start sweeping each vertex using index 'i' and use the index
        // 'j' to keep the other end fixed, this i and j edge will then be evaluated
        // with every other vertex in between them by making a triangle with it and checking
        // the score of left and right side of remaining polygon.
        // first vertex
        for(int i = 2; i < N; i++) {
            // second vertex
            for(int j = i - 2; j >= 0; j--) {
                // pick the third vertex in between the endpoints
                for(int k = j + 1; k < i; k++) {
                    int curr_area = arr[i] * arr[k] * arr[j]; 
                    dp[j][i] = min(dp[j][i] == 0 ? INT_MAX : dp[j][i],
                                   dp[j][k] + curr_area + dp[k][i]);
                }
            }
        }
        return dp[0][N-1];
    }
    
    // Tabular Sol: Style 2
    int tabSol(vector<int>& values) {
        const int N = values.size();
        // dp[i][j] = max score of triangulation between vertices i and j
        vector<vector<int>> dp(N, vector<int>(N, 0));
        
        for(int l = 2; l < N; l++) {
            for(int start = 0; start < N - l; start++) {
                int end = start + l;
                for(int k = start + 1; k < end; k++) {
                    dp[start][end] = min(dp[start][end] == 0 ? INT_MAX : dp[start][end],
                                        values[start] * values[k] * values[end]
                                        + dp[start][k] + dp[k][end]);
                }
            }
        }
        
        return dp[0][N-1];
    }

    // using memoization
    // TC: O(N ^ 3)
    // SC: O(N ^ 2)
    int minScoreTriangulationRec(vector<vector<int> >& dp, 
                                 vector<int>& arr, int i, int j) {
            
        if(dp[i][j] == 0)
            // pick a vertex in between and evaulate the triangulation score
            for(int k = i + 1; k < j; k++) {
                int curr_score = arr[i] * arr[k] * arr[j];
                
                dp[i][j] = min(dp[i][j] == 0 ? INT_MAX : dp[i][j],
                              minScoreTriangulationRec(dp, arr, i, k) + // left polygon
                              curr_score +  // curret triangle with (i, k, j) vertices
                              minScoreTriangulationRec(dp, arr, k, j)); // right polygon
            }    
        
        return dp[i][j];
    }
    
    int minScoreTriangulationRecDriver(vector<int>& arr) {
        if(arr.empty())
            return 0;
        const int N = arr.size();
        vector<vector<int> > dp(N, vector<int>(N, 0));
        
        return minScoreTriangulationRec(dp, arr, 0, N-1);    
    }
    
    int minScoreTriangulation(vector<int>& A) {
        //return minScoreTriangulationTabular(A);
        return minScoreTriangulationRecDriver(A);
    }
};
