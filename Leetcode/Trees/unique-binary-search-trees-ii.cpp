/*
    95. Unique Binary Search Trees II
    https://leetcode.com/problems/unique-binary-search-trees-ii/

    TC: O(n * Cn)
    SC: O(n * Cn)
    Cn = nth Catalan number

    Though the solution is the nth Catalan number, to compute that we end up computing
    Catalan number for each of 1...n. So n * Cn. Similarly we save n Catalan numbers.

    For each n, the time complexity due to the loops and picking each intermediate node as 
    root leads to a total of nth Catalan.

    The Catalan number grows asymptotically similar to 4^n/n^(3/2)
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
