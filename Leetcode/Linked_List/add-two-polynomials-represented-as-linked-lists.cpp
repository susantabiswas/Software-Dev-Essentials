/*
    https://leetcode.com/problems/add-two-polynomials-represented-as-linked-lists/
    
    TC: O(m + n)
    SC: O(1)
    
    Simply traverse both the list together, adding the coefficeint only when the powers 
    are same. When the powers are diff, add the node with higher power first and move that
    forward.
    Edge case: 0 coefficient component shouldnt be put.
*/
/**
 * Definition for polynomial singly-linked list.
 * struct PolyNode {
 *     int coefficient, power;
 *     PolyNode *next;
 *     PolyNode(): coefficient(0), power(0), next(nullptr) {};
 *     PolyNode(int x, int y): coefficient(x), power(y), next(nullptr) {};
 *     PolyNode(int x, int y, PolyNode* next): coefficient(x), power(y), next(next) {};
 * };
 */

class Solution {
public:
    // Adds a node to the end of list
    void addToLast(PolyNode* node, PolyNode*& last) {
        last->next = node;        
        // update the last ptr
        last = last->next;
        // disconnect the newly added node from its next node
        last->next = nullptr;
    }
    
    PolyNode* addPoly(PolyNode* poly1, PolyNode* poly2) {
        // Adding a dummy head for code convenience
        PolyNode* head = new PolyNode(-1, -1);
        PolyNode* last = head;
        
        while(poly1 && poly2) {
            // We can add the coefficient only when the powers are same
            if(poly1->power == poly2->power) {
                // instead of allocating memory for a new node,
                // utilize the existing node and update the coeff value
                poly1->coefficient += poly2->coefficient;
                PolyNode* curr_node = poly1;
                
                // move both the ptrs to point to the next element
                poly1 = poly1->next;
                poly2 = poly2->next;
                
                // add the last ptr only when the coefficient is not zero
                if(curr_node->coefficient != 0)
                    addToLast(curr_node, last);
            }
            // Move the polynomial with bigger power, since that might have a smaller matching power
            // component and also bigger powers need to come first 
            else if(poly1->power > poly2->power) {
                PolyNode* curr_node = poly1;
                poly1 = poly1->next;
                addToLast(curr_node, last);
                
            }
            else {
                PolyNode* curr_node = poly2;
                poly2 = poly2->next;
                addToLast(curr_node, last);
            }
        }
        
        // Add the remaining components of polynomial 1
        while(poly1) {
            PolyNode* curr_node = poly1;
            poly1 = poly1->next;
            addToLast(curr_node, last);
        } 
        
        // Add the remaining components of polynomial 2
        while(poly2) {
            PolyNode* curr_node = poly2;
            poly2 = poly2->next;
            addToLast(curr_node, last);
        }
            
        // delete the dummy head
        PolyNode* dummy_head = head;
        head = head->next;
        delete dummy_head;
        
        return head;
    }
};
