/*
    https://leetcode.com/problems/average-of-levels-in-binary-tree/
    
    TC: O(N)
    SC: O(N)
    
    Simple BFS to track the nodes per level and find their avg.
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
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> avg;
        long sum = 0, n_nodes = 0;
        queue<TreeNode*> q;
        q.emplace(root);
        
        int level_nodes = q.size();
        
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            --level_nodes;
            
            // process the current node
            sum += curr->val;
            ++n_nodes;
            
            // add the child nodes
            if(curr->left)
                q.emplace(curr->left);
            if(curr->right)
                q.emplace(curr->right);
            
            // end of level
            if(level_nodes == 0) {
                level_nodes = q.size();
                avg.emplace_back((double)sum / n_nodes);
                
                // reset the level sum and node count for the next level
                sum = 0, n_nodes = 0;
            }
        }
        return avg;
    }
};
