/*
    99. Recover Binary Search Tree
    https://leetcode.com/problems/recover-binary-search-tree/

    We do inorder traversal of tree and find the anamoly nodes in the order.
    There can be two cases:
    1.When the two nodes are adjacent
    2.When the two nodes are not adjacent

    We use three vars. which gets the value as soon as we get the anamolies.
    For the first time when we get the anamoly, we set the first and second vars, for the third
    time we set the second node in anamoly as the third var.

    TC: O(n)
    SC: O(n)
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
    
    void recoverTree(TreeNode* root) {
        TreeNode *first = nullptr, *second = nullptr, *third = nullptr;
        TreeNode* prev = nullptr;

        stack<TreeNode*> s;
        TreeNode* curr = root;

        while(curr || !s.empty()) {
            while(curr) {
                s.emplace(curr);
                curr = curr->left;
            }
            
            curr = s.top();
            s.pop();

            // when anamoly is detected
            if(prev && prev->val >= curr->val) {
                if (!first) {
                    first = prev;
                    second = curr;
                }
                else {
                    third = curr;
                }
            }

            prev = curr;
            curr = curr->right;
        }
        
        // swap changes
        
        // when adjacent nodes have been swapped
        if(third == nullptr) {
            int t = first->val;
            first->val = second->val;
            second->val = t;
        }
        // when swapped nodes are not adjacent
        else {
            int t = first->val;
            first->val = third->val;
            third->val = t;
        }
    }
};
