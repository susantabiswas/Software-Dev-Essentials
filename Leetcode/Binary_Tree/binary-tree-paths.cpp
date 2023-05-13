/*
    https://leetcode.com/problems/binary-tree-paths/
    
    We do preorder traversal so that each time the current node is visited
    before its children. For each subsequent DFS call we also pass the nodes visited
    in the prder they were visited. When a leaf node is visited, we add the path
    covered so far to the final result.
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
    void preorder(TreeNode *root, string path, 
                  vector<string> &result) {
        // if NULL node
        if(!root)
            return;
        
        // add the current node to path
        // if a node is already present
        if(path.empty())
            path += to_string(root->val);
        else   
            path += "->" + to_string(root->val);
        
        // current node is a leaf, add the path
        if(!root->left && !root->right) {
            result.emplace_back(path);
            return;
        }
        
        preorder(root->left, path, result);
        preorder(root->right, path, result);
    }
    
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        preorder(root, "", result);
        return result;
    }
};
