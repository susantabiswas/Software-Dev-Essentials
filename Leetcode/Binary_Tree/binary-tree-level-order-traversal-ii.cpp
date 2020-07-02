/*
    https://leetcode.com/problems/binary-tree-level-order-traversal-ii/
    
    We Do BFS and save the level wise output and then reverse the output 
    array
        
    TC: O(N)
    SC: O(N)
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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if(!root)
            return vector<vector<int>>{};
        vector<vector<int>> result;
        vector<int> level;
        queue<TreeNode*> q;
        
        q.emplace(root);
        int n_level = q.size();
        
        while(!q.empty()) {
            TreeNode *curr = q.front();
            q.pop();
            
            // add to current level
            level.emplace_back(curr->val);
            --n_level;
            
            // add the child nodes
            if(curr->left)
                q.emplace(curr->left);
            if(curr->right)
                q.emplace(curr->right);
            
            // if the level has ended
            if(n_level == 0) {
                n_level = q.size();
                result.emplace_back(move(level));
            }
        }
        // reverse the output levels
        reverse(result.begin(), result.end());
        return result;
    }
};
