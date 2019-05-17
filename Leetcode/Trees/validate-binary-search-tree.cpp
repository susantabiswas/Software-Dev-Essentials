/*
    98. Validate Binary Search Tree
    https://leetcode.com/problems/validate-binary-search-tree/
    
    Since inorder traversal of BST gives a non-decreasing order of elements, so we
    keep track of previous element and check if at any time the value of current node
    becomes lesser than equal to previous or not.
    TC: O(n)
    SC: O(1)
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
    // checks if a BST is valid or not
    bool isValid(TreeNode* root, TreeNode*& prev) {
        // a null node is always valid
        if(root == nullptr)
            return true;

        bool left = isValid(root->left, prev);
        // check if current node is in valid position
        if(prev && prev->val >= root->val)
            return false;
        // update value of previous node
        prev = root;
        bool right = isValid(root->right, prev);

        if(!left || !right)
            return false;

        return true;
    }

    bool isValidBST(TreeNode* root) {
        TreeNode* prev = nullptr;
        return isValid(root, prev);
    }
};
