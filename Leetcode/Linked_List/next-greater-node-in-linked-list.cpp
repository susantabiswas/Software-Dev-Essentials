/*
    https://leetcode.com/problems/next-greater-node-in-linked-list/
    
    The problem is basically find the next greater right element.
    But since this is a linked list we can't start traversing from right
    directly using index, so we reverse the list so that we start from right side.
    We use a stack to keep track of largest element on right side in the original list.
    
    For stack: for the current element, we check if the stack contains any elements <= current
    and pop those since the smaller elements will never be used as a next larger element because 
    of current being greater than those. So current is added such that the stack top is greater than current.
    TC: O(N), SC: (N)
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
    // Reverses a linked list
    ListNode* reverseList(ListNode* head) {
        ListNode *nextptr = nullptr, *prev = nullptr;
        while(head) {
            nextptr = head->next;
            head->next = prev;
            prev = head;
            head = nextptr;
        }
        return prev;
    }
    
    vector<int> nextLargerNodes(ListNode* head) {
        vector<int> result;
        
        // reverse the linked list
        ListNode *rev_head = reverseList(head);
        // Stack is used for keeping track of closest largest elements
        // Element is only inserted if stack is empty or top is greater
        stack<int> largest;
        
        while(rev_head) {
            // find the closest largest element
            while(!largest.empty() && largest.top() <= (rev_head->val))
                largest.pop();
            
            if(largest.empty())
                result.emplace_back(0);
            else
                result.emplace_back(largest.top());
            
            largest.emplace(rev_head->val);
            rev_head = rev_head->next;
        }
        
        // reverse the array to match the order
        reverse(result.begin(), result.end());
        return result;
    }
};
