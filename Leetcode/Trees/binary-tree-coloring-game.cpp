/*
    https://leetcode.com/problems/binary-tree-coloring-game/
    
    Idea is to find the total nodes in the left, right and before node x. Then the second player can just
    choose to color the branch with majority nodes(> N/2). If such a node is there then he can win, otherwise not possible.
    
    TC: O(n)
    
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
    
    int postTraversal(TreeNode* root, int& x, bool& can_win, int n) {
        if(!root)
            return 0;
        
        int left = postTraversal(root->left, x, can_win, n);
        int right = postTraversal(root->right, x, can_win, n);
        
        // if the current node is the one chosen by first player
        if(root->val == x) {
            // In order for the second player to win, he needs to select a neighouring branch
            // which has more nodes than the combined nodes of other two neighbouring branches
            // +1 for including the current node
            int num_nodes_before = n - (1 + left + right);
            can_win = (num_nodes_before > left + right) || 
                        (left > num_nodes_before + right) ||
                        (right > num_nodes_before + left);
        }
        
        // total no. of nodes int the subtree with the current node as root 
        return left + right + 1;
    }
    
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        // whether second player can win or not
        bool can_win = false;
        postTraversal(root, x, can_win, n);
        return can_win;
    }
};
