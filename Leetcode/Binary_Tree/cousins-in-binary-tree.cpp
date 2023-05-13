/*
    https://leetcode.com/problems/cousins-in-binary-tree/
    
    Idea is to do BFS and check if any node is a parent of x or y.
    If parent is found for either x or y, then in order for them to be 
    cousins, they should be in the depth(level), so we can skip traversing further levels. Then we just check if parents for both the nodes were found or not and
    are they different.
    TC: O(N), SC: (m), m: nodes in last level, N: total number of nodes
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
    bool isCousins(TreeNode* root, int x, int y) {
        // if the root node is one of the cousins,
        // then it will always be false, as only root has no parent
        if(root->val == x && root->val == y)
            return false;
            
        queue<TreeNode*> q;
        q.emplace(root);
        
        TreeNode *x_parent = nullptr, *y_parent = nullptr;
        bool first = false, second = false;
        int n_level = 1;
        
        while(!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();
            --n_level;
            
            // if current is parent of any one
            if(curr->left) {
                q.emplace(curr->left);
                // one of child nodes is one of the cousins
                if(curr->left->val == x) {
                    x_parent = curr;
                }
                if(curr->left->val == y) {
                    y_parent = curr;
                }
            }
            
            if(curr->right) {
                q.emplace(curr->right);
                // one of child nodes is one of the cousins
                if(curr->right->val == x) {
                    x_parent = curr;
                }
                if(curr->right->val == y) {
                    y_parent = curr;
                }
            }
                
            if(n_level == 0) {
                // if level has ended and one of the cousins
                // is in next level, no need to traverse further
                if(x_parent || y_parent)
                    break;
                n_level = q.size();
            }
        }
        
        // if the nodes are cousins they must be in the same level, 
        // then we must have node values in the parent variables,
        // and the parents should have diff node values
        return x_parent && y_parent && x_parent != y_parent;
    }
};
