/*
  94. Binary Tree Inorder Traversal
    https://leetcode.com/problems/binary-tree-inorder-traversal/
*/
// using Morris Threaded Binary tree 
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> inorder;
        TreeNode* curr = root;
        
        while(curr) {
            // if current node has left subtree
            if(curr->left) {
                // go to its rightmost node, if this is the first
                // time this node is being visited, then we just create a 
                // link from rightmost node to current, otherwise we break the exisiting 
                // link and revert back the rightmost leaf node
                TreeNode* right_ptr = curr->left;
                while(right_ptr->right && right_ptr->right != curr) 
                    right_ptr = right_ptr->right;
                
                // first time 
                if(right_ptr->right == nullptr) {
                    right_ptr->right = curr;
                    curr = curr->left;
                }
                // current node is being visited for the second time,
                // this time it should be added to traversal order
                else {
                    // revert back
                    right_ptr->right = nullptr;
                    // add the current node
                    inorder.emplace_back(curr->val);
                    // go right
                    curr = curr->right;
                }
            }
            // process current node and go to right subtree
            else {
                inorder.emplace_back(curr->val);
                // go right
                curr = curr->right;
            }
            
        }
        
        return inorder;
    }
