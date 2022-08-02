/*
    https://leetcode.com/problems/sum-of-nodes-with-even-valued-grandparent/
    
    Idea is to do DFS and send the parent and grandparent along the dfs call. For the next child node
    current node becomes its parent and its parent becomes the grandparent.
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
    void findSum(TreeNode *root, TreeNode *parent, 
                 TreeNode *grandparent, long &sum) {
        if(!root)
            return;
        
        // check if the grandparent was even or not
        if(grandparent && !(grandparent->val % 2))
            sum += root->val;
        
        findSum(root->left, root, parent, sum);
        findSum(root->right, root, parent, sum);
    }
    
    int sumEvenGrandparent(TreeNode* root) {
        long sum = 0;
        findSum(root, nullptr, nullptr, sum);
        return sum;
    }
};
