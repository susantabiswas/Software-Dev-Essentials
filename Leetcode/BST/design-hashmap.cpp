/*
    https://leetcode.com/problems/design-hashmap/
    
*/
class MyHashMap {
    struct TreeNode {
        int key = 0, val = 0;
        TreeNode* left = nullptr, *right = nullptr;
        TreeNode(int key, int val): key(key), val(val) {};
    };
    TreeNode* root = nullptr;
public:
    MyHashMap() {
        
    }
    
    TreeNode* insert(TreeNode* root, TreeNode*& node) {
        if(!root)
            return node;
        if(root->key == node->key) {
            root->val = node->val;
        }
        else if(root->key < node->key)
            root->right = insert(root->right, node);
        else
            root->left = insert(root->left, node);
        return root;
    }
    
    TreeNode* search(TreeNode* root, int key) {
        if(!root)
            return nullptr;
        if(root->key == key)
            return root;
        else if(root->key < key)
            return search(root->right, key);
        else 
            return search(root->left, key);
    }
    
    void preorder(TreeNode* root) {
        if(root) {
            cout << root->val <<" ";
            preorder(root->left);
            preorder(root->right);
        }    
    }
    
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(!root)
            return nullptr;
        // node found
        if(root->key == key) {
            // if node is a leaf node
            if(!root->left and !root->right)
                return nullptr;
            // if the node only has one subtree
            if(!root->left || !root->right)
                return root->left ? root->left : root->right;
            // node has both subtrees, find the inorder successor and put that element
            // here and delete that leaf node
            else if(root->left && root->right) {
                TreeNode* successor = root->right;
                while(successor && successor->left)
                    successor = successor->left;
                // put the inorder successor at the curr root's place
                root->key = successor->key;
                root->val = successor->val;
                // now recurse further to delete that node
                root->right = deleteNode(root->right, successor->key);
            }
        }
        else if(root->key < key)
            root->right = deleteNode(root->right, key);
        else
            root->left = deleteNode(root->left, key);
        return root;
    }
    
    void put(int key, int value) {
        TreeNode* node = new TreeNode(key, value);
        // cout <<"Preorder" << endl;
        // preorder(root);
        root = insert(root, node);
    }
    
    int get(int key) {
        TreeNode* node = search(root, key);
        return node ? node->val : -1;
    }
    
    void remove(int key) {
        // always return the root node, incase the root 
        // node key is deleted
        root = deleteNode(root, key);
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
