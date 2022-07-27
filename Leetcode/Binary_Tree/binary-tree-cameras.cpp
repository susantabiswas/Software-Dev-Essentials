/*
    https://leetcode.com/problems/binary-tree-cameras/
    
    We start looking for camera placement position from bottom to top.
    1. A camera is needed when either any of the child nodes are not covered by a camera.
    2. If any of the child nodes are covered by a camera, the parent doesn;t need a camera.
            o
            |
            x
           / \
          o   o
    Ideally we want to put a camera at position x.
    
    When we find that either of the child nodes are covered, means current need not be covered.
    When we find that either of the child node is not covered, means current node need a camera so that the
    child node missing coverage is covered as well.
    When we find that both the child nodes don't need a camera, means current has no camera placed.
    
    NO_CAMERA status is used to indicate the parent node that bottom is strictly without any cover and needs coverage.
    
    
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
    // NOT_NEEDED: When the node is covered by any of the child nodes's camera
    // NO_CAMERA: When the node strictly is not covered and needs cover. This is to indicate the parent that a camera is needed
    // CAMERA_ADDED: When a node gets a camera
    enum { NOT_NEEDED, NO_CAMERA, CAMERA_ADDED } Status;
public:
    // TC: O(N)
    // SC: O(N)
    int postorder(TreeNode* root, int& cams_req) {
        if(!root)
            return NOT_NEEDED;
        
        int left = postorder(root->left, cams_req);
        int right = postorder(root->right, cams_req);
        
        // We need to put a camera if either of the child nodes are not covered
        // since that means current node is not covered as well
        if(left == NO_CAMERA || right == NO_CAMERA) {
            ++cams_req;
            return CAMERA_ADDED;
        }
        // If either of the child nodes have a camera, current need not be covered
        else if(left == CAMERA_ADDED || right == CAMERA_ADDED)
            return NOT_NEEDED;
        // Either leaf node or the child nodes have no camera need (NOT_NEEDED)
        return NO_CAMERA;
    }
    
    int minCameraCover(TreeNode* root) {
        int cams_req = 0;
        // If the root node has no camera, a camera is needed
        return postorder(root, cams_req) == NO_CAMERA ? 1 + cams_req : cams_req;
    }
};
