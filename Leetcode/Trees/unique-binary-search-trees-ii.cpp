/*
    95. Unique Binary Search Trees II
    https://leetcode.com/problems/unique-binary-search-trees-ii/
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
    vector<TreeNode*> createTree(int start, int end) {
        // base case
        if(end < start)
            return vector<TreeNode*>(1, nullptr);

        vector<TreeNode*> ans;
        // for current interval each number is taken as root once
        for(int i = start; i <= end; i++) {
            vector<TreeNode*> left_subtree, right_subtree;
            // recurse for left and right subtrees
            left_subtree = createTree(start, i-1);
            right_subtree = createTree(i+1, end);

            for(int j = 0; j < left_subtree.size(); j++) {
                for(int k = 0; k < right_subtree.size(); k++) {
                    // create the root 
                    TreeNode* root = new TreeNode(i);
                    root->left = left_subtree[j];
                    root->right = right_subtree[k];
                    ans.emplace_back(root);
                }
            }

        }

        return ans;
    }

    vector<TreeNode*> generateTrees(int n) {
        if(n <= 0)
            return vector<TreeNode*>{};
        return createTree(1, n);
        
    }
};
