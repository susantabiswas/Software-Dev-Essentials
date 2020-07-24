/*
    https://leetcode.com/problems/distribute-coins-in-binary-tree/
    
    The idea is track the net flow of coins from child nodes to parent. Since there
    are exactly N coins for N nodes, that means for any coin with surplus/deficit coins
    it will involve movement of coins in its surrounding via itself.
    So we do post order traversal, we get the net coins from left and right nodes. All
    the net coins (+,-) needs to be moved so it will be equal to |Sum of net coins from left + right|.
    
    Now we convey the net resultant coin till current to the parent, so that it can move in or out coins
    from itself.
    TC: O(N)
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
    int minCoinMoves(TreeNode* root, int& moves) {
        if(!root)
            return 0;
        // Find the Net coin amount from children 
        int net_coins_left = minCoinMoves(root->left, moves);
        int net_coins_right = minCoinMoves(root->right, moves);
        // Now if we get any net coins value from left or right, that
        // means we need to moves those coins through the current node
        // Net flow : -ve, move that many coins to the child node
        // Net flow: +ve, We need to move those coins out from the child node to the upper parent
        moves += abs(net_coins_left) + abs(net_coins_right);
        // convey the net resultant coins till current node to upper parent
        // -1: Current node requires 1 coin
        return net_coins_left + net_coins_right + root->val - 1;
    }
    
    int distributeCoins(TreeNode* root) {
        int moves = 0;
        minCoinMoves(root, moves);
        return moves;
    }
};
