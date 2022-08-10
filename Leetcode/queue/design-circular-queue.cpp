/*
    https://leetcode.com/problems/design-circular-queue/
    
    Idea is to keep two pointers, one which tracks the first element inserted in queue
    and the other which points to the position where the last element was written.
    To make it act in a circular fashion we make use of % QUEUE_CAPACITY each time 
    we want to move the front or back pointer index.
    
    TC: Enqueue = Dequeue = O(1)
    
*/
class MyCircularQueue {
private:
    vector<int> q_;
    // Total capacity of queue
    int capacity_ = 0;
    // Number of elements in queue at any given time
    int num_elements_ = 0;
    // back index: where last element was written, front: where the first element is
    int rear_ = -1, front_ = 0;
     
public:
    MyCircularQueue(int k) {
        capacity_ = k;
        // resize the vector with the req size
        q_.resize(k, 0);
    }
    
    bool enQueue(int value) {
        /*
            If queue is not full, add the elements by moving the 
            rear index towards right/clockwise.
        */
        if(isFull())
            return false;
        rear_ = (rear_ + 1) % capacity_;
        q_[rear_] = value;
        ++num_elements_;
        return true;
    }
    
    bool deQueue() {
        /*
            If queue is not empty, move the front index clockwise
            and update the num_elements counter
        */
        if(isEmpty())
            return false;
        front_ = (front_ + 1) % capacity_;
        --num_elements_;
        return true;
    }
    
    int Front() {
        return isEmpty() ? -1 : q_[front_];
    }
    
    int Rear() {
        return isEmpty() ? -1 : q_[rear_];
    }
    
    bool isEmpty() {
        return num_elements_ == 0;
    }
    
    bool isFull() {
        return num_elements_ == capacity_;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
