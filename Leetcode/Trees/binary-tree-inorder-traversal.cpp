/*
    94. Binary Tree Inorder Traversal
    https://leetcode.com/problems/binary-tree-inorder-traversal/
    
    Sol1:
        Using a stack, we start with the root element. Then we try going as much as left as 
        possible, then pop the last node and add to ans, then try going for its right subtree.

        TC: O(n)
        SC: O(n)
        
    Sol2: Morris Traversal
        We start with the root node. The idea here is to connect the last rightmost node of left
        subtree to current element, doing so will help getting back to the current node without the
        recursion stack. Once a node is reached and processed, again traversal happens for its previous nodes and this time we revert back the tree. So basically each node is visited twice.
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
    vector<int> inorderTraversal1(TreeNode* root) {
        vector<int> inorder;
        
        stack<TreeNode*> s;
        
        // current node being traversed
        TreeNode* curr = root;
        
        while(curr || !s.empty()) {
            // go as much left as possible
            while(curr) {
                s.push(curr);
                curr = curr->left;
            }
            
            // process current node
            curr = s.top();
            s.pop();
            inorder.emplace_back(curr->val);
            
            // go as much right as possible
            curr = curr->right;
        }
        
        return inorder;
    }
    
    // using Morris Threaded Binary tree 
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> inorder;
        TreeNode* curr = root;
        
        while(curr) {
            // if current node has left subtree
            if(curr->left) {
                // go to its rightmost node, if this is the first
                // time this node is being visited, then we just create a 
                // link from rightmost node to current, otherwise we break the exisiting 
                // link and revert back the rightmost leaf node
                TreeNode* right_ptr = curr->left;
                while(right_ptr->right && right_ptr->right != curr) 
                    right_ptr = right_ptr->right;
                
                // first time 
                if(right_ptr->right == nullptr) {
                    right_ptr->right = curr;
                    curr = curr->left;
                }
                // current node is being visited for the second time,
                // this time it should be added to traversal order
                else {
                    // revert back
                    right_ptr->right = nullptr;
                    // add the current node
                    inorder.emplace_back(curr->val);
                    // go right
                    curr = curr->right;
                }
            }
            // process current node and go to right subtree
            else {
                inorder.emplace_back(curr->val);
                // go right
                curr = curr->right;
            }
            
        }
        
        return inorder;
    }
};
