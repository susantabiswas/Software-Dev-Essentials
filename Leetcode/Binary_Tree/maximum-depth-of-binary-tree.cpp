/*
    https://leetcode.com/problems/maximum-depth-of-binary-tree/submissions/
    TC: O(N)
    SC: O(N)
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
    int maxDepth(TreeNode* root) {
        if(!root)
            return 0;
        
        // pich the subtree with more no. of nodes
        return 1 + max(maxDepth(root->left),
                      maxDepth(root->right));
    }
};
