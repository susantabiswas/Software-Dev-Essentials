/*
    https://leetcode.com/problems/flip-equivalent-binary-trees/
    
    We traverse the two trees at the same time, each time exploring the 
    possibility of a flip. Eg traverse to left in tree1 and right in tree2,
    traverse to left in both tree1 and tree2.
    
    TC: O(min(n, m))
    SC: O(min(n, m))
    n = no. of nodes in tree1, m = no. of nodes in tree 2
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
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        // base case: When both nodes are null
        if(!root1 && !root2)
            return true;
        // base case: When only one node is null, then they are not flip equivalent
        if((!root1 && root2) || (root1 && !root2))
            return false;
        // if the current nodes don't match, then also not flip equi
        if(root1->val != root2->val)
            return false;
        
        // We recurse in all possible directions combo
        return (flipEquiv(root1->left, root2->left) && flipEquiv(root1->right, root2->right)) ||
            (flipEquiv(root1->left, root2->right) && flipEquiv(root1->right, root2->left));
    }
};
