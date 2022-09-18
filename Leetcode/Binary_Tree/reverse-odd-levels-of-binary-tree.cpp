/*
    https://leetcode.com/problems/reverse-odd-levels-of-binary-tree/
    
    TC: O(N)
    SC: O(2^h), worst case leaf level will have the max no. of nodes
    h = log(n)
    
    Idea is to use BFS traversal and keep track of each level. For a current level,
    we save its level nodes, if the level is odd, then reverse only the node value
    instead of changing any of the parent pointers.
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
    TreeNode* bfsSol(TreeNode* root) {
        queue<TreeNode*> q;
        // Saves the nodes of a level
        vector<TreeNode*> level_nodes;
        if(root)
            q.emplace(root);
        
        int level = 0;
        // tracks the no. of remaining nodes in a level
        int n_level_nodes = q.size();
        
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            level_nodes.emplace_back(curr);
            --n_level_nodes;
            
            // add its children
            if(curr->left)
                q.emplace(curr->left);
            if(curr->right)
                q.emplace(curr->right);
            
            // end of level
            if(n_level_nodes == 0) {
                n_level_nodes = q.size();
                // reverse the nodes in the current level if the level is odd
                if(level % 2) {
                    for(int start = 0, end = level_nodes.size() - 1;
                        start < end; start++, end--) {
                        swap(level_nodes[start]->val, level_nodes[end]->val);
                    }
                }
                // remove current level nodes
                level_nodes.clear();
                ++level;
            }
        }
        return root;
    }
    
    TreeNode* reverseOddLevels(TreeNode* root) {
        return bfsSol(root);
    }
};
