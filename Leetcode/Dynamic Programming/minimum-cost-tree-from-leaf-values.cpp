/*
    https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/
    
    The idea is to keep track of min inner sum of nodes that can be formed by each subarray range.
    TC: O(N^3)
    SC: O(N^2)
    
*/
class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        const int N = arr.size();
        // max_leaf(i, j): max value leaf node in [i:j]
        vector<vector<int> > max_leaf(N, vector<int>(N, 0));
        // inner_node(i, j): min sum of inner node possible in [i:j]
        vector<vector<int> > inner_node(N, vector<int>(N, INT_MAX));
        
        for(int i = 0; i < N; i++)
            max_leaf[i][i] = arr[i];
        
        for(int l = 0; l < N; l++) {
            for(int start_idx = 0; start_idx < N - l; start_idx++) {
                int end_idx = start_idx + l;
                
                for(int k = start_idx; k < end_idx; k++) {
                    // update the max leaf node
                    max_leaf[start_idx][end_idx] = max(max_leaf[start_idx][k], max_leaf[k+1][end_idx]);
                    // find the inner sum for the current k
                    int left_subtree = inner_node[start_idx][k] == INT_MAX ? 0 : inner_node[start_idx][k];
                    int right_subtree = inner_node[k+1][end_idx] == INT_MAX ? 0 : inner_node[k+1][end_idx];
                    int curr_inner_sum =  left_subtree +  right_subtree + 
                                           max_leaf[start_idx][k] * max_leaf[k+1][end_idx];
                    inner_node[start_idx][end_idx] = min(inner_node[start_idx][end_idx], 
                                        curr_inner_sum);
                }
            }
        }
        
        //for(auto v:inner_node){for(auto a: v)cout<<a<<" ";cout<<endl;}
        return inner_node[0][N-1];
    }
};
