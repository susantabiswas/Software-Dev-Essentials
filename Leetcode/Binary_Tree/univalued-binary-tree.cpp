/*
    https://leetcode.com/problems/univalued-binary-tree/submissions/
    
    Idea is to compare the value of each root node with its 
    children. Do the same check in all subtrees.
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
    bool isUnivalTree(TreeNode* root) {
        if(!root)
            return true;
        // check if the currentt root has the same
        // value as that of its children if they exist
        if(root->left && root->val != root->left->val ||
          root->right && root->val != root->right->val)
            return false;
        // Check in left and right subtree
        return isUnivalTree(root->left) && 
                isUnivalTree(root->right);
    }
};
