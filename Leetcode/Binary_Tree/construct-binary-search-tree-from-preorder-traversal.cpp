/*
    https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/
    TC: O(N)
    
    Idea is to track the range of values that are allowed for a subtree.
    Since this is a BST, each branch is based on the range of values it can have.
    For root node it is [-INF, INF], for its left child it is [-INF, root->val - 1]
    and for its right child: [root->val + 1, INF] and so on.
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
    TreeNode* createBST(int &curr, int min_val, 
                        int max_val, vector<int>& preorder) {
        // If all the traversal nodes have been processed or
        // current traversal node's value doesnt lie in [min : max] value
        if(curr >= preorder.size() || preorder[curr] < min_val ||
            preorder[curr] > max_val)
            return nullptr;
        
        // create the current node
        TreeNode* root = new TreeNode(preorder[curr++]);
        root->left = createBST(curr, min_val, root->val-1, preorder);
        root->right = createBST(curr, root->val-1, max_val, preorder);
        
        return root;
    }
    
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        if(preorder.empty())
            return nullptr;
        int curr = 0;
        return createBST(curr, INT_MIN, INT_MAX, preorder);
    }
};
