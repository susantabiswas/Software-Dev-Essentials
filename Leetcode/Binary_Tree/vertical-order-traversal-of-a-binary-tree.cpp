/*
    https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/submissions/
    
    We use a hash table to keep track of x and y coordinate of each node.
    Root is taken as x = 0, y = 1 and for each DFS call y = y + 1 and
    each left DFS call (x = x - 1) and right DFS call (x = x + 1).
    We do preorder traversal and add the nodes acc to its x and y coord
    in the hash table.
    TC: O(N)
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void dfs(TreeNode *root, int x, int y,
             map<int, map<int, vector<int>> > &dist) {
        
        if(root) {
            dist[x][y].emplace_back(root->val);
            dfs(root->left, x-1, y+1,  dist);
            dfs(root->right, x+1, y+1, dist);
        }
    }
    
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        // {x_coord: {y_coord: vector of node values}}
        map<int, map<int, vector<int>> > dist;
        dfs(root, 0, 1, dist);
        
        vector<vector<int>> result;
        
        // traverse the same x coordinate nodes
        for(auto x_it = dist.begin(); x_it != dist.end(); x_it++) {
            vector<int> x_nodes;
            // traverse the y coordinate elements for the same x coord.
            for(auto y_it = x_it->second.begin(); y_it != x_it->second.end(); y_it++) {               // sort the element in increasing order of the same y coord.
                sort(y_it->second.begin(), y_it->second.end());
                for(auto node : y_it->second)
                    x_nodes.emplace_back(node);
            }
            result.emplace_back(move(x_nodes));
        }
        return result;
    }
};
