/*
    https://leetcode.com/problems/subtree-of-another-tree/

    SOLUTION 1
    We use BFS to look for the root mode of tree t. Once a node
    is found in s, we check if t is present as a subtree with that node as root.
    
    TC: O(NM), M: nodes in t, N: nodes in s

    SOLUTION 2: Hashing
    TC: O(M + N)
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
    // TC: O(N)
    bool isIdentical(TreeNode* root1, TreeNode* root2) {
        if(!root1 && !root2)
            return true;
        if(!root1 || !root2)
            return false;
        if(root1->val != root2->val)
            return false;
        return isIdentical(root1->left, root2->left) && 
                isIdentical(root1->right, root2->right);
    }
    
    bool isSubtree(TreeNode* s, TreeNode* t) {
        // Find the root node of subtree t in s
        // using BFS
        queue<TreeNode*> q;
        q.emplace(s);
        
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            // check if the tree t is a subtree
            if(curr->val == t->val && isIdentical(curr, t))
                return true;
            if(curr->left)
                q.emplace(curr->left);
            if(curr->right)
                q.emplace(curr->right);
        }
        return false;
    }
};

////////////////////////////////// SOLUTION 2 : HASHING
void postorder(TreeNode* root, string& tree_hash) {
        // There can be case where only one child is present, hence
        // we need to fill that null node position
        if(!root) {
            tree_hash += 'L';
            return;
        }
        
        // Use ',' to separate the nodes
        tree_hash += "," + to_string(root->val);
        
        postorder(root->left, tree_hash);
        postorder(root->right, tree_hash);
        
        tree_hash += '#';
    }
    
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        // find the hash
        string orig;
        postorder(root, orig);
        
        string subtree;
        postorder(subRoot, subtree);
        
        return orig.find(subtree) != string::npos;
    }
