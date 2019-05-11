/*
    1038. Binary Search Tree to Greater Sum Tree 
    https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/
    
    TC: O(n)
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
    
    // does the required task
    /*
        We just need to traverse in right, current, left manner.
        We keep track of last value from right subtree and that is used
        for upadting the value of current node
    */
    int changeBST(TreeNode* root, int& greater_val) {
        if(root == nullptr) 
            return 0;
        
        // We first go right, then process current and go left
        int right = changeBST(root->right, greater_val);
        // process current node, as we know all the bigger nodes
        root->val = root->val + greater_val;
        greater_val = root->val;
        // process left subtree nodes
        int left = changeBST(root->left, greater_val);
        
        return greater_val;
    }
    
    TreeNode* bstToGst(TreeNode* root) {
        int greater_val = 0;
        changeBST(root, greater_val);
        return root;
    }
};
