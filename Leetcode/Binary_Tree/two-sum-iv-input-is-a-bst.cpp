/*
    https://leetcode.com/problems/two-sum-iv-input-is-a-bst/
    
    TC: O(nlogn)
    SC: O(n)
    
    1. Iterate through the elements
        1.1 For each element, check if the counterpart is present or not
        1.2 If present return true

    Best Solution
    TC: O(n)
    SC: O(n)

    Solution 1
    - We can do an inorder traversal of BST and save the elements, inorder of BST ensures that
    we will be traversing in sorted order.
    - Once we have the sorted order of elements, we perform the classic 2 sum solution using two pointers.

    Solution 2
    - Perform any traversal and save the elements
    - Perform 2 sum using hashing
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
    // Finds whether a number is present or not
    bool exists(TreeNode* root, int x) {
        if(!root)
            return false;
        
        if(root->val == x)
            return true;
        else if(root->val < x)
            return exists(root->right, x);
        else
            return exists(root->left, x);
    }
    
    // Preorder traversal of elements and for each
    // element, check if its counterpart is present or not that
    // can make up the sum
    bool twoSum(TreeNode* curr, TreeNode* root, int k) {
        if(!curr)
            return false;
        
        // find the complementary number 
        // Each number can be used only once so if k = 2 * curr->val,
        // then we doing a BST check will return true since this same curr->val
        // will be present there, so we only allow a BST check if the counterpart
        // is != curr->val
        if((k - curr->val != curr->val) && exists(root, k - curr->val))
            return true;
        
        return twoSum(curr->left, root, k) ||
            twoSum(curr->right, root, k);    
    }
    
    bool findTarget(TreeNode* root, int k) {
        return twoSum(root, root, k);
    }
};
