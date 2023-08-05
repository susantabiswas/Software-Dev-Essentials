/*
    95. Unique Binary Search Trees II
    https://leetcode.com/problems/unique-binary-search-trees-ii/
    **************** NOTE******************* 
    O(n*Cn) only happens with memoization, otherwise with the below code
    we end of doing backtracking and repeating a lot of computations. Refer the 2nd solution of DP
    
    Time: O(C0+C1+...Cn), where Cn is the Catalan number
    SC: O(n * Cn), Cn: Total Cn no. of BSTs with n nodes

    TC: O(n * Cn)
    SC: O(n * Cn)
    Cn = nth Catalan number

    Though the solution is the nth Catalan number, to compute that we end up computing
    Catalan number for each of 1...n. So n * Cn. Similarly we save n Catalan numbers.

    For each n, the time complexity due to the loops and picking each intermediate node as 
    root leads to a total of nth Catalan.

    The Catalan number grows asymptotically similar to 4^n/n^(3/2)
    So n * (4^n/n^(3/2)) => (4^n/n^(1/2))
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
    vector<TreeNode*> createTree(int start, int end) {
        // base case: return nullptr
        if(end < start)
            return vector<TreeNode*>{nullptr};

        vector<TreeNode*> ans;
        // for current interval each number is taken as root once
        for(int i = start; i <= end; i++) {
            vector<TreeNode*> left_subtree, right_subtree;
            // recurse for left and right subtrees
            left_subtree = createTree(start, i-1);
            right_subtree = createTree(i+1, end);
            
            // fixing the current root, traverse through the ]
            // different root nodes of left and right subtrees and
            // make them the child nodes one by one
            for(int j = 0; j < left_subtree.size(); j++) {
                for(int k = 0; k < right_subtree.size(); k++) {
                    // create the root 
                    TreeNode* root = new TreeNode(i);
                    root->left = left_subtree[j];
                    root->right = right_subtree[k];
                    ans.emplace_back(root);
                }
            }

        }

        return ans;
    }

    vector<TreeNode*> generateTrees(int n) {
        if(n <= 0)
            return vector<TreeNode*>{};
        return createTree(1, n);
        
    }
};

/*
    https://leetcode.com/problems/unique-binary-search-trees-ii/

    TC: O(n * Catalan Number) = O(n * (4^n/n^1.5)) ~ O(4^n/n^0.5)
    SC: O(4^n/n^0.5)
    
    There are C(n) unique trees. C(n) = Catalan number = 4^n/n^1.5.
    Also each tree consists finally of n nodes and while building the tree, we
    need to create each of those unique nodes which takes O(n).
*/
class Solution {
public:
    vector<TreeNode*> genTrees(int start, int end, vector<vector<vector<TreeNode*>>>& dp) {
        // base case
        if(start > end)
            return vector<TreeNode*>{ nullptr };
        
        if(dp[start][end].empty()) {
            vector<TreeNode*> trees;
        
            for(int curr = start; curr <= end; curr++) {
                vector<TreeNode*> leftSubtrees = genTrees(start, curr - 1, dp);
                vector<TreeNode*> rightSubtrees = genTrees(curr + 1, end, dp);

                for(auto left: leftSubtrees)
                    for(auto right: rightSubtrees) {
                        // current root
                        TreeNode* root = new TreeNode(curr);

                        root->left = left;
                        root->right = right;

                        trees.emplace_back(root);
                    }
            }

            dp[start][end] = trees;
        }
        return dp[start][end];
    }
    
    vector<TreeNode*> generateTrees(int n) {
        // dp[start][end] = vector<TreeNode*>{ All possible unique trees with nodes from start..end }
        vector<vector<vector<TreeNode*>>> dp(n + 1, vector(n + 1, vector<TreeNode*>(0))); dp;
        return genTrees(1, n, dp);
    }
};
