/*
    https://leetcode.com/problems/palindrome-linked-list/
    Solution1: TC: O(n), SC: O(1)
    Solution2: TC: O(n), SC: O(n)
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
    /*  
        SOLUTION 1
    */
    // reverses the linked list
    ListNode* reverse(ListNode* head) {
        ListNode *temp = head, *prev = nullptr, *nextptr = nullptr;
        // traverse the list and reverse one node at a time
        while(temp) {
            // save next node value and make the current
            // node point to previous node
            nextptr = temp->next;
            temp->next = prev;
            prev = temp;
            temp = nextptr;
        }
        return prev;
    }
    
    // returns the middle node
    // For even list: middle is n/2th node(1 based indexing)
    // for odd list: middle is floor(n/2)
    ListNode* getMiddle(ListNode*& head, int& count) {
        ListNode *slow = head, *fast = head, *prev = slow;
        
        while(slow && fast && fast->next) {
            ++count;
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        // when there are odd number of nodes, fast doesnt become null
        count = fast ? (2 * count - 1) : 2 * count;
        return prev;
    }
    
    // checks if a linked list is palindromic
    bool isPalindrome(ListNode* head) {
        if(!head || !head->next)
            return true;
        
        int count = 0;
        // get the middle node 
        ListNode *middle = getMiddle(head, count);
        
        // break the first half of the list 
        ListNode *nextptr = middle->next;
        middle->next = nullptr;
        // reverse the first half of list
        ListNode *rev_head = reverse(head);
        
        // if number of nodes is odd, we skip the middle node
        // and start comparing the first head node and node after middle
        if(count % 2 != 0) nextptr = nextptr->next;
        // start traversal from the reversed head and the first node
        // after middle
        ListNode *t1 = rev_head, *t2 = nextptr;
        
        while(t1 && t2) {
            if(t1->val != t2->val)
                return false;
            t1 = t1->next;
            t2 = t2->next;
        }
        
        return true;
    }
    
    /*
        SOLUTION 2
    */
    /*
    bool isPalindromeSolution2(ListNode* head) {
        stack<ListNode*> s;
        
        ListNode *slow = head, *fast = head;
        
        // get the middle node
        while(slow && fast && fast->next) {
            s.push(slow);
            slow = slow->next;
            fast = fast->next->next;
        }
        // if there are odd number of nodes, we start with 
        // comparing the node after middle with the stack top node
        if(fast) 
            slow = slow->next;
        while(!s.empty()) {
            if(s.top()->val != slow->val)
                return false;
            slow = slow->next;
            s.pop();
        }
        
        return true;
    }
    
    bool isPalindrome(ListNode* head) {
        return isPalindromeHelper2(head);
    }
    */
};
