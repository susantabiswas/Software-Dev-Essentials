/*
    https://leetcode.com/problems/convert-bst-to-greater-tree/
    
    TC: O(N)
    SC: O(N)
    
    Idea is based on the fact that inorder traversal of BST traverses
    the elements in non-decreasing order. Since we want to update a node's 
    value with sum of all nodes greater than itself (including itself), we can just
    change the order of inorder traversal so that it traverses from right to left and
    traverses the elements in non-increasing order.
    Track the sum seen so far and for the curr node update its value with that.
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
    void greaterTree(TreeNode* root, long& sum_so_far) {
        if(!root)
            return;
        
        greaterTree(root->right, sum_so_far);
        // update the total sum so far and update the node value
        sum_so_far += root->val;
        root->val = sum_so_far;
        
        greaterTree(root->left, sum_so_far);
    }
    
    TreeNode* convertBST(TreeNode* root) {
        // tracks the total sum from greatest till current node
        long sum_so_far = 0;
        greaterTree(root, sum_so_far);
        return root;
    }
};
