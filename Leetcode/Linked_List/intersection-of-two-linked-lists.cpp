/*
    https://leetcode.com/problems/intersection-of-two-linked-lists/
    
    Solution1 : Using Stack
    Solution2: Two pointers
    
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
        Idea is to use store the elements of both the lists, it can either
        be in a stack or even a vector. Then iterate from the back side
        and traverse while the nodes in both the containers are same. The
        node before the first mismatched node is the intersection node.
        TC: O(N)
        SC: O(1)
    */
    ListNode *stackSol(ListNode *headA, ListNode *headB) {
        stack<ListNode*> sA, sB;
        // add all the elements of list A
        while(headA)
            sA.emplace(headA), headA = headA->next;
        // add all the elements of list B
        while(headB)
            sB.emplace(headB), headB = headB->next;
        // Find the first node that is not same
        ListNode *intersection_node = nullptr;
        while(!sA.empty() && !sB.empty() && sA.top() == sB.top()) {
            intersection_node = sA.top();
            sA.pop(), sB.pop();
        }
        
        return intersection_node;
    }
    
    /*
        SOLUTION 2
        
        Count the number of nodes in both the lists, idea is to move
        the delta gap distance between the lengths of two lists |M - N|.
        Once the iterator are at placed at starting points such that the
        number of nodes after that is same for both, we start the iteration 
        and stop when we come across a node which is same in both the list
        
        TC: O(N)
        SC: O(1)
    */
    int countNodes(ListNode *head) {
        int c = 0;
        while(head)
            ++c, head = head->next;
        return c;
    }
    
    ListNode *twoPointersSol(ListNode *headA, ListNode *headB) {
        // get the node counts for both the lists
        int count_a = countNodes(headA);
        int count_b = countNodes(headB);
        
        int delta = abs(count_a - count_b);
        // iterator for the longer list
        ListNode *it1 = count_a > count_b ? headA : headB;
        // iterator for the shorter list
        ListNode *it2 = it1 == headA ? headB : headA;
        // close the delta distance gap
        while(delta-- > 0)
            it1 = it1->next;
        
        // now traverse both the lists and look for the first match
        while(it1 && it2 && it1 != it2) 
            it1 = it1->next, it2 = it2->next;
        return it1 == it2 ? it1 : nullptr;
    }
    
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        // return stackSol(headA, headB);
        return twoPointersSol(headA, headB);
    }
};
