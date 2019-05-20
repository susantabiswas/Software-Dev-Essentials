/*
    979. Distribute Coins in Binary Tree
    https://leetcode.com/problems/distribute-coins-in-binary-tree/
    
    The idea is :
    For each node which has 0 coins: we need atleast 1 move from its parent, for nodes with extra coins, we need those excess coins to be moved to parent.
    So the resultant excess coins at current: 
    excess_left + excess_right + curr root coins - 1
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
    
    int findMovesReq(TreeNode* root, int& moves_req) {
        if(!root)
            return 0;

        int left_excess = findMovesReq(root->left, moves_req);
        int right_excess = findMovesReq(root->right, moves_req);

        // For this subtree, the no. of excess coins at this root 
        // decides the no. of moves req for moving them
        moves_req += abs(left_excess) + abs(right_excess);

        // the excess coins at the current root will be the excess number for its parent
        //for leaf node, excess will be -1
        return root->val + left_excess + right_excess - 1;
    }

    int distributeCoins(TreeNode* root) {
        int moves_req = 0;
        findMovesReq(root, moves_req);

        return moves_req;
    }
};
