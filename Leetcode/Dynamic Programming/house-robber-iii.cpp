/*
    337. House Robber III
    https://leetcode.com/problems/house-robber-iii/

    Easy DFS
    
    DP:
        For each house, it can either be robbed or not robbed
         // when current is robbed, then we add the value that can be obtained 
        // from left and right subtrees when its left and child are not robbed

        // when current is not robbed, max value is the value we can get by either robbing or 
        // not robbing the left and right child
    
    DFS:
        Same as above without memoization
*/

class Solution {
public:
    pair<long, long> sol(TreeNode* root) {
        if(!root)
            return {0, 0};
        
        // pair.first = rob current house
        // pair.second = don't rob current house
    
        pair<long, long> left = sol(root->left);
        pair<long, long> right = sol(root->right);
        
        pair<long, long> curr;
        // rob current house
        curr.first = root->val + left.second + right.second;
        curr.second = max(left.first, left.second) + max(right.first, right.second);
        
        return curr;
    } 
    
    int rob(TreeNode* root) {
        auto ans = sol(root);
        return max(ans.first, ans.second);
    }
};

//////////////////////////////////////////////////////////////////////////
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
    int maxRob(TreeNode* root, unordered_map<TreeNode*, pair<int, int> >& dp) {
        if(!root)
            return 0;
		if(dp.find(root) == dp.end()) {
			int left = maxRob(root->left, dp);
			int right = maxRob(root->right, dp);

			// when current house is not robbed
			dp[root].second = 0;
			// when current house is robbed
			dp[root].first = root->val;
			
            // when current is robbed, then we add the value that can be obtained 
            // from left and right subtrees when its left and child are not robbed
          
            // when current is not robbed, max value is the value we can get by either robbing or 
            // not robbing the left and right child
			if(root->left) {
                // when current is robbed 
				dp[root].first += dp[root->left].second;
                // when current is not robbed
				dp[root].second += max(dp[root->left].first, dp[root->left].second);
			}
			if(root->right) {
                dp[root].first += dp[root->right].second;
				dp[root].second += max(dp[root->right].first, dp[root->right].second);
			}
		}

        return max(dp[root].first, dp[root].second);
    }
    
    // We find the max value that can be achieved by robbing or not robbing a house
    // from bottom up.
    int maxRobDFS(TreeNode* root, int& include_curr, int& exclude_curr) {
        if(!root)
            return include_curr = 0, exclude_curr = 0;
        
        // these will store the max value when the next house 
        // is robbed or not robbed
        int exclude_left = 0;
        int include_left = 0;
        int exclude_right = 0;
        int include_right = 0;
        
        int left = maxRobDFS(root->left, include_left, exclude_left);
        int right = maxRobDFS(root->right, include_right, exclude_right);
        
        // if current house is robbed, then only add the max value when its left and right
        // are not robbed
        include_curr = root->val + exclude_left + exclude_right;
        // if curret house is not robbed, then the max value can be sum of max values of left/right houses
        // robbed/not robbed
        exclude_curr = max(include_left, exclude_left) + 
                        max(include_right, exclude_right);
        
        return max(include_curr, exclude_curr);
    }
    int rob(TreeNode* root) {
        // pair:
        // first: max value when current house is robbed
        // second: max value when curret house is not robbed
        //unordered_map<TreeNode*, pair<int, int> > dp;
        //int max_loot = maxRob(root, dp);	
        int include_curr = 0, exclude_curr = 0;
        int max_loot = maxRobDFS(root, include_curr, exclude_curr);
        return max_loot;
    }
};
