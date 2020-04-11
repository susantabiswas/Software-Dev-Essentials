/*
    https://leetcode.com/problems/diameter-of-binary-tree/submissions/
    TC: O(N)
    
    The max path will be formed when a path is created using the path left + root + right.
    Idea is to always return the max path that is connected to the root from the subchild.
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
    int findDiameter(TreeNode* root, int& diameter) {
        if(!root)
            return 0;
        
        int left = findDiameter(root->left, diameter);
        int right = findDiameter(root->right, diameter);
        
        // left + root + right, -1 since we need only the edges
        int left_root_right = left + right + 1 - 1;
        // maximum path formed at current root
        if(diameter < left_root_right)
            diameter = left_root_right;
        
        // return the path formed with max of left or right subtree
        return max(left, right) + 1;
    }
    
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        findDiameter(root, diameter);
        return diameter;
    }
};
