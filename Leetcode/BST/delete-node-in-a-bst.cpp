/*
    https://leetcode.com/problems/delete-node-in-a-bst/
    
    TC: O(logn)
    SC: O(logn)
    
    Since this a BST, we can prune the search and will traverse max of 
    height no. of nodes in the tree.
    
    There are 3 cases for a node:
    - If the node is a leaf node, delete it
    - If it has 1 child, make that child the child of node's parent
    - If it has 2 children, then we need to find the next greatest element that can
    take its place and that will the inorder successor.
*/
class Solution {
public:
    // Finds the inorder successor of a node in BST
    TreeNode* inorderSuccessor(TreeNode* root) {
        TreeNode* node = root->right;
        while(node->left) {
            node = node->left;    
        }
        return node;
    }
    
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(!root)
            return nullptr;
        
        if(root->val == key) {
            // if leaf node
            if(!root->left && !root->right) {
                delete root;
                return nullptr;
            }
            // if has both the children, current node is set to the inorder successor
            else if(root->left && root->right) {
                TreeNode* successor = inorderSuccessor(root);
                swap(successor->val, root->val);
                
                root->right = deleteNode(root->right, key);
                return root;
            }
            // if has only one child, just return that subtree
            else {
                TreeNode* subtree = root->left ? root->left : root->right;
                delete root;
                return subtree;
            }
        }
        
        root->left = deleteNode(root->left, key);
        root->right = deleteNode(root->right, key);
        
        return root;
    }
};
