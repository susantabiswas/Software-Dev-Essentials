/*
    https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/solution/
    
    We create the tree in preorder fashion. So each time the current index of preorder is used, 
    once a node is created we increment its index position. For the current preoder element, we 
    search for its position in inorder and recursively build the left and right subtrees around that
    index.
    
    TC: O(N^2), if the index positions of inorder is hashed, TC becomes O(N)
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
    TreeNode* buildBTree(vector<int>& preorder, vector<int>& inorder,
                        int &pre_idx, int inorder_start, int inorder_end) {
        if(inorder_start > inorder_end)
            return nullptr;
        // create the current node and recurse for its subtress
        TreeNode *root = new TreeNode(preorder[pre_idx]);
        // search for the position of preorder node in inorder
        int inorder_idx = inorder_start;
        for(int i = inorder_start; i <= inorder_end; i++)
            if(inorder[i] == preorder[pre_idx]) {
                inorder_idx = i;
                break;
            }
        
        ++pre_idx;
        // build the left and right subtree
        root->left = buildBTree(preorder, inorder, pre_idx, inorder_start, inorder_idx-1);
        root->right = buildBTree(preorder, inorder, pre_idx, inorder_idx+1, inorder_end);
        return root;
    }
    
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int pre_idx = 0, inorder_start = 0, inorder_end = inorder.size()-1;
        return buildBTree(preorder, inorder, 
                          pre_idx, inorder_start, inorder_end);
    }
};
