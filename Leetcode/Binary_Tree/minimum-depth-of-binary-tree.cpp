/*
    https://leetcode.com/problems/minimum-depth-of-binary-tree/submissions/
    
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
    int minDepth(TreeNode* root) {
        if(!root)
            return 0;
        // when current is a leaf node
        // then only the path becomes valid
        if(!root->left && !root->right)
            return 1;
        
        // Since only leaf node paths are valid, so if the current node has a NULL
        // child, it gets 0 as depth which is wrong. To discourage such behavior we assign
        // the depth as INF in such cases
        int left = root->left ? minDepth(root->left) : INT_MAX;
        int right = root->right ? minDepth(root->right) : INT_MAX;
        return 1 + min(left, right);
    }
};
