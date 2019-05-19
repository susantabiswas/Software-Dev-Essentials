/*
    113. Path Sum II
    https://leetcode.com/problems/path-sum-ii/
    
    Solved using DFS.
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
    
    // recursive solution
    void findPathSumRec(TreeNode* root, int sum, vector<int>& path, 
                     vector<vector<int>>& result) {
        // when leaf's child is encountered
        if(root == nullptr) {
            return;
        }

        // add current node to path
        path.emplace_back(root->val);
        // subtract current node value from total sum
        sum -= root->val;
        
        // if the current path contains the sum
        if(sum == 0 && !root->left && !root->right) {
            result.emplace_back(path);
            return;
        }
            
        findPathSumRec(root->left, sum, path, result);
        if(root->left)
            path.pop_back();
        
        findPathSumRec(root->right, sum, path, result);
        if(root->right)
            path.pop_back();
        
        return;
    }
    
    // Iterative solution
    void findPathSumIter(TreeNode* root, int sum, vector<vector<int>>& result) {
        if(!root)
            return;
        
        // for keeping track of current node and sum
        stack<pair<TreeNode*, int> > s;
        // for keeping track of path
        stack<vector<int>> path_s;
        TreeNode* curr = root;
        vector<int> path;
        
        // We do a preorder traversal 
        while(curr || !s.empty()) {
            // go left
            while(curr) {
                // update path sum and path and add to stacks
                sum = sum - curr->val;
                path.emplace_back(curr->val);
                s.emplace(make_pair(curr, sum));
                
                // check if the path sum is zero 
                if(sum == 0 && !curr->left && !curr->right)
                    result.emplace_back(path);
                
                path_s.emplace(path);
                
                curr = curr->left;
            }
            
            // take out the last node and go right
            curr = s.top().first;
            sum = s.top().second;
            path = path_s.top();
            s.pop();
            path_s.pop();
            
            curr = curr->right;
        }
    }
    
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int> > result;
        vector<int> path;
        
        findPathSumRec(root, sum, path, result);
        //findPathSumIter(root, sum, result);
        return result;
    }
};
