/*
    https://leetcode.com/problems/online-stock-span/
    
    TC: 
        next: O(N), happens only once when all the elements are in decreasing order
                    and last one is the biggest.
            Ammortised: O(1)
            
    SC: O(N)
        Ammortised: O(1)
        
*/
class StockSpanner {
private:
    // Element with its entry number
    struct BiggerElement {
        int pos = 0;
        int data = 0;
        BiggerElement(int pos, int data): pos(pos), data(data) {};
    };
    // to keep track of last bigger element
    stack<BiggerElement> span_;
    // to keep track of order in which elements are pushed
    int idx_ = 0;
public:
    StockSpanner() {
        
    }
    
    int next(int price) {
        // We use a stack to keep track of last largest element
        // So if the new element is smaller it is pushed and if it is
        // bigger than the stack top, we pop elements till stack top is empty
        // or bigger than current
        while(!span_.empty() && span_.top().data <= price)
            span_.pop();
        
        // if the stack is empty, means all the previous elements were smaller
        int span_elements = span_.empty() ? idx_ + 1 : idx_ - span_.top().pos;
        span_.emplace(BiggerElement(idx_, price));
        ++idx_;
        
        return span_elements; 
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
