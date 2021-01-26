/*
  https://leetcode.com/problems/design-a-stack-with-increment-operation/
*/

// SOLUTION 2: Simple
// TC: Push:O(1), Pop: O(1), Increment: O(k)
class CustomStack {
    int max_size = 0;
    vector<int> s;
    int top = 0;
public:
    CustomStack(int maxSize) {
        max_size = maxSize;
        s.resize(max_size);
    }
    
    void push(int x) {
        if (top < max_size)
            s[top++] = x;
    }
    
    int pop() {
        if (top <= 0)
            return -1;
        return s[--top];
    }
    
    void increment(int k, int val) {
        for(int i = 0 ; i < k && i < top && i < max_size; i++)
            s[i] += val;
    }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */
