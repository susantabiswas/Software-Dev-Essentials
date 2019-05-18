/*
    102. Binary Tree Level Order Traversal
    https://leetcode.com/problems/binary-tree-level-order-traversal/
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(!root)
            return vector<vector<int> > {};
        
        queue<TreeNode*> q;
        vector<vector<int> > ans;
        
        // add the root
        q.emplace(root);
        TreeNode* curr = nullptr;
        
        int level = 0;
        int node_c = q.size();
        
        // add the first level 
        ans.emplace_back(vector<int>{});
        
        while(!q.empty()) {
            // take out the current node
            curr = q.front();
            q.pop();
            --node_c;
            
            ans[level].emplace_back(curr->val);
            
            // add next level child nodes
            if(curr->left)
                q.emplace(curr->left);
            if(curr->right)
                q.emplace(curr->right);
            
            // add the next level vector to answer only if 
            // current level is not the last level
            if(node_c == 0 && !q.empty()) {
                node_c = q.size();
                ans.emplace_back(vector<int>{});
                ++level;
            }
        }
        
        return ans;
    }
};
