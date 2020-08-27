/*
    https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/submissions/
    
    Idea is to use BFS, we track the previous left node for the current node in the same 
    level to join it.
    TC: O(N)
*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        if(!root)
            return nullptr;
        
        queue<Node*> q;
        q.emplace(root);
        
        // tracks the left node 
        Node *prev = nullptr;
        int n_level = q.size();
        
        while(!q.empty()) {
            Node *curr = q.front();
            q.pop();
            --n_level;
            
            // link the current node with previous if that exists
            if(prev)
                prev->next = curr;
            
            if(curr->left)
                q.emplace(curr->left);
            if(curr->right)
                q.emplace(curr->right);
            // make current the previous node for next
            prev = curr;
            
            // end of level
            if(n_level == 0) {
                n_level = q.size();
                prev = nullptr;
            }
        }
        
        return root;
    }
};
