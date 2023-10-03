/*
    https://leetcode.com/problems/leaf-similar-trees/
    
    Idea is to find the order of leaf nodes of 1st tree and then do a 
    preorder traversal of 2nd tree and check if the leaves of 2nd tree
    are also in the same order.
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
    // Finds the leaves in sequential order
    void findLeaves(TreeNode *root, vector<int> &leaves) {
        if(root) {
            // if current is a leaf node
            if(!root->left && !root->right) {
                leaves.emplace_back(root->val);
                return;
            }
            
            findLeaves(root->left, leaves);
            findLeaves(root->right, leaves);
        }    
    }
    
    // checks if the leaves of the current tree match the
    // given order of leaves
    bool compareLeaves(TreeNode *root, vector<int> &leaves, int &curr) {
        if(root) {
            // if leaf node
            if(!root->left && !root->right) {
                return curr < leaves.size() && 
                    root->val == leaves[curr++];
            }
            return compareLeaves(root->left, leaves, curr)
                && compareLeaves(root->right, leaves, curr);
        }
        return true;    
    }
    
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        /// find the leaf nodes of tree 1
        vector<int> leaves;
        findLeaves(root1, leaves);
        
        int curr = 0;
        // check if the leaves of tree 2 are the same as that of tree 1
        return compareLeaves(root2, leaves, curr) 
                && curr == leaves.size(); // if n_leaves_tree1 > n_leaves_tree2
    }
};


////////////////////// SOLUTION 2: Easy
class Solution {
public:
    void leafSequence(TreeNode* root, string& seq) {
        if(root) {
            if(!root->left && !root->right)
                seq += to_string(root->val) + ',';
            
            leafSequence(root->left, seq);
            leafSequence(root->right, seq);
        }    
    }
    
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        string seq1, seq2;
        leafSequence(root1, seq1);
        leafSequence(root2, seq2);
        return seq1 == seq2;
    }
};
