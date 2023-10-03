/*
    https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    
    TC: O(n)
    SC: (1)
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
    ListNode* deleteMiddle(ListNode* head) {
        if(!head || !head->next)
            return nullptr;
        
        ListNode* slow = head, *fast = head;
        ListNode* prev = nullptr;
        
        while(slow && fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        // delete the middle node
        if(prev)
            prev->next = slow->next;
        
        delete slow;
        return head;
    }
};
