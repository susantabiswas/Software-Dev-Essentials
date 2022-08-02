/*
    https://leetcode.com/problems/implement-stack-using-queues/
    
    Push: TC: O(N)
    Pop: TC: O(1)
    
    Idea is to use two queues, one which which can serve the functionalities of
    a stack and the other to facilitate. To mimic stack like behaviour we need to
    put the most recent element at the front of queue so that it can support stack pop.
    So current stack is one which keeps track of elements such that all the elements
    in it are in order: recent -> oldest. This makes the current stack do pop, top and isempty 
    functions.
    To have a queue with such arrangement of elements, we make sure that everytime during a 
    push we push the element in an empty queue, so that it is at the front and move all the 
    from the other queue with already ordered elements to current.
*/

class MyStack {
private:
    queue<int> q1, q2;
    queue<int> *curr = nullptr, *other = nullptr;
public:
    /** Initialize your data structure here. */
    MyStack() {
        // set the curr enqueue stack
        curr = &q2;
        // set the auxilliary queue used for swap
        other = &q1;
    }
    
    void transfer_elements() {
        // Transfers elements from auxilliary other queue to current
        while(!other->empty()) {
            curr->emplace(other->front());
            other->pop();
        }
    }
    
    /** Push element x onto stack. */
    void push(int x) {
        // make the empty stack as operational current stack
        swap(curr, other);
        // push the element in empty stack 
        // and set it as default
        curr -> emplace(x);
        transfer_elements();
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int popped = curr->front();
        curr->pop();
        return popped;
    }
    
    /** Get the top element. */
    int top() {
        return curr->front();
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return curr->empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
