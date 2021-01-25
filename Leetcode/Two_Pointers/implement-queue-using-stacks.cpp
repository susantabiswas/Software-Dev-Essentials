/*
    https://leetcode.com/problems/implement-queue-using-stacks/submissions/
    
    Idea is to use two stacks, one incharge of enqueue and other for dequeue operation.
    The enqueue stack accepts the elements in O(1).
    For dequeue, we check if the dequeue stack isempty or not, ifnot empty
    we transfer all the elements from enqueue stack so that the oldest element
    comes on top while popping and pushing the elements.
    Dequeue: O(N)
*/
class MyQueue {
    stack<int> push_s, pop_s;
    
public:
    /** Initialize your data structure here. */
    MyQueue() {
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        push_s.push(x);    
    }
    
    void transfer_elements() {
        // transfer the elements from push stack to pop
        while(!push_s.empty()) {
            pop_s.push(push_s.top());
            push_s.pop();
        }    
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if(pop_s.empty()) 
            transfer_elements();
        
        int popped = pop_s.top();
        pop_s.pop();
        return popped;
    }
    
    /** Get the front element. */
    int peek() {
        if(pop_s.empty()) 
            transfer_elements();
        
        return pop_s.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return push_s.empty() && pop_s.empty();    
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
