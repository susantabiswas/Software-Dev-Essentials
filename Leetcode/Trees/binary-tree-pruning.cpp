/*
    814. Binary Tree Pruning
    https://leetcode.com/problems/binary-tree-pruning/
    
    Recurse in postorder, if at current root we find 1 in current subtree, return true else false.
    Delete the child subtree from where we get false
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
    bool pruneTree1(TreeNode* root) {
        if(!root)
            return false;
        
        bool left = pruneTree1(root->left);
        bool right = pruneTree1(root->right);
        
        // delete the child subtree if it doesnt contain 1 
        if(!left) {
            delete root->left;
            root->left = nullptr;
        }
        if(!right) {
            delete root->right;
            root->right = nullptr;
        }
        
        // return the existence of 1 if in either of left, right or current
        return left || right || root->val == 1;
    }
    
    TreeNode* pruneTree(TreeNode* root) {
        bool result = pruneTree1(root);
        
        return result ? root : nullptr;
    }
};
