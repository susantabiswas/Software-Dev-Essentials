/*
    https://leetcode.com/explore/featured/card/30-day-leetcoding-challenge/532/week-5/3315/
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
    bool checkSequence(TreeNode* root, vector<int>& arr, int curr) {
        if(!root)
            return false;
        // if the sequence has finished, but leaf has not reached
        if(curr == arr.size())
            return false;
        // check if current node value not match the value in sequence
        if(root->val != arr[curr])
            return false;
        
        // if current node is a leaf node and it is the last char
        if(!root->left && !root->right && root->val == arr[curr] && curr == arr.size()-1)
            return true;
        
        return checkSequence(root->left, arr, curr+1) || checkSequence(root->right, arr, curr+1);
    }
    
    bool isValidSequence(TreeNode* root, vector<int>& arr) {
        return checkSequence(root, arr, 0);
    }
};
