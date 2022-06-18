/*
    https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another/
    
    Solution 1: LCA
    
    Find the LCA. Then from the lca, find the path to source and destination. Join the paths
    
    Solution 2: Common Prefix path
    Find the path from root to both the source and destination. Then merge the paths, i.e remove the
    common prefix, this results in a path joining the source and destination via LCA.
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
    // Finds Lowest Common Ancestor of two nodes
    TreeNode* findLCA(TreeNode* root, int src, int dst) {
        if(!root)
            return nullptr;
        // either of source or destination found
        if(root->val == src || root->val == dst)
            return root;
        
        TreeNode* left = findLCA(root->left, src, dst);
        TreeNode* right = findLCA(root->right, src, dst);
        // The two nodes lie on opp sides, so this node is the LCA
        if(left && right)
            return root;
        // LCA already found in either side, just return it
        if(left || right)
            return left ? left : right;
        
        return nullptr;
    }
    
    // Finds the Path from a root node to a destination node
    bool getPath(TreeNode* root, int node, string& path) {
        if(!root)
            return false;
        // Target node found on the path
        if(root->val == node) 
            return true;
        
        // Traverse left and right subtrees. If a subtree has a path
        // leading to destination node, then only add the direction for that path
        // and return immediately without traversing the other side
        auto left = getPath(root->left, node, path);
        if(left) {
            path += 'L';
            return true;
        }
        
        auto right = getPath(root->right, node, path);
        if(right) {
            path += 'R';
            return true;
        }
        
        return false;
    }
    
    // SOLUTION 1: LCA
    // TC: O(N)
    // SC: O(N)
    string lcaSol(TreeNode* root, int src, int dst) {
        // Find the LCA of source and destination node
        TreeNode* lca = findLCA(root, src, dst);
        // tracks the path from source to lca, lca to destination
        string src_lca_path, lca_dst_path;
        
        // Find the source to ancestor path
        if(src != lca ->val) {
            getPath(lca, src, src_lca_path);
            // since the path is made bottom up, reverse it
            reverse(src_lca_path.begin(), src_lca_path.end());
            // replace moves with U, since we are moving up
            for(int i = 0; i < src_lca_path.size(); i++)
                src_lca_path[i] = 'U';
        }
        
        // find the ancestor to destination path
        if(dst != lca->val) {
            getPath(lca, dst, lca_dst_path);
            reverse(lca_dst_path.begin(), lca_dst_path.end());
        }
        // Join the two paths 
        return src_lca_path + lca_dst_path;
    }
    
    // SOLUTION 2: PREFIX PATH
    // TC: O(N)
    // SC: O(N)
    string prefixPathSol(TreeNode* root, int src, int dst) {
        // Find the path from root to source
        string root_to_src;
        getPath(root, src, root_to_src);
        
        // Find the path from root to destination
        string root_to_dst;
        getPath(root, dst, root_to_dst);
        
        // since the path is made bottom up, reverse it
        reverse(root_to_src.begin(), root_to_src.end());
        reverse(root_to_dst.begin(), root_to_dst.end());
        
        // Remove the common prefix path
        int i = 0, j = 0;
        for(; i < root_to_src.size() && j < root_to_dst.size(); i++, j++)
            if(root_to_src[i] != root_to_dst[j])
                break;
        // Since the path from source might be moving upwards, fill with U
        // if it goes downwards to find dst, the portion for upwards path will
        // anyway not come below as the common path from root for both source and dst
        // will have the same prefix and hence upwards_path.length() = 0 
        string upwards_path(root_to_src.size() - i, 'U');
        string path = upwards_path + root_to_dst.substr(j);
        
        return path;
    }
    
    string getDirections(TreeNode* root, int src, int dst) {
        // return lcaSol(root, src, dst);
        return prefixPathSol(root, src, dst);
    }
};
