/*
    https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/submissions/
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
    // SOLUTION 1: BOTTOM - UP 
    // We try to find the smallest and largest subchild for ecah node
    // once it is found, we find the abs difference of those with the
    // current node value since max value is when difference between max
    // and min value is computed. So since there is no surety whether the
    // current node value is going to be min or max. Once we update the 
    // ans, then update the max and min values using the current node 
    // value and pass it to its parent.
    
    // TC: O(N)
    void findMaxDiff(TreeNode *root, int &ans,
                    int &max_child, int &min_child) {
        // if leaf node
        if(!root->left && !root->right) {
            max_child = min_child = root->val;
        }
        else {
            // To find the max and min nodes in the children subtrees
            int max_subchild = INT_MIN, min_subchild = INT_MAX;
            if(root->left)
                findMaxDiff(root->left, ans,
                       max_subchild, min_subchild);
            // update the max and min till current node
            // with the children subtree values
            max_child = max(max_child, max_subchild);
            min_child = min(min_child, min_subchild);
            // reset the values again for the right subtree
            max_subchild = INT_MIN, min_subchild = INT_MAX;
            if(root->right)
                findMaxDiff(root->right, ans,
                       max_subchild, min_subchild);
            
            max_child = max({max_child, max_subchild});
            min_child = min({min_child, min_subchild});
            // check if a new max ans is found
            ans = max({ans, abs(root->val - min_child),
                      abs(root->val - max_child)});
            // update the max and min subtree node values
            // for its parents
            max_child = max({max_child, root->val});
            min_child = min({min_child, root->val});
        }
    }
    
    // SOLUTION 2: Top down
    /*
        TC: O(N)
        
        Here we try to pass down the min and max values for each
        path all the way till the last node i.e leaf node. At the 
        end of the path we compute abs(min - max) and then return that value.
        Since all the leaf paths will return the |max - min| we just
        need to find the max out of all those.
    */
    int findMaxDiffTop(TreeNode *root,
                    int max_child, int min_child) {
        // End of path
        if(!root)
            return max_child - min_child;
        // update the min and max for the path with the current value
        max_child = max(max_child, root->val);
        min_child = min(min_child, root->val);
        
        return max(findMaxDiffTop(root->left, max_child, min_child),
                  findMaxDiffTop(root->right, max_child, min_child));
    }
    
    int maxAncestorDiff(TreeNode* root) {
        int ans = INT_MIN, max_child = INT_MIN, min_child = INT_MAX;
        //findMaxDiff(root, ans, max_child, min_child);
        //return ans;
        
        return findMaxDiffTop(root, max_child, min_child);
    }
};
