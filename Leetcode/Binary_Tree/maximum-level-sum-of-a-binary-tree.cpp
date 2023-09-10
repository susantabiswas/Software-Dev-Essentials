/*
    https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/
    
    TC: O(n)
    SC: O(n), in worst case last level can have 2^h nodes ~ (n + 1) / 2
    O((n+1)/2) ~ O(n)
    
    Iterate the tree using BFS and track the sum of each level.
    At the end of each level, check if that level's sum is the new max
*/
class Solution {
public:
    int maxLevelSum(TreeNode* root) {
        int max_sum = INT_MIN, max_level = -1;
        queue<TreeNode*> q;
        
        q.emplace(root);
        int level = 1;
        int level_nodes = q.size();
        int level_sum = 0;
        
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            --level_nodes;
            level_sum += curr->val;
            
            if(curr->left)
                q.emplace(curr->left);
            if(curr->right)
                q.emplace(curr->right);
            
            // end of level
            if(level_nodes == 0) {
                // if current level's sum is max
                if(level_sum > max_sum) {
                    max_sum = level_sum;
                    max_level = level;
                }
                ++level;
                level_nodes = q.size();
                level_sum = 0;
            }
        }
        return max_level;
    }
};
