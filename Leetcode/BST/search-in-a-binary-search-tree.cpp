/*
    https://leetcode.com/problems/search-in-a-binary-search-tree/
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
    TreeNode* searchBST(TreeNode* root, int val) {
        if(!root)
            return nullptr;
        // if the current node is the one being searched
        if(root->val == val)
            return root;
        
        TreeNode* left = searchBST(root->left, val);
        TreeNode* right = searchBST(root->right, val);
        
        if(left || right)
            return left ? left : right;
        return nullptr;
    }
};
