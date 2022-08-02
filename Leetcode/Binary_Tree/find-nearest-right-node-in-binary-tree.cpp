/*
    https://leetcode.com/problems/find-nearest-right-node-in-binary-tree/
    
    Idea is to perform BFS to iterate through the tree level by level.
    In a given level if the target node is found, then set the flag tracking that to true.
    Now the next node in the same level will see that the flag is set and return itself.
    
    If we reach end of level without finding a right node, exit the process.
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
    TreeNode* bfsSol(TreeNode* root, TreeNode* u) {
        if(!root)
            return nullptr;
        
        // Tracks whether target node is found or not in current level
        bool node_found = false;
        queue<TreeNode*> q;
        q.emplace(root);
        int level_nodes = q.size();
        
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            --level_nodes;
            
            // This is the 1st node after the target node was found
            if(node_found)
                return curr;
            
            // Node found in the current level
            if(curr == u)
                node_found = true;
            
            // Add child nodes 
            if(curr->left)
                q.emplace(curr->left);
            if(curr->right)
                q.emplace(curr->right);
            
            // End of level
            if(level_nodes == 0) {
                // End of level and nearest right node not found
                if(node_found)
                    return nullptr;
                level_nodes = q.size();
            }
            
        }
        return nullptr;
    }
    
    TreeNode* findNearestRightNode(TreeNode* root, TreeNode* u) {
        return bfsSol(root, u);
    }
};
