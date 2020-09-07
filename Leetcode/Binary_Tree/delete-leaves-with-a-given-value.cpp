/*
    https://leetcode.com/problems/delete-leaves-with-a-given-value/
    
    Idea is do a post order traversal, so that we can check if the left and 
    right nodes of current exists or not, if they dont't current becomes a leaf node.
    Check if current == target and return nullptr to its parent->left/right to indicate deletion.
    
    NOTE: doing a delete on LC resulted in error, so had to remove that.
    TC: O(N)
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
    TreeNode* removeLeafNodes(TreeNode* root, int target) {
        // if current is NULL
        if(!root)
            return nullptr;
        
        // We process the left and right subtrees first
        root->left = removeLeafNodes(root->left, target);
        root->right = removeLeafNodes(root->right, target);
        // check if the current node is the same as the target and
        // also a leaf node
        if(!root->left && !root->right && root->val == target) {
            // delete the node
            delete root;
            return nullptr;
        }
        return root;
    }
};
