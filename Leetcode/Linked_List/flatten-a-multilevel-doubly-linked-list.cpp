/*
    https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/submissions/
    
    This list is nothing but a tree with each node having next and child nodes
    like right and left child.
    So we do preorder traversal to get the flattened list by adding each
    node to the flattened list
        
*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/
/////////////////////// STYLE 1
class Solution {
public:
    void dfs(Node* head, Node*& last) {
        if(!head)
            return;
        
        Node* nxtptr = nullptr;
        // add the nodes in the current level
        while(head) {
            // Make the last added node's next point
            // to current node and current node's prev
            // point to last node
            head->prev = last;
            last->next = head;
            last = head;
            // save the next node addr since this node is the current
            // last and will be altered during dfs of its child
            nxtptr = head->next;
            
            // end the current last node
            last->next = nullptr;
                     
            // Do dfs of its child nodes
            if(head->child)
                dfs(head->child, last);
            
            head->child = nullptr;
            // go to the next node originally in the multilevel list
            head = nxtptr;
        } 
    }
    
    Node* flatten(Node* multilevel_head) {
        Node* head = new Node(-1), *last = head;
        
        dfs(multilevel_head, last);
        // Delete the dummy head node
        Node* temp = head;
        head = head->next;
        // Since the 1st node's prev was pointing to the dummy head,
        // make it point to null now
        if(head)
            head->prev = nullptr;
        delete temp;
        
        return head;
    }
};

/////////////////////// STYLE 2
class Solution {
public:
    // Preorder traversal 
    // TC: O(N)
    void preorderTraversal(Node* head, Node*& flatten_tail)  {
        if(head) {
            // add current node
            flatten_tail->next = head;
            // link the prev of current
            head->prev = flatten_tail;
            flatten_tail = flatten_tail->next;
            
            Node *right = head->next;
            // recurse for child node
            preorderTraversal(head->child, flatten_tail);
            // recurse for remainiing list in its level
            preorderTraversal(right, flatten_tail);
            
            // set the child ptr as NULL
            head->child = nullptr;
        }
    }
    
    Node* flatten(Node* head) {
        // We use a dummy head to make head related operations easier
        Node *flatten_head = new Node(-1), *tail = flatten_head;
        
        preorderTraversal(head, tail);
        // end the linked list
        tail->next = nullptr;
        
        // delete the dummy head node
        Node *temp = flatten_head;
        flatten_head = flatten_head->next;
        delete temp;
        // make the head' prev point to NULL
        if(flatten_head)
            flatten_head->prev = nullptr;
        
        return flatten_head;
    }
};
