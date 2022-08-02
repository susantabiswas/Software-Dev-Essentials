/*
    https://leetcode.com/problems/design-a-stack-with-increment-operation/
    
    Push and pop are simple to do with O(1), problem is with increment operation
    that can take O(k) if done naively each time.
    To make that faster, we can use a hash table that can save the increment needed
    till elements of stack from position: 0 -> position
    Eg: if increment(2): then we can set hash_table[2] = value
    Now a check for incremented value can only be ensured with a pop operation
    in a stack, so we update the popped value. During pop, we check the additional
    value needed for the element with that index, it might happen that the current position
    is lesser than the position for which the increment update was done in hash table and
    hence the current position in hash table is not aware that it should have some increment
    amount. The optimization lies in this problem, if we simply look for the first updated
    value position in hash table after the current stack top position, O(max_size) worst case.
    So each time when we do a pop, we make sure to pass the value to its immediate left index
    and we do the same each time during a pop.
    This ensures that the index in hash table for any pop operation is always updated.
    
    Eg: Stack: 1, 2 
    Hash Table: 
    
    inc(2, 100): Hash Table: <2, 100> // Notice how oonly index 2 is set and not index 1
    pop(): Stack: 1
        Hash Table: 
            #Step 1: <1, 0> + <2, 100> = <1, 100> : Pass the increment value to lower index
            #Step 2: <2, 0>: Reset value for index which has passed
    
    TC: Push: O(1), Pop: O(1), increment: O(1)
    SC: O(max_size)
*/
class CustomStack {
    int max_size = 0;
    vector<int> s;
    int top = 0;
    // This saves the increment value set for 
    // till each position
    unordered_map<int, int> additional_val;
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
        int increment_val = additional_val[top];
        // propagate the increment to lower indices, since all lower 
        // position elements should also have component of this increment
        additional_val[top-1] += increment_val;
        // reset the increment for till this position caused
        // by incrment() for this position
        additional_val[top] = 0;
        return increment_val + s[--top];
    }
    
    void increment(int k, int val) {
        // find the effective K based on actual number of elements
        k = min(k, top);
        additional_val[k] += val;
    }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */
