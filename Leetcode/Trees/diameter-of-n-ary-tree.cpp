/*
    https://leetcode.com/problems/diameter-of-n-ary-tree/
    
    TC: O(n)
    SC: O(n)
    
    This is similar to max path sum problem in binary tree. The diff being here the 
    metric is path length. Since we want the max path length, we can always get a longer path
    by combining multiple path's lengths. So for each node, find the 2 longest lengths ending at
    the node from its subtrees.
    These two will be checked for the max length path, return the max length path from there to
    its parent.
*/
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    int postorder(Node* root, int& max_len) {
        if(!root || root->children.empty())
            return 0;
        
        int max_len1 = 0, max_len2 = 0;
        // Pick the 2 max length paths ending at the current node
        for(auto child: root->children) {
            int len = 1 + postorder(child, max_len);
            // Update the max or 2nd max length if applicable
            if(len > max_len1) {
                max_len2 = max_len1;
                max_len1 = len;
            }
            else if(len > max_len2)
                max_len2 = len;
        }
        // Since we are considered with max path length, we will always
        // get a bigger length by combining paths
        max_len = max(max_len, max_len1 + max_len2);
        
        // return the max path length upto the current node
        return max_len1;    
    }
    
    int diameter(Node* root) {
        int max_len = 0;
        postorder(root, max_len);
        return max_len;
    }
};
