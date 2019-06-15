/*
    145. Binary Tree Postorder Traversal
    https://leetcode.com/problems/binary-tree-postorder-traversal/submissions/
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
    vector<int> postorderTraversal(TreeNode* root) {
        if(!root)
            return vector<int>{};
        
        stack<TreeNode*> s;
        vector<int> postorder;
        
        TreeNode *curr = nullptr, *prev = nullptr;
        s.emplace(root);
        
        while(!s.empty()) {
            curr = s.top();
            
            // if current node is going down
            // either from left or right
            if(!prev || prev->left == curr || prev->right == curr) {
                if(curr->left)
                    s.emplace(curr->left);
                else if(curr->right)
                    s.emplace(curr->right);
            }
            // if current is a leaf node, add to traversal 
            else if(!curr->left && !curr->right) {
                postorder.emplace_back(curr->val);
                s.pop();
            }
            // if current is going up from left subtree
            else if(prev == curr->left) {
                // go to right subtree if it exists
                if(curr->right) {
                    s.emplace(curr->right);
                }
                else {
                    postorder.emplace_back(curr->val);
                    s.pop();
                }
            }
            // if current is going up from right subtree
            else if(prev == curr->right) {
                postorder.emplace_back(curr->val);
                s.pop();
            }
            
            prev = curr;
        }
        
        
        return postorder;
    }
};
