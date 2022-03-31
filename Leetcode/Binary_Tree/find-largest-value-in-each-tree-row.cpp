/*
    https://leetcode.com/problems/find-largest-value-in-each-tree-row/
    
    Sol1
    TC : O(N * logL), LogL: Lookup in sorted hash table
    SC: O(N)
    Using DFS
    Idea is to use a hash table that tracks the largest for each of the 
    levels in DFS, then in DFS we also pass the level info to track the level
    max in hash table.
    
    Sol2
    TC: O(N)
    SC: O(D), D=Diameter of tree (Excluding the result storage)
    
    Use BFS to traverse level wise and for each level keep track of the 
    max element.
    
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
    void DFS(TreeNode* root, int level, map<int, int>& level_largest) {
        if(!root) 
            return;
        // If this is the 1st val in the curr level
        if(!level_largest.count(level))
            level_largest[level] = root->val;
        // Compare the curr value against the max found in the current level
        level_largest[level] = max(level_largest[level], root->val);
        
        DFS(root->left, level + 1, level_largest);
        DFS(root->right, level + 1, level_largest);
    }
    
    // Sol1: Using DFS
    // TC : O(N * logL), LogL: Lookup in sorted hash table
    // SC: O(N)
    vector<int> DFSSol(TreeNode* root) {
        // Map of <level, Largest in curr level> 
        map<int, int> level_largest;
        DFS(root, 0, level_largest);
    
        vector<int> result;
        for(auto largest: level_largest)
            result.emplace_back(largest.second);
        
        return result;
    }
    
    // Sol2 : BFS
    // TC: O(N)
    // SC: O(D), D = Diameter
    vector<int> BFSSol(TreeNode* root) {
        vector<int> largest;
        
        if(!root)
            return largest;
        
        // Use BFS to traverse row wise and track the largest
        queue<TreeNode*> q;
        q.emplace(root);
        // Track curr level and no. of nodes 
        int level = 0, n_nodes = q.size();
        int row_largest = INT_MIN;
        
        while(!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();
            --n_nodes;
            
            row_largest = max(row_largest, curr->val);
            if(curr->left)
                q.emplace(curr->left);
            if(curr->right)
                q.emplace(curr->right);
            
            // end of level
            if(n_nodes == 0) {
                ++level;
                largest.emplace_back(row_largest);
                // reset the value according to the next level
                n_nodes = q.size();
                row_largest = INT_MIN;
            }
        }
        
        return largest;
    }
    
    vector<int> largestValues(TreeNode* root) {
        // return BFSSol(root);
        return DFSSol(root);
    }
};
