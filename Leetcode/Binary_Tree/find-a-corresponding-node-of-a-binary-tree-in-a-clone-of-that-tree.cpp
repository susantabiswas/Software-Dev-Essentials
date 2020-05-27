/*
    https://leetcode.com/problems/find-a-corresponding-node-of-a-binary-tree-in-a-clone-of-that-tree/submissions/
    
    Since there is a clone of the original tree, we do traversal of original 
    tree alongside the cloned tree and once the target node is found set the ref_node 
    to the current node of cloned tree.

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
    bool traverseTree(TreeNode* orig, TreeNode* cloned,
                     TreeNode* target, TreeNode*& ref_node) {
        if(orig) {
            // check the current node
            if(orig == target) {
                ref_node = cloned;
                return true;
            }
            
            return traverseTree(orig->left, cloned->left, target, ref_node) ||
                    traverseTree(orig->right, cloned->right, target, ref_node);
        }   
        return false;
    }
    
    TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
        TreeNode* ref_node = nullptr;
        // preorder traversal
        traverseTree(original, cloned, target, ref_node);
        return ref_node;
    }
};
