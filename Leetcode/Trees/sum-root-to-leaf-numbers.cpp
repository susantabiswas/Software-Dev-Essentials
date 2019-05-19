/*
    129. Sum Root to Leaf Numbers
    https://leetcode.com/problems/sum-root-to-leaf-numbers/
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
    void findTotalSum(TreeNode* root, int& num, long long& sum) {
        if(!root)
            return;
        
        num = num * 10 + root->val;
        // if current is leaf node, add number
        if(!root->left && !root->right)
            sum += num;
        
        findTotalSum(root->left, num, sum);
        if(root->left)
            num = num / 10;
        
        findTotalSum(root->right, num, sum);
        if(root->right)
            num /= 10;
    }
    
    int sumNumbers(TreeNode* root) {
        long long sum = 0;
        int num = 0;
        findTotalSum(root, num, sum);
        
        return sum;
    }
};
