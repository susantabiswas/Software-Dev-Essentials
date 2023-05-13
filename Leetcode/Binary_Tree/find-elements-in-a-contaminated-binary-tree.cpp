/*
    https://leetcode.com/problems/find-elements-in-a-contaminated-binary-tree/
    
    Idea is to create the tree in a top down manner using the given rules.We pass the value
    that needs to be set. Initially 0 is passed for the root node, there onwards, we use the
    rules to pass the left and right values in a preorder fashion.
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
class FindElements {
private:
    TreeNode *root_ = nullptr;
    unordered_set<int> nodes_;
public:
    void recoverTree(TreeNode *root, int val) {
        if(root) {
            // set the value
            root->val = val;
            // add the current node value to the set of all nodes
            nodes_.emplace(val);
            // left child: 2*val + 1
            recoverTree(root->left, 2 * val + 1);
            // right child: 2*val + 2
            recoverTree(root->right, 2 * val + 2);
        }    
    }
    
    FindElements(TreeNode* root) {
        root_ = root;
        // recover the tree
        recoverTree(root_, 0);
    }
    
    bool find(int target) {
        return nodes_.count(target);
    }
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
