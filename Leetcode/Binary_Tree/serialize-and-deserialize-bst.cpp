/*
    https://leetcode.com/problems/serialize-and-deserialize-bst/submissions/
    
    Encoding: TC: O(N)
    We use the preorder traversal data.
    
    Decoding: TC: O(nlogn)
    We use the node values from preorder traversal and insert one node at
    a time to the BST. Since we use preorder data we will be pushing nodes
	as they appeared in the original tree.
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
class Codec {
public:
    void preOrder(TreeNode *root, string &traversal) {
        if(root) {
            traversal = traversal + '#' + to_string(root->val);
            preOrder(root->left, traversal);
            preOrder(root->right, traversal);
        }
    }
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        // we store the preorder traversal for encoding
        string traversal;
        preOrder(root, traversal);
        return traversal;
    }
    
    // Creates a BST from enocoded string data
    TreeNode *createBST(TreeNode *root, int data) {
        // if leaf node
        if(!root)
            return new TreeNode(data);
        if(data < root->val)
            root->left = createBST(root->left, data);
        else
            root->right = createBST(root->right, data);
        return root;
    }
    
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        TreeNode *root = nullptr;
        istringstream ss(data);
        string token;
        
        while(getline(ss, token, '#')) {
            if(token.empty() == false)
              root = createBST(root, stoi(token));
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
