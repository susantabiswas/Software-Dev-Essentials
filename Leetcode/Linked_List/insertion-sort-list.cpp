/*
    https://leetcode.com/problems/insertion-sort-list/submissions/
    
    With dummy head approach.
    TC: O(N)
    SC: O(1)
*/

class Solution {
public:
    // put the current node at its correct position
    // dummy_node never changes, since we add the node after 
    // all repeated elements if there so even  if cur is INT_MIN it will
    // come after dummy_head, so no need to return
    void positionNode(ListNode* head, ListNode* curr) {
        ListNode *prev = nullptr;
        while(head && head->val <= curr->val) {
            prev = head;
            head = head->next;
        }
        prev->next = curr;
        curr->next = head;
        
    }
    
    ListNode* insertionSortList(ListNode* head) {
        // we use another list to which is supposed to contain only the sorted
        // nodes, since we are not using an array it is easier this way
        ListNode *dummy_head = new ListNode(INT_MIN), *curr = nullptr;
        ListNode *sorted_head = nullptr;
        
        curr = head;
        // for each of the nodes in current list, check the position 
        // it belongs in the sorted list and put it there
        while(curr) {
            ListNode *nextptr = curr->next;
            curr->next = nullptr;
            positionNode(dummy_head, curr);
            curr = nextptr;
        }
        
        sorted_head = dummy_head->next;
        delete dummy_head;
        return sorted_head;
    }
};

////////////// Without dummy head
class Solution {
public:
    void placeNode(ListNode* &sorted, ListNode* &node) {
        ListNode *curr = sorted, *prev = nullptr;
        // find the position to place the node
        while(curr && curr->val < node->val) {
            prev = curr;
            curr = curr->next;
        }
        
        // insert the node at its correct position
        node->next = curr;
        // when it is the smallest and should be at head pos.
        if(prev) 
            prev->next = node;
        else 
            sorted = node;
    }
    
    // TC: O(N^2)
    ListNode* insertionSortList(ListNode* head) {
        // Sorted list of nodes
        ListNode *sorted = nullptr;
        ListNode *curr = head, *next_ptr = nullptr;
        
        while(curr) {
            // save the next node info and remove it from current list
            next_ptr = curr->next;
            curr->next = nullptr;
            placeNode(sorted, curr);
            // goto next node
            curr = next_ptr;
        }
        
        return sorted;
    }
};
