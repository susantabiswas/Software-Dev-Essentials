/*
    https://leetcode.com/problems/serialize-and-deserialize-bst/submissions/

    SOLUTION 1:
    TC: O(n) for both the operations

    SOLUTION 2
    Encoding: TC: O(N)
    We use the preorder traversal data.
    
    Decoding: TC: O(nlogn)
    We use the node values from preorder traversal and insert one node at
    a time to the BST. Since we use preorder data we will be pushing nodes
	as they appeared in the original tree.
*/
//////////// SOLUTION 1

public:
    void preorder(TreeNode* root, string& result) {
        if(!result.empty())
            result += ',';
        
        if(!root) {
            result += 'n';
            return;
        }
        
        result += to_string(root->val);
        
        preorder(root->left, result);
        preorder(root->right, result);
    }
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string result;
        
        preorder(root, result);
        return result;
    }
    
    TreeNode* decode(istringstream& ss) {
        string token;
        if(!getline(ss, token, ','))
            return nullptr;
        
        if(token == "n")
            return nullptr;
        
        TreeNode* root = new TreeNode(stoi(token));
        root->left = decode(ss);
        root->right = decode(ss);
        
        return root;
    }
    
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream ss(data);
        return decode(ss);
    }
};



//////////// SOLUTION 2
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
