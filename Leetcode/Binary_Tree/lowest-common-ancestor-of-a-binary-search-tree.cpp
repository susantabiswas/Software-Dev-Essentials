/*
    https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
    
    SOLUTION 1
    When a node is equal to either p or q, then it is its own descendant and is returned.
    LCA is the first node that has found descendants on both sides, we return that node
    if found.
    TC: O(n)
    SC: O(n), when the tree is skewed
    
    SOLUTION 2
    We make use of BST property. When a node is equal to either p or q, then it is its own descendant
    and is returned. LCA is the first node that has found descendants on both sides, we return that node
    if found. We keep pruning the search path and move in the direction where the the nodes should exist
    according to their value, if we reach NULL then that means nodes are not present in tree.
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
    // SOLUTION 1
    // Generalized solution for any binary tree
    TreeNode* sol1(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root)
            return nullptr;
        // if current node is one of the two, then it is its own descendant
        if(root == p || root == q)
            return root;
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        // if the current node has descendants returned from both sides,
        // then it is the LCA
        if(left && right)
            return root;
        return left ? left : right;
    }
    
    // SOLUTION 2
    // Makes use of BST property for prunning the search path
    TreeNode* sol2(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root)
            return nullptr;
        // if current node is one of the two, then it is its own descendant
        if(root == p || root == q)
            return root;
        // for the current root, the two nodes exists on diff sides, so it is LCA
        else if((root->val < p->val && root->val > q->val) ||
               (root->val > p->val && root->val < q->val))
            return root;
        // search in the direction where the two nodes exists
        else if(root->val > p->val && root->val > q->val)
            return sol2(root->left, p, q);
        else
            return sol2(root->right, p, q);
    }
    
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // return sol1(root, p, q);
        return sol2(root, p, q);
    }
};
