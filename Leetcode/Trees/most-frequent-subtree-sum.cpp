/*
    508. Most Frequent Subtree Sum
    https://leetcode.com/problems/most-frequent-subtree-sum/
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

    int findFrequentSum(TreeNode* root, unordered_map<int, int>& freq,
					int& max_freq) {
        if(!root)
            return 0;
        
        // recurse for left and right
        int left = findFrequentSum(root->left, freq, max_freq);
        int right = findFrequentSum(root->right, freq, max_freq);
        
        // add the current sum to hash table
        int curr_sum = left + root->val + right;
        if(freq.find(curr_sum) == freq.end())
            freq[curr_sum] = 0;

        ++freq[curr_sum];
        max_freq = max(max_freq, freq[curr_sum]);

        return curr_sum;
    }

    vector<int> findFrequentTreeSum(TreeNode* root) {
        // for storing the sum frequency
        unordered_map<int, int> freq;
        vector<int> ans;
        // max frequency of sum
        int max_freq = 0;
        findFrequentSum(root, freq, max_freq);
        
        // find all those sum values with max frequency value
        unordered_map<int, int> :: iterator it;
        for(it = freq.begin(); it != freq.end(); it++) {
            if(it->second == max_freq) 
                ans.emplace_back(it->first);
        }
        
        return ans;
    }
};
