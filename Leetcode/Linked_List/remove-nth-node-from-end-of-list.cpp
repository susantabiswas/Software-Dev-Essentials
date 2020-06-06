/*
    https://leetcode.com/problems/remove-nth-node-from-end-of-list/submissions/
    
    Idea is to traverse n nodes first, once reached we
    use another ptr which starts from beginning.
    Continue the traversal, moving both the ptrs.
    Once the traversal is finished the second ptr will on nth node from end.
    
    Corner case: If n is equal to length of list, then we need to delete 
    the first node.
    
    TC: O(N), SC: O(1)

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *prev = nullptr, *first = head, *second = head;
        
        // traverse n nodes
        while(first && n--) {
            first = first->next;
        }
        
        // continue the remaining traversal
        // traverse M - n nodes, M:list length
        while(first) {
            first = first->next;
            prev = second;
            second = second->next;
        }
        
        //check if head needs to be deleted
        ListNode *nth_last = nullptr;
        if(prev == nullptr) {
            nth_last = head;
            head = head->next;
        }
        else {
            nth_last = second;
            // remove the node
            prev->next = nth_last->next;
        }
        
        delete nth_last;
        
        return head;
    }
};
