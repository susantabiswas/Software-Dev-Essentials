/*
    124. Binary Tree Maximum Path Sum
    https://leetcode.com/problems/binary-tree-maximum-path-sum/
    
    We do postorder traversal and each time we return the max path in the subtree 
    to the subtree root. At root we update the global max. Now the max path can be
    either left, right, left+curr+right, curr. 
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
    int findMaxSum(TreeNode* root, long long& max_sum) {
        if(!root)
            return numeric_limits<int> :: min();
        
        long long left = findMaxSum(root->left, max_sum);
        long long right = findMaxSum(root->right, max_sum);

        // find the max amongst the left path, right path and curr node only
        long long left_curr_right_max = max({left + root->val, (long long)root->val,
                             right + root->val});
        // now find the max with the combined left + curr + right path sum
        max_sum = max({left_curr_right_max, left + root->val + right,
                      max_sum});
        
        return left_curr_right_max;
    }
    
    int maxPathSum(TreeNode* root) {
        long long max_sum = numeric_limits<int> :: min();
        findMaxSum(root, max_sum);
        return max_sum;
    }
};
