/*
    https://leetcode.com/problems/smallest-string-starting-from-leaf/
    
    TC: O(n + mL), n = total nodes, m = leaf nodes, L = length of longest string
    SC: O(n)
    
    Idea is to create the word from top to bottom. When we reach a leaf node,
    compare the word formed so far with the smallest word seen so far.
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
    void preorder(TreeNode* root, string str, string& smallest) {
        if(root) {
            // Add the current char to the string percolated from root
            str += string(1, 'a' + root->val);
            // leaf node, check if the string formed from root till current leaf
            // is the smallest or not
            if(!root->left && !root->right) {
                // reverse the word to make it start from leaf to top
                reverse(str.begin(), str.end());
                smallest = min(smallest, str);
            }
            
            preorder(root->left, str, smallest);
            preorder(root->right, str, smallest);
        }    
    }
    
    string smallestFromLeaf(TreeNode* root) {
        string smallest = "~";
        preorder(root, "", smallest);
        return smallest;
    }
};

//////////////////////////////////////////////////
/*
    988. Smallest String Starting From Leaf
    https://leetcode.com/problems/smallest-string-starting-from-leaf/
    
    Since we want to find the smallest lexographically string which includes
    root, we start with the root and go in top down manner. If we try doing this in 
    bottom up manner then we can't be sure if the string selected at a particular node
    is indeed going to be lexographically smaller by the time we reach root. So if we start from root. 
    For each NULL node we return '~' which has ascii more than [a-z], this takes care of cases
    where node has only one child. Once a leaf node is reached return the string formed so far
    else any other node return min of left and right subtree strings.
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
class Solution {
public:
    string findSmallestString(TreeNode* root, string curr) {
        if(!root)
            return "~";
        
        // add the current character to the string
        curr = string(1, 'a' + root->val) + curr;
        
        // recurse for left and right subtrees
        string left = findSmallestString(root->left, curr);
        string right = findSmallestString(root->right, curr);
        
        // when a leaf node is encountered, we just return the string from that 
        // till root, else we return the min of left and right
        // null node returns '~' which takes care of situations where
        // node has only one child
        return (left == right) && (left == "~") ? curr : min(left, right);
    }
    
    string smallestFromLeaf(TreeNode* root) {
        string curr;
        return findSmallestString(root, curr);
    }
};
