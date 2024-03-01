/*
    https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
    
    TC: O(n)
    SC: O(n)
    
    Idea is to just do the preorder traversal and track the last processed node.
    For the current node the prev node is the predecessor node in the linked list also,
    so we make its right ptr point to current node, then make the current node as prev for
    its successor to update it next.
    
    Since the successor will update the right ptr, make sure to save it somewhere so that it 
    can be used to traverse to the right subtree.
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
    void toList(TreeNode* root, TreeNode*& prev) {
        if(!root)
            return;
        
        // save the right ptr, since the successor is going to set current
        // node's right ptr and we will loose track of right child
        TreeNode* right = root->right;
        
        // make the predecessor a linked list node pointing to
        // current node which is its successor
        if(prev) {
            prev->right = root;
            prev->left = nullptr;
        }
        
        // Current node has been processed (preorder processing, node is processed first)
        prev = root;
        
        toList(root->left, prev);
        toList(right, prev);
    }
    
    void flatten(TreeNode* root) {
        TreeNode* prev = nullptr;
        toList(root, prev);
    }
};
