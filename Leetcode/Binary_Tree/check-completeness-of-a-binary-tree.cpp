/*
    https://leetcode.com/problems/check-completeness-of-a-binary-tree/
    
    Idea is simple, we check for the cases which violate the completeness property.
    1. In a level, if a null node exists, then all the nodes following it should be null
        as well. We can't have non-null nodes afterwards.
    2. If we have seen a previous level with any null nodes and again we see any other level
        other than the last level with null nodes, then also it can't be a complete bin tree.
        
    Perform BFS of tree, track the level where the first null node is seen. For each
    level track whether a null node is seen or not. If seen already, then if we encounter one
    again, it can't be complete.
    
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
    bool isCompleteTree(TreeNode* root) {
        queue<TreeNode*> q;
        q.emplace(root);
        
        // level where a null node has been encountered or not so far
        int null_node_level = -1;
        // whether null nodes seen in the next level
        bool null_node_seen = false;
        int level_nodes = q.size(), level = 0;
        
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            
            // null node was found in the next level and now
            // a non null node is seen in the same next level
            if(curr->left && null_node_seen)
                return false;
            
            if(curr->left) 
                q.emplace(curr->left);    
            else
                null_node_seen = true;
            
            // null node was found in the next level and now
            // a non null node is seen in the same next level
            if(curr->right && null_node_seen)
                return false;
            
            if(curr->right) 
                q.emplace(curr->right);
            else
                null_node_seen = true;
            
            // end of level
            if(level_nodes == 0) {
                // if null node was found in the next level, check if there was any previous level
                // with null nodes. Also only applicable if the current level is
                // not the last one as last level will have the next level as null
                if(null_node_seen && null_node_level != -1 && !q.empty())
                    return false;
                
                level_nodes = q.size();
                ++level;
                
                // save the level where the null nodes were seen
                if(null_node_seen)
                    null_node_level = level;
                
                null_node_seen = false;
            }
        }
        return true;
    }
};
