/*
    https://leetcode.com/problems/count-complete-tree-nodes/
    
    Solution 1: Binary Search
    Main idea is to find the height of tree and then find the no. of 
    nodes in the leaf level using binary search. For each binary search mid, we use
    another binary search to check if a path can be traversed from root to that node.
    
    Solution 2: Recursive
    Main idea is that subtree of a complete binary tree is a complete or perfect binary tree.
    If the tree has incomplete leaf level, then the tree can be divided into 2 subtrees, one which
    is perfect and another complete. For a given subtree we check whether it is a perfect tree or not. 
    If not then we recurse for its subtrees, one would be perfect and return immediately, while the 
    other will again recurse to point out the complete binary tree.
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
    // Finds a path from root to target leaf node. This takes O(logn)
    bool nodeExists(int node_idx, int height, TreeNode* root) {
        int low = 1, high = pow(2, height);
        // Find a way towards the target node
        int idx = 0;
        // Go till leaf level
        while(idx < height) {
            int mid = low + (high - low) / 2;
            // Node lies in the right subtree
            if(node_idx > mid) {
                low = mid + 1;
                root = root->right;
            }
            // node lies in the left subtree
            else {
                high = mid;
                root = root->left;
            }
            ++idx;
        }
        // Node exists
        return root != nullptr;
    }
    
    // SOLUTION 1: BINARY SEARCH
    // TC: O(height + height*height) => O(logn) + O(log2n)
    // SC: O(logn)
    int binarySearchSol(TreeNode* root) {
        if(!root)
            return 0;
        
        // Find the height of tree. Since it's a full binary tree
        // We can just keep travelling left till nullptr
        int height = 0;
        TreeNode* curr = root;
        while(curr->left) {
            ++height;
            curr = curr->left;
        }
        
        // only 1 node, no need to compute leaf level partial nodes
        if(height == 0)
            return 1;
        
        // Now find the no. of nodes in the last level
        // Since we have a full binary tree, we can use the nodes
        // inside the tree to travel towards the last level.
        // We use binary search to find the no. of nodes in last level,
        // to confirm whether whether that many nodes are there, we find
        // a path from root till that node using the fact that we can use the
        // inner nodes to traverse and checking in which subtree that node will lie.
        // Last level can have 0 .. 2^height - 1 nodes
        int low = 1, high = (int)pow(2, height);
        
        while(low <= high) {
            // Assume that the nodes in last level are numbered from 1...2^height-1
            int mid = low + (high - low) / 2;
            
            // Check whether mid indexed node exists or not
            // If it exists, try a bigger node idx
            if(nodeExists(mid, height, root)) 
                low = mid + 1;
            else
                high = mid - 1;
        }
        // inner nodes till height-1 level + leaf nodes
        return pow(2, height) - 1 + high;
    }
    
    // SOLUTION 2: RECURSIVE 
    // TC: O(height * height) => O(logn * logn)
    // SC: O(height) => O(logn)
    // The recursive call happens from a root node, but the thing to note is that
    // this call happens always from one node in a level. This is because the tree is a 
    // complete binary tree and a subtree of a complete binary tree is either complete or
    // perfect binary tree. Only when we are in a complete subtree with partial leaf level, the 
    // root there will call recursively for the next two subtrees. The other subtree at the
    // same level would be perfect binary tree and use pow(2, left_height + 1) - 1 to return immediately.
    int recursiveSol(TreeNode* root) {
        // base case
        if(!root)
            return 0;
        
        // Find the height from left and right side
        int left_height = 0, right_height = 0;
        TreeNode* root1 = root, *root2 = root;
        // left side height
        while(root1->left) {
            ++left_height;
            root1 = root1->left;
        }
        // right side height
        while(root2->right) {
            ++right_height;
            root2 = root2->right;
        }
        
        // If the tree is has all the nodes in the leaf level,
        // then both left and right heights will be same. 
        // Total nodes: 2 ^ (height + 1) - 1
        if(left_height == right_height)
            return pow(2, left_height + 1) - 1;
        
        // If the heights are not same, that means in the current tree there
        // are some leaf nodes but not all.
        // Now since we are dealing with a complete binary tree, except for the last level
        // other levels will have all the nodes. Now for the current root, there are 2 subtrees that
        // each have half the nodes before height-1 level and in the last level only one of them will have
        // unfilled leaf level, the other subtree will have all the nodes and will be a perfect binary tree.
        // We recurse further with the children of current node, each will serve as root of the below subtrees
        return 1 + recursiveSol(root->left) + recursiveSol(root->right);
    }
    
    int countNodes(TreeNode* root) {
        // return binarySearchSol(root);
        return recursiveSol(root);
    }
};
