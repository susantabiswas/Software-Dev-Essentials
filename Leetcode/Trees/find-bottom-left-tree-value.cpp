/*
    513. Find Bottom Left Tree Value
    https://leetcode.com/problems/find-bottom-left-tree-value/
    
    BFS:
        We use BFS. We use a var for storing the leftmost node.Before going for each level 
        traversal, we assign the first node of that level to this var.
        The final value of this var is the ans.
    DFS:
        We use DFS for going down the tree, as we go down, we keep track of current depth.
        Every time for the first time we reach a deeper level, we update the left most node.

    TC: O(n)
    SC: O(n)
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
    void findLeftMostDFS(TreeNode* root, TreeNode*& left_most, 
                        int& max_depth, int curr_depth) {
        if(!root)
            return;
        
        // recurse for left and right subtrees
        findLeftMostDFS(root->left, left_most, max_depth, curr_depth + 1);
        findLeftMostDFS(root->right, left_most, max_depth, curr_depth + 1);
        
        // update the left most node 
        if(curr_depth > max_depth) {
            left_most = root;
            max_depth = curr_depth;
        }
    }
    
    // We use BFS for finding the leftmost node
    void findLeftMostBFS(TreeNode* root, TreeNode*& left_most) {
        TreeNode* curr = nullptr;
        
        // for storing nodes of a level
        queue<TreeNode*> q;
        q.emplace(root);
        
        int num_nodes = q.size();

        while(!q.empty()) {
            curr = q.front();
            q.pop();
            --num_nodes;

            if(curr->left)
                q.emplace(curr->left);
            if(curr->right)
                q.emplace(curr->right);

            if(num_nodes == 0) {
                num_nodes = q.size();

                // each time before traversing the current level,
                // we assign the leftmost node of current level to left_most
                if(num_nodes != 0) {
                    left_most = q.front();
                }
            }	
        }
    }

    int findBottomLeftValue(TreeNode* root) {
        TreeNode* left_most = nullptr;
        // the initial value for leftmost node
        left_most = root;

        int max_depth = 0;
        //findLeftMostBFS(root, left_most);
        findLeftMostDFS(root, left_most, max_depth, 0);
        return left_most->val;
    }
};
