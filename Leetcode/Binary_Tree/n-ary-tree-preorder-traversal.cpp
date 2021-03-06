/*
    https://leetcode.com/problems/n-ary-tree-preorder-traversal/submissions/
    
    Iterative Solution:
    The idea is to use a stack to save the info of children nodes for each of the parents.
    Since it is preorder, the leftmost is always picked up, so leftmost node is never saved
    in the stack. The leftmost node is used for doing DFS in the current path.
    
            0
        /  /  \ \
        1 2   3  4
        
        We start with 0 as the current node, print it and save the children in right->left
        
        curr: 0
        Save 0 in the traversal oder
        Stack: 4,3,2
        Use the leftmost node for DFS in the next iteration:
        curr: 0->leftmost
        
        curr: 1
        Save 1 in the traversal oder
        Iterate through the children of node 1, since there are none, it becomes NULL and
        we look into the stack for the next child, which is 2
        
        curr: 2
        Stack: 4,3
        Save 2 in the traversal oder
        Repeat the same
        
    TC: O(N)
    SC: O(w), w: max width of tree, worst case, n-2 nodes when root has all
        the nodes as its children
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
    // Iterative
    void preorderIter(Node *root, vector<int> &order) {
        stack<Node*> s;
        Node *curr = root;
        
        while(curr || !s.empty()) {
            // DFS till a NULL node is not reached
            while(curr) {
                order.emplace_back(curr->val);
                // if current is a leaf node
                if(curr->children.empty())
                    curr = nullptr;
                else {
                    // add the child nodes from last to first
                    // so that the left nodes comes first in the stack
                    for(int i = curr->children.size() - 1; i >= 0; i--) {
                        // We use the leftmost node during the current traversal
                        // in the next cycle, we save the remaining nodes in stack
                        // so that they can used later for traversal
                        if(i == 0)
                            curr = curr->children[i]; 
                        else
                            s.emplace(curr->children[i]);
                    }
                }
                
            }
            // Update the current node with the next preorder successor
            if(!s.empty()) {
                curr = s.top();
                s.pop();
            }
        }
    }
    
    // Recursive
    void preorderRec(Node *root, vector<int> &order) {
        if(root) {
            order.emplace_back(root->val);
            for(auto child: root->children)
                preorderRec(child, order);
        }    
    }
    
    vector<int> preorder(Node* root) {
        vector<int> order;
        preorderIter(root, order);
        //preorderRec(root, order);
        return order;
    }
};
