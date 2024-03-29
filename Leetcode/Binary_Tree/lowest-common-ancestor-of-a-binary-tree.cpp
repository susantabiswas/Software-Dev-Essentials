/*
    https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/solution/
    
    SOLUTION 
    When a node is equal to either p or q, then it is its own descendant and is returned.
    LCA is the first node that has found descendants on both sides, we return that node
    if found.
    TC: O(n)
    SC: O(n), when the tree is skewed
    
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
    // SOLUTION 
    // Generalized solution for any binary tree
    TreeNode* sol(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root)
            return nullptr;
        // if current node is one of the two, then it is its own descendant
        if(root == p || root == q)
            return root;
        TreeNode *left = sol(root->left, p, q);
        TreeNode *right = sol(root->right, p, q);
        // if the current node has descendants returned from both sides,
        // then it is the LCA
        if(left && right)
            return root;
        return left ? left : right;
    }
    

    
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return sol(root, p, q);
    }
};
