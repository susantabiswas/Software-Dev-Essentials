/*
    https://leetcode.com/problems/path-sum-iii/
    
    TC: O(N)
    SC: O(N), worst case: skewed tree
    
    Since the paths to check for start from top and continue from parent to
    child subtrees. So each path from parent A to a node in some nested subchild 
    B is basically a path which can have sum equivalent to req. sum. We can look
    at the problem as finding a subarray sum in an array which matches the given sum.
    SO to do that we start tracking all the sums seen during traversal from
    top to bottom and at each node also check if we found paths matching the req. sum.
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
    void findPaths(TreeNode* root, int sum, int path,
                   int &paths, unordered_map<int, int>& path_sums) {
        if(root) {
            // add current node to path
            path += root->val;
            // check the number of paths found with req. sum
            paths += path_sums[path - sum];
            // Add the current path to the 
            ++path_sums[path];
        
            findPaths(root->left, sum, path, paths, path_sums);
            findPaths(root->right, sum, path, paths, path_sums);
            // remove the current path from visited paths
            --path_sums[path];
        }    
    }
    
    int pathSum(TreeNode* root, int sum) {
        int paths = 0;
        // <path sum, number of such paths>
        unordered_map<int, int> path_sums;
        // 0 node path
        path_sums[0] += 1;
        findPaths(root, sum, 0, paths, path_sums);
        
        return paths;
    }
};
