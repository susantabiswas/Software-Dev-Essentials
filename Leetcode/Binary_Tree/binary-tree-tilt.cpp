/*
    https://leetcode.com/problems/binary-tree-tilt/
    
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
    int findTiltSum(TreeNode *root, 
                    int &tilt) {
        if(!root)
            return 0;
        int left = findTiltSum(root->left, tilt);
        int right = findTiltSum(root->right, tilt);
        
        // compute current tilt sum
        tilt += abs(left - right);
        return left + right + root->val;
    }
    
    int findTilt(TreeNode* root) {
        int tilt = 0;
        findTiltSum(root, tilt);
        return tilt;
    }
};
