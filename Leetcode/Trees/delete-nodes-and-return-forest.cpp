/*
    https://leetcode.com/problems/delete-nodes-and-return-forest/submissions/
	
	Idea is to traverse in post order and while processing a node check if that node 
	needs to be deleted or not. If it needs deletion then the child nodes become tree root 
	candidates, so add them as new tree roots in the final answer if they are not null.
	TC: O(N)
	SC: O(N)
*/

class Solution {
public:
    TreeNode* createForest(TreeNode *root, unordered_set<int>& delete_nodes,
                          vector<TreeNode*>& roots) {
        if(!root)
            return nullptr;
        // Process the left and right subtrees
        root->left = createForest(root->left, delete_nodes, roots);
        root->right = createForest(root->right, delete_nodes, roots);
        
        // if current node needs to be deleted
        if(delete_nodes.count(root->val)) {
            // the left and right subtrees will be orphans and
            // become disjoint tree roots
            if(root->left)
                roots.emplace_back(root->left);
            if(root->right)
                roots.emplace_back(root->right);
            return nullptr;
        }
        
        return root;
    }
    
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        if(!root)
            return {};
        
        vector<TreeNode*> roots;
        // Set of all node values to be deleted
        unordered_set<int> delete_nodes(to_delete.begin(), to_delete.end());
        // Since head wont be processed in the recursive code unless
        // a dummy head is attached
        if(!delete_nodes.count(root->val))
            roots.emplace_back(root);
        
        createForest(root, delete_nodes, roots);
        
        return roots;
    }
};
