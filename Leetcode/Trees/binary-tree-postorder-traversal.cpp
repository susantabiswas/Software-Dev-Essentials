/*
    145. Binary Tree Postorder Traversal
    https://leetcode.com/problems/binary-tree-postorder-traversal/
*/


/////////////////////////// Clean Solution 
/*
    Core Idea: 
    Post order can be derived from preorder where we take Right and then Left turn, and then reversing the entire order of elements.

    Post Order:
        1. Do preorder like movement with Right and then Left
        2. Reverse the order of elements

    Now the above idea can be implemented via 2 ways:
    1. Stack solution
    2. Threaded Binary Tree / Morris Traversal
*/

////// Stack Solution
vector<int> sol1(TreeNode* root) {
    vector<int> order;
    
    stack<TreeNode*> s;
    TreeNode* curr = root;
    
    while(!s.empty() || curr) {
        
        // go right first
        while(curr) {
            order.push_back(curr->val);
            s.push(curr);
            curr = curr->right;
        } 
        
        curr = s.top();
        s.pop();
        
        // now go left
        curr = curr->left;
        
    }
    
    reverse(order.begin(), order.end());
    return order;
}
//////////////////////////////////////////////////////

/**
    SOLUTION - Pretty bad
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
