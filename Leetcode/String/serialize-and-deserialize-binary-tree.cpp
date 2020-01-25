/*
    https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
    
    Solutions:
    1. BFS
    2. Preorder traversal
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
    // Encodes a tree to a single string using BFS.
    // TC: O(N)
    string serialize(TreeNode* root) {
        string encode_msg = "";
        queue<TreeNode*> q;
        TreeNode* curr = root;
        q.emplace(curr);
        
        while(!q.empty()) {
            curr = q.front();
            q.pop();
            encode_msg += (curr ? to_string(curr->val) : "n") + ",";
            
            if(curr) {
                q.emplace(curr->left);
                q.emplace(curr->right);
            }
        }
        return encode_msg;
    }
    
    // Decodes your encoded data to tree using BFS.
    // TC: O(N)
    TreeNode* deserialize(string data) {
        TreeNode* root = nullptr, *curr = nullptr;
        stringstream ss(data);
        string token;
        getline(ss, token, ',');
        root = token == "n" ? nullptr : new TreeNode(stoi(token));
        
        if(!root)
            return root;
        queue<TreeNode*> q;
        q.emplace(root);
            
        while(!q.empty()) {
            curr = q.front();
            q.pop();
            
            // add the left and right nodes 
            getline(ss, token, ',');
            curr->left = token == "n" ? nullptr : new TreeNode(stoi(token));
            getline(ss, token, ',');
            curr->right = token == "n" ? nullptr : new TreeNode(stoi(token));
            
            if(curr->left) 
                q.emplace(curr->left);
            if(curr->right) 
                q.emplace(curr->right);
        }
        return root;    
    }
};

/*
class Codec {
public:
    // Encodes the binary tree using preorder traversal
    // Do preorder traversal and save the root as string, incase of null
    // put that in the preorder traversal as if it is also a node
    // TC: O(N)
    void serializePreorder(TreeNode* root, string& encode_msg) {
        if(!root) {
            encode_msg += "n,";
            return;
        }
        // encode the current node
        encode_msg += to_string(root->val) + ',';
        serializePreorder(root->left, encode_msg);
        serializePreorder(root->right, encode_msg);
    }
    
    // Decodes the encoded string using preorder data
    // TC: O(N)
    TreeNode* deserializePreorder(stringstream& ss, string& data, int& curr) {
        string token;
        getline(ss, token, ',');
        
        if(token == "n") {
            return nullptr;
        }
        // create the node with current root element
        TreeNode* root = new TreeNode(stoi(token));
        root->left = deserializePreorder(ss, data, curr);
        root->right = deserializePreorder(ss, data, curr);
        return root;
    }
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string encode_msg = "";
        serializePreorder(root, encode_msg);
        
        return encode_msg;
    }
    
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int curr = 0;
        TreeNode* root = nullptr;
        stringstream ss(data);
        // if there is atleast one node
        if(!data.empty())
            root = deserializePreorder(ss, data, curr);
        
        return root;    
    }
};
*/
// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
