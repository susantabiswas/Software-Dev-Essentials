/*
    https://leetcode.com/problems/deepest-leaves-sum/submissions/
    
    Idea is to use BFS, where for each level we find the sum and when
    the BFS ends, we end up with sum of last level.
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
    int deepestLeavesSum(TreeNode* root) {
        // We use to keep track of sum of levels
        queue<TreeNode*> q;
        q.emplace(root);
        
        // Tracks level sum, no. of nodes in level
        long level_sum = 0, n_level = 0;
        n_level = q.size();
        
        // after BFS ends, we will have the sum of the last level which
        // is the deepest level
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            --n_level;
            level_sum += curr->val;
            
            if(curr->left)
                q.emplace(curr->left);
            if(curr->right)
                q.emplace(curr->right);
            
            if(n_level == 0) {
                n_level = q.size();
                // last level reached
                if(q.empty())
                    break;
                // reset level sum
                level_sum = 0;
            }
        }
        
        return level_sum;
    }
};
