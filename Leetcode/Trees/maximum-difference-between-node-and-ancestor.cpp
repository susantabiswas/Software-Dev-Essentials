/*
    1026. Maximum Difference Between Node and Ancestor
    https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/submissions/
    
    Bottom up:
        For this we just need to maximize the diff of root and child value. We do postorder traversal.
        So for each root of a subtree we return a pair of max and min value in the subtree rooted
        at current node. Then we just find the diff with current root, we check if that is the max diff 
        value obtained so far. Then update the ma and min value ending at current subtree for its parent.
    Top down:
        We pass min and max value from top and once leaf is reached we return the max-min, also
        while returning we return the max of left and right subtree calls.
    
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
    // bottom up
    pair<int, int> findMaxDiff(TreeNode* root, int& max_diff) {
        if(!root)
            return make_pair(INT_MIN, INT_MAX);
        
        pair<int, int> left = findMaxDiff(root->left, max_diff);
        pair<int, int> right = findMaxDiff(root->right, max_diff);
        
        // if current is not leaf node 
        // find the diff of current root with max and min of left and right sides
        if(root->left || root->right) {
            int diff = INT_MIN;
            if(left.first != INT_MIN)
                diff = max(diff, abs(root->val - left.first));
                           
            if(left.second != INT_MAX)
                diff = max(diff, abs(root->val - left.second));
           
            if(right.first != INT_MIN)
                diff = max(diff, abs(root->val - right.first));
                           
            if(right.second != INT_MAX)
                diff = max(diff, abs(root->val - right.second));
            
           max_diff = max(max_diff, diff);
        }
        
        // update the min and max value node in current tree which will
        // be given to its parent
        int min_node = min({left.second, right.second, root->val});
        int max_node = max({left.first, right.first, root->val});
        
        // return the max and min values in the current subtree to its parent
        return make_pair(max_node, min_node);
    }
    
    // top down:
    int findMaxDiffTopDown(TreeNode* root, int l, int h) {
        return !root ? h - l : max(findMaxDiffTopDown(root->left, min(root->val, l), max(root->val, h)),
                                  findMaxDiffTopDown(root->right, min(root->val, l), max(root->val, h)));
    }
    
    int maxAncestorDiff(TreeNode* root) {
        int max_diff = numeric_limits<int> :: min();
        
    //    pair<int, int> max_min;
        //findMaxDiff(root, max_diff);
        //return max_diff;
        int l = numeric_limits<int> :: max();
        int h = numeric_limits<int> :: min();
        return findMaxDiffTopDown(root, l, h);
    }
};
