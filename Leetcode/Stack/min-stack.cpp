/*
    https://leetcode.com/problems/min-stack/submissions/
    
    TC: push/pop O(1)
    SC: O(N)
*/
class MinStack {
private:
    stack<int> s;
    stack<int> min_stack;

public:
    /** initialize your data structure here. */
    MinStack() {
    }
    
    void push(int x) {
        // push the element in stack
        s.push(x);
        // push the current element only if it is the smallest
        if(min_stack.empty() || min_stack.top() >= x)
            min_stack.push(x);
    }
    
    void pop() {
        if(!s.empty()) {
            int pop_el = s.top();
            s.pop();
            if(min_stack.top() == pop_el)
                min_stack.pop();
        }
    }
    
    int top() {
        return s.top();
    }
    
    int getMin() {
        return min_stack.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
