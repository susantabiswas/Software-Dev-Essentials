/*
    https://leetcode.com/problems/path-sum/
    
    TC: O(N)
    SC: O(N)
    
    Idea is to simply subtract the current number from remaining targetSum
    and then pass the remaining downwards. Only at the leaf node, we check if
    the targetSum == 0 at the leaf node, if yes then we have a valid path.
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
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(!root)
            return false;
        
        targetSum -= root->val;
        // check if the path sum is equal to target or not
        if(!root->left && !root->right) 
            return targetSum == 0;    
        
        return hasPathSum(root->left, targetSum) ||
            hasPathSum(root->right, targetSum);
    }
};
