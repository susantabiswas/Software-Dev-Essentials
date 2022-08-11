/*
    https://leetcode.com/problems/binary-tree-preorder-traversal/
    
    Solution 1: Morris Traversal
    
    Idea of morris traversal is to set links to inorder predecessor to their successor.
    This is what is naturally achieved with a recursion.
    For each node, we first find out its inorder predecessor and set this right link to current node.
    This way we can reach the current node again via that link later on.
    
    Now we visit each node twice, so to check which time is it, we can look at the predecessor's
    right link. If it is already set, we have come to the node for the 2nd time.
    Since this is preorder we process curr node for the 1st when we visit it, for inorder we would
    have processed it in the 2nd time.
    
    Now if there is no left child, process it and go to the right node.
    
    TC: O(N)
    SC: O(1)
    
    SOLUTION 2: Stack
    
    Idea is to use stack to mimic the recusion stack, we go left as usual while saving the 
    nodes on the way. When we hit a null node, just pop the last node from stack and then from there 
    take a right turn. 
    In case we are again null, then pop back to last node and so on.
    TC: O(N)
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
    // SOLUTION 1: Morris Traversal (Threaded Binary Tree)
    // TC: O(N)
    // SC: O(1)
    vector<int> morrisTraversal(TreeNode* root) {
        TreeNode* curr = root;
        vector<int> order;
        
        while(curr) {
            // Check the inorder predecessor
            if(curr->left) {
                TreeNode* inorder_pred = curr->left;
                // Go to the inorder predecessor
                while(inorder_pred->right && inorder_pred->right != curr)
                    inorder_pred = inorder_pred->right;
                
                // If the current node is visited for the 1st time,
                // set inorder predecessor's right link to current node
                if(inorder_pred->right == nullptr) {
                    inorder_pred->right = curr;
                    // Since preorder and curr is visited for the 1st time
                    order.emplace_back(curr->val);
                    curr = curr->left;
                }
                // Curr node is visited for the 2nd time via inorder predecessor,
                // remove the link and go to the right child
                else {
                    inorder_pred->right = nullptr;
                    curr = curr->right;
                }
            }
            // No left child, so process curr and move to right
            else {
                order.emplace_back(curr->val);
                curr = curr->right;
            }
        }
        
        return order;
    }
    
    // SOLUTION 2: Stack
    // TC: O(N)
    // SC: O(N)
    vector<int> stackSol(TreeNode* root) {
        stack<TreeNode*> s;
        TreeNode* curr = root;
        vector<int> order;
        
        while(curr || !s.empty()) {
            // Go as much left as possible
            while(curr) {
                order.emplace_back(curr->val);
                s.emplace(curr);
                curr = curr->left;
            }
            // Now we have hit a null node, so step back to the 
            // last node
            curr = s.top();
            s.pop();
            // Explore the right subtree
            curr = curr->right;
        }
        return order;
    }
    
    vector<int> preorderTraversal(TreeNode* root) {
        // return morrisTraversal(root);
        return stackSol(root);
    }
};
