/*
    https://leetcode.com/problems/copy-list-with-random-pointer/
*/
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

// SOLUTION 0: Cleanest
class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> clone;
        
        Node* curr = head;
        
        // make clone nodes
        while(curr) {
            clone[curr] = new Node(curr->val);
            curr = curr->next;
        }
        
        // set the random and next ptrs of clones
        curr = head;
        while(curr) {
            clone[curr]->next = curr->next ? clone[curr->next] : nullptr;
            clone[curr]->random = curr->random ? clone[curr->random] : nullptr;
            
            curr = curr->next;
        }
        
        return clone[head];
    }
};

class Solution {
public:
    // Solution 1
    // TC: O(N)
    // Idea is to create copy of original nodes and put them just after
    // their original counterparts. Eg: 1(orig)->1(Copy)->2(Orig)->2(Copy)->NULL
    // Since each copied node will be after their original, we can access the copied
    // counterpart by going to (orig->random)->next.
    Node* copyRandom1(Node* head) {
        Node* copy_head = nullptr, *copy_tail = nullptr;
        Node *nextptr = nullptr;
        
        // Add the copy nodes after the original nodes
        Node* temp = head;
        while(temp) {
            Node* node = new Node(temp->val);    
            nextptr = temp->next;
            // add the node copy
            temp->next = node;
            node->next = nextptr;
            
            temp = nextptr;
        }
        
        // update the random pointers
        temp = head;
        while(temp) {
            // set the random ptr of cloned node
            (temp->next)->random = temp->random ? (temp->random)->next : nullptr;
            // next node
            temp = temp->next->next;
        }
        
        temp = head;
        // remove the cloned list
        while(temp) {
            // remove the cloned node 
            // when current is the head of cloned list
            if(!copy_head) {
                copy_head = temp->next;
                copy_tail = copy_head;
            }
            else {
                copy_tail->next = temp->next;
                copy_tail = copy_tail->next;
            }
            // disconnect the cloned node
            temp->next = (temp->next)->next;
            temp = temp->next;
        }
        
        return copy_head;
    }
    
    // Solution 2
    // TC: O(N), SC: O(N)
    // Deep copy using Hashing
    Node* deepCopyHashing(Node* head) {
        // create a new linked list for each of the nodes and
        // maintain a hash table to map original and its copy
        Node* copy_head = nullptr, *copy_tail = nullptr;

        if(!head)
            return copy_head;

        // first node
        copy_head = new Node(head->val);
        copy_tail = copy_head;
        unordered_map<Node*, Node*> m;
        m[head] = copy_head;
        
        Node* temp = head->next;
        while(temp) {
            // create a node  
            Node* node = new Node(temp->val);
            copy_tail->next = node;
            copy_tail = node;
            // map the original and its copy
            m[temp] = node;
            temp = temp->next;
        }

        // set the random pointers
        temp = head;
        while(temp) {
            m[temp]->random = m[temp->random];
            temp = temp->next;
        }
        return copy_head;
    }

    
    Node* copyRandomList(Node* head) {
        // Using hashing
        //return deepCopyHashing(head);
        return copyRandom1(head);
    }
};


