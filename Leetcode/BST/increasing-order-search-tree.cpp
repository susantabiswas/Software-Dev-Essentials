/*
    https://leetcode.com/problems/increasing-order-search-tree/
    
    TC: O(N)
    SC: O(N)
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
    void newBST(TreeNode* root, TreeNode*& new_root,
               TreeNode*& last_node) {
        if(!root)
            return;
        
        newBST(root->left, new_root, last_node);
        
        // 1st node in inorder traversal, this will be the new root
        if(last_node) {
            last_node->right = root;
            root->left = nullptr;
        }
        // add the current element in inorder traversal order
        if(!new_root) {
            new_root = root;
        }
        // now the curr element becomes the last node for the next node
        last_node = root;
        
        newBST(root->right, new_root, last_node);
    }
    
    TreeNode* increasingBST(TreeNode* root) {
        TreeNode* new_root = nullptr;
        TreeNode* last_node = nullptr;
        
        newBST(root, new_root, last_node);
        return new_root;
    }
};
