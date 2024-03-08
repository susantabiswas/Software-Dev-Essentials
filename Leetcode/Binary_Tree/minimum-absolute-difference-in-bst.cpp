/*
    https://leetcode.com/problems/minimum-absolute-difference-in-bst/
    
    TC: O(n)
    SC: O(n)
    
    The min abs diff can be found between two closest numbers or consecutive numbers
    in the sorted order of elements.
    
    We can perform an inorder traversal of elements and then track the min diff between two
    consecutive pairs.
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
    int getMinimumDifference(TreeNode* root) {
        TreeNode* curr = root, *prev = nullptr;
        int min_diff = INT_MAX;
        
        stack<TreeNode*> s;
        
        while(curr || !s.empty()) {
            while(curr) {
                s.push(curr);
                curr = curr->left;
            }
            
            curr = s.top();
            s.pop();
            
            if(prev)
                min_diff = min(min_diff, abs(curr->val - prev->val));
            
            prev = curr;
            
            curr = curr->right;
        }
        return min_diff;
    }
};
