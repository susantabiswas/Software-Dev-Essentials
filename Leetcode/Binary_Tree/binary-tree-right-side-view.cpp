/*
    https://leetcode.com/problems/binary-tree-right-side-view/
    
    Do normal BFS so that we can be aware of the level. In each level add the last
    node to the traversal result.
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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        
        queue<TreeNode*> q;
        // Add non-null root
        if(root)
            q.emplace(root);
        int n_level = q.size();
        
        while(!q.empty()) {
            TreeNode *curr = q.front();
            q.pop();
            --n_level;
            
            if(curr->left)
                q.emplace(curr->left);
            if(curr->right)
                q.emplace(curr->right);
            
            // end of level
            if(n_level == 0) {
                // add the last node of current level
                result.emplace_back(curr->val);
                n_level = q.size();
            }
        }
        
        return result;
    }
};
