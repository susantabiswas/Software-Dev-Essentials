/*
    https://leetcode.com/problems/kth-smallest-element-in-a-bst/
    
    TC: O(logn + k), TC: O(k)
    Worst case is traversing till the depth of tree and then iterate till the kth element.
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
    // Finds the kth node
    // Inorder traversal of BST gives a sorted order
    // of elements, so once we are at kth node, return
    
    // TC: O(k), TC: O(k)
    bool findKthSmallest(TreeNode* root, int& k, TreeNode*& kth_node) {
        if(!root)
            return false;
        // search left subtree
        bool left = findKthSmallest(root->left, k, kth_node);
        // if node has been found, don't continue traversal
        if(left)
            return true;
        // process the current and if current is kth node, return
        --k;
        if(k == 0) {
            kth_node = root;
            return true;
        }
        
        // search right subtree
        bool right = findKthSmallest(root->right, k, kth_node);
        
        return false;    
    }
    
    int kthSmallest(TreeNode* root, int k) {
        TreeNode* kth_node = nullptr;
        findKthSmallest(root, k, kth_node);
        return kth_node->val;
    }
};
