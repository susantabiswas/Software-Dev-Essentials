/*
    https://leetcode.com/problems/count-good-nodes-in-binary-tree/submissions/
    
    Idea is to pass the max node encountered in each path from root and each
    time comparing the root node with the max node seen so far, if it is <= max seen
    so far or it is root, that means it is a good node.
    
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
    void preorder(TreeNode *root, TreeNode *max_node, 
                 int &good_nodes) {
        if(!root)
            return;
        // check if the max node in path till current is 
        // greater than current or not
        if(!max_node || max_node && max_node->val <= root->val)
            ++good_nodes;
        // update max node
        if(!max_node || root->val > max_node->val)
            max_node = root;
        // DFS in subtrees
        preorder(root->left, max_node, good_nodes);
        preorder(root->right, max_node, good_nodes);
    }
    
    int goodNodes(TreeNode* root) {
        int good_nodes = 0;
        preorder(root, nullptr, good_nodes);
        return good_nodes;
    }
};
