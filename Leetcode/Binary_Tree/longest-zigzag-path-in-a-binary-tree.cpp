/*
    https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/
    
    TC: O(N)
    SC: O(N), recursive stack will be equal to height of tree which in worst case is N
    
    Idea is simple:
    - A zigzag path needs alternating left and right child nodes in the subtree
    - For a given node, if we want to create a zigzag with its child node then we need to make sure
    that the path from that child node is alternating.
    E.g if we make a zigzag path with the right child, we can only follow the left zigzag path starting from
    the right child
    1
     \
      2
     / \
    3   4
    
    Path: 1, 2, 3 
    
    Similarly to create path with the left child, we use the left child's right zigzag path
    
    - We return the left and right zigzag path lengths for each of the nodes to its parent.
    - For the current node, set its left and right zigzag paths using the computed values of its children
    - Track the max length path
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
private:
    struct Zigzag {
        // length of max length left and right zigzag paths
        int leftPath = 0, rightPath = 0;
    };
public:
    Zigzag findLongestZigzag(TreeNode* root, int& max_len) {
        if(!root)
            return Zigzag();
        
        Zigzag left = findLongestZigzag(root->left, max_len);
        Zigzag right = findLongestZigzag(root->right, max_len);
        
        // find the longest zigzag path lengths ending from
        // left and right child ending here
        Zigzag path;
        path.leftPath = root->left ? left.rightPath + 1 : 0;
        path.rightPath = root->right ? right.leftPath + 1 : 0;
        
        max_len = max({max_len, path.leftPath, path.rightPath});
        
        return path;
    }
    
    int longestZigZag(TreeNode* root) {
        int max_len = 0;
        findLongestZigzag(root, max_len);
        return max_len;
    }
};
