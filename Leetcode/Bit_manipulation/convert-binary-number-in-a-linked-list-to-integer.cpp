/*
    https://leetcode.com/explore/featured/card/november-leetcoding-challenge/564/week-1-november-1st-november-7th/3516/
    
    Since the list contains the bits in LSB -> MSB fashion, we recurse the list 
    to reach the last node(LSB) and from there we set the bits for each position
    from LSB.
    TC: O(N)
    
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
    template <size_t N>
    void getNum(ListNode *head, int &pos, bitset<N> &num) {
        if(!head)
            return;
        getNum(head->next, pos, num);
        // set the current pos, position setting starts from LSB
        num[pos] = head->val == 1;
        ++pos;
    }
    
    int getDecimalValue(ListNode* head) {
        // We use a bitset for representing the number
        bitset<30> num;
        int pos = 0;
        getNum(head, pos, num);
        
        return (int)num.to_ulong();
    }
};
