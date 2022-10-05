/*
    https://leetcode.com/problems/add-one-row-to-tree/
    
    TC: O(N)
    SC: O(N)
    
    Idea is to use BFS to traverse the tree level by level. We track the current
    traversal depth. At level == depth-1, we add the new nodes one by one. 
    For each curr tree node, save its children and make two new val nodes
    as the new children. Then for the new left val node, make the original left subtree 
    the left child and for the new right val node, make the original right subtree
    the right child.
    Once the level has been placed, stop the traversal.
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
    TreeNode* bfsSol(TreeNode* root, int val, int depth) {
        if(!root)
            return new TreeNode(val);
        
        // level to be placed is at root
        if(depth == 1) {
            TreeNode *node = new TreeNode(val);
            node->left = root;
            return node;
        }
        
        // Tracks whether the new level has been placed or not
        bool level_placed = false;
        
        queue<TreeNode*> q;
        if(root)
            q.emplace(root);
        
        int level_nodes = q.size();
        int level = 1;
        
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            --level_nodes;
            
            if(curr->left)
                q.emplace(curr->left);
            if(curr->right)
                q.emplace(curr->right);
            
            // if the current level is depth-1, then add the next level
            // of nodes with data = val
            if(level == depth - 1) {
                TreeNode* node1 = new TreeNode(val);
                TreeNode* node2 = new TreeNode(val);
                
                // make the left and right subtrees of current node the 
                //children of new val nodes
                node1->left = curr->left;
                node2->right = curr->right;
                
                // set the new val nodes as the subtree
                curr->left = node1;
                curr->right = node2;
                
                level_placed = true;
            }
            
            // end of level
            if(level_nodes == 0) {
                // Since new level has been placed, exit traversal
                if(level_placed)
                    break;
                level_nodes = q.size();
                ++level;
            }
        }
        return root;
    }
    
    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        return bfsSol(root, val, depth);
    }
};
