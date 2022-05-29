/*
    https://leetcode.com/problems/trim-a-binary-search-tree/
    
    Idea:
    1. If root is smaller than low, then entire left subtree (including root) is smaller as well, so trim them
    2. If root is greater than high, entire right subtree (including root) is greater, trim them
    3. If root is well within the limit, recurse further for its left and right subtrees
    
    Note: While trimming, make sure to recurse further with the remaining subtree and not just return its root
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
    // TC: O(N)
    // SC: O(N)
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if(!root)
            return nullptr;
        
        // if current node lie within the range
        if(root->val >= low && root->val <= high) {
            root->left = trimBST(root->left, low, high);
            root->right = trimBST(root->right, low, high);
            return root;
        }
        // Root including its left subtree will be smaller than low
        // so trim the entire smaller subtree alongside root
        else if(root->val < low)
            return trimBST(root->right, low, high);
        // Root including entire right subtree will be greater than high,
        // so trim them
        else
            return trimBST(root->left, low, high);
            
    }
};
