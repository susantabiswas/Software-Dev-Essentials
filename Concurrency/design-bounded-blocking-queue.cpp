/*
    https://leetcode.com/problems/design-bounded-blocking-queue/
    
    Idea is use pessimistic concurrency control. Whenever there is modification
    operation on the queue, acquire the lock and perform the operation.
    
    Condition variable is used to check if the operation should be allowed or not.
    For enqueue the condition is that the queue should not be full
    For dequeue the condition is that the queue should not be empty
    
    Also since CV is used, make sure to notify the other threads once the operation
    is performed.

    Note - Perf implications
    Since all the threads will be adding an element only, they all are equals.
    So it is better to use Cv.notify_all() as that only one thread is woken up instead of 
    all the threads waking up and then again going back to sleep.
*/

class BoundedBlockingQueue {
private:
    mutex mtx;
    condition_variable cv;
    list<int> data_queue;
    int capacity = 0;
public:
    BoundedBlockingQueue(int capacity) {
        this->capacity = capacity;
    }
    
    void enqueue(int element) {
        unique_lock<mutex> lock(mtx);
        // only allow enqueue if the queue has leftover capacity
        cv.wait(lock, [this]{ return data_queue.size() < capacity; });
        data_queue.push_front(element);
        
        // since the threads are waiting on CV and will sleep once the predicate is
        // false, notify them again
        // Read Note:Perf implications in the start
        cv.notify_one();
    }
    
    int dequeue() {
        unique_lock<mutex> lock(mtx);
        // only allow dequeue if the queue is not empty
        cv.wait(lock, [this]{ return data_queue.size() > 0; });
        int data = data_queue.back();
        data_queue.pop_back();

        // Read Note:Perf implications in the start
        cv.notify_one();
        
        return data;
    }
    
    int size() {
        return data_queue.size();
    }
}; 
