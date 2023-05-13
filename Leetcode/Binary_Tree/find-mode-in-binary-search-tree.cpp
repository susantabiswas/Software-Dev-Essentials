/*
    https://leetcode.com/problems/find-mode-in-binary-search-tree/
    
    // Solution 1
    We find the frequency count of all the nodes and sort them in decreasing order 
    of frequency count. Return all the elements which have the max freq count.
    
    // Solution 2
    Since inorder traversal in BST gives sorted order,
    we use that to get the numbers in increasing order. 
    Each time we check if the current number is same as the previous,
    if it is and the frequency count for this number equal to the max_frequency count seen 
    so far, we add that to the final result. If the curr frequency > max frequency,
    then we remove all the numbers which had the previously thought max freq and 
    set the current number's frequency as the max frequency and add to the final result.

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
    void dfs(TreeNode *root, unordered_map<int, int> &freq) {
        if(root) {
            ++freq[root->val];
            dfs(root->left, freq);
            dfs(root->right, freq);
        }   
    }
    
    // Solution 1: Using O(N) space
    // TC: O(N)
    vector<int> sol1(TreeNode *root) {
        unordered_map<int, int> freq;
        // get the frequency count of all the nodes
        dfs(root, freq);
        vector<int> result;
        vector<pair<int, int>> elements;
        
        // save the freq found for each nodes
        for(auto &element: freq)
            elements.emplace_back(element);
        // sort by freq
        sort(elements.begin(), elements.end(), 
             [](const pair<int, int> &a, const pair<int, int> &b)->bool{
                 return a.second > b.second;
             });
        int max_count = INT_MIN;
        
        // save all the numbers which has the max freq count
        if(!elements.empty()) 
            max_count = elements[0].second;
        for(auto it = elements.begin(); it != elements.end(); it++) {
            if(it->second < max_count)
                break;
            result.emplace_back(it->first);
        }
        
        return result;
    }
    
    
    void inorder(TreeNode *root, TreeNode* &prev,
                int &max_freq, int &curr_freq,
                 vector<int> &result) {
        if(root) {
            inorder(root->left, prev, max_freq, curr_freq, result);
            
            // check if the current node value is the
            // same as the previous one
            curr_freq = (prev && root->val == prev->val? curr_freq + 1 : 1);
            
            if(curr_freq == max_freq)
                result.emplace_back(root->val);
            // new max freq element found, remove previous
            else if(curr_freq > max_freq) {
                result.clear();
                result.emplace_back(root->val);
            }
            
            prev = root;
            max_freq = max(max_freq, curr_freq);
            inorder(root->right, prev, max_freq, curr_freq, result);
        }
    }
    
    // Solution 2: Using O(1) space
    // TC: O(N)
    vector<int> sol2(TreeNode *root) {
        int max_freq = 0, curr_freq = 0;
        TreeNode *prev = nullptr;
        vector<int> result;
        
        inorder(root, prev, max_freq, curr_freq, result);
        return result;
    }
    
    vector<int> findMode(TreeNode* root) {
        // return sol1(root);
        return sol2(root);
    }
};
