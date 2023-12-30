/*
    https://leetcode.com/problems/subtree-of-another-tree/

    SOLUTION 1
    We use BFS to look for the root mode of tree t. Once a node
    is found in s, we check if t is present as a subtree with that node as root.
    
    TC: O(NM), M: nodes in t, N: nodes in s

    SOLUTION 2: Hashing
    TC: O(N + M)
    SC: O(max(M, N))

    Postorder/ Preorder
    NOTE - One imp thing to take care is with the start of a node. The hash of a subtree might start from the 
    the substring of another tree's node, this can give false positive.
    eg: tree: [21]
    subtree: [1]

        hash: 1 might match with partial node string 21, so we need to ensure that the start of node is clear and cannot be a 
        substring of another node's string value.
    
        This is why if we add ',' before each value, we can ensure that a char is there to mark the start of a node value.
        With this, above problem is resolved, 
        tree hash: ,21,LL
        subtree hash: ,1,LL

        Note - We don't need to mark the recursion end of child call with a special char since we are marking the null nodes
        and they capture the tree structure.

    
    Inorder:
        One caution with inorder, since the left subtree hash is present before the curr + right, the null node of left subtree
        might along with the rest of matching subtree might give a false positive. Here we can use a special symbol to mark the end of recursion
        call, this way after the null node of left subtree we will get * symbols to capture the actual structure.
    
    Subtree
        9
      /  \
     0    1
          \
           2

    Main Tree
        100
       / \ 
      9
    /  \
   0    1
    \    \
     8    2

    Here the main tree doesnt really have the subtree, but without capturing the end of recursion, the null node after 8 will appear just before 9 and 
    the string search wll turn true.
    With capturing the recursion call end, we will have null,*,9.... => this will not match the string as expected
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
    }
    
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        // find the hash
        string orig;
        postorder(root, orig);
        
        string subtree;
        postorder(subRoot, subtree);
        
        return orig.find(subtree) != string::npos;
    }
