/*
    https://leetcode.com/problems/rotate-list/
    
    TC: O(n)
    SC: O(1)
    
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head)
            return head;
        
        // Find the length of list
        ListNode* curr = head;
        int len = 0;
        while(curr)
            ++len, curr = curr->next;
        
        // find the net rotation required
        k = k % len;
        
        if(k == 0)
            return head;
        
        // go till the len-k th node (1 indexing)
        curr = head;
        for(int i = 0; i < len - k - 1 && curr; i++)
            curr = curr->next;
        
        // Save the position of next segment of list, this will be the final head
        ListNode* nxtptr = curr->next;
        // end the current segment as this will be at the end
        curr->next = nullptr;
        
        // go till the last node of 2nd segment so that the tail of 2nd segment
        // can be linked to the head of the 1st segment
        curr = nxtptr;
        while(curr->next)
            curr = curr->next;
        
        // (2nd segment) -> (1st segment)
        curr->next = head;
        
        return nxtptr;
    }
};
