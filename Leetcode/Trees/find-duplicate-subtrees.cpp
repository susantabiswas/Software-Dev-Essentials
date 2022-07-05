/*
    https://leetcode.com/problems/find-duplicate-subtrees/
    
    TC: O(n^2), Even though we traverse only once i.e O(n), the hash string gets longer and longer.
    We first add one node info, then two, then three .....
    Processing the hash string: 1 + 2 + .... n => n^2
    
    Idea is same as in merkel tree. We hash the paths from bottom up. Keep track of hash of the path and
    for the current node check if the hash path was seen before or not, if yes then there isa duplicate subtree.
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
    string postOrder(TreeNode* root, unordered_map<string, int>& subtree_hash,
                    vector<TreeNode*>& result) {
        // null node
        if(!root)
            return "#";
        
        // Get the traversal hash for the left and right subtrees
        string left_hash = postOrder(root->left, subtree_hash, result);
        string right_hash = postOrder(root->right, subtree_hash, result);
        
        // Hash string for the current subtree rooted at 'root'
        // If we do left + curr + right, then we can have same pattern for this pattern:
        /*
                       0
                      / \
         [#,0,#,0,#] 0   0 [#,0,#,0,#]
                    /     \
          [#,0,#]  0       0 [#,0,#]
          
          That's why we need either preorder or postorder in subtree path pattern
        */
        string subtree = left_hash + "," + right_hash + "," + to_string(root->val);
        
        // check if the same subtree path was seen before or not
        // If seen before and this is the second time seen, then only add to result
        // don't add after second time since that would be redundant
        if(subtree_hash.count(subtree) && subtree_hash[subtree] == 1)
            result.emplace_back(root);
        
        ++subtree_hash[subtree];
        return subtree;
    }
    
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        // <subtree_traversal_path, no. of nodes to have that in their tree with them as root>
        unordered_map<string, int> subtree_hash;
        vector<TreeNode*> result;
        
        postOrder(root, subtree_hash, result);
        return result;
    }
};
