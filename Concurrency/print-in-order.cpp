/*
    https://leetcode.com/problems/print-in-order/
    
    We use the following:
    1. mutex: This is an exclusive lock that only one thread can hold at a time
    2. unique_lock: This is a self unlocking variant of lock, that automatically unlocks when out of scope
    3. condition_variable: This is for thread synchronization. Threads can wait on a CV and can only acquire the
        lock when the condition is met.
        
    We use a var turn that stores which thread should be executing at the moment. Initially it is set to 1, so first() ca
    execute.
    The other threads wait on the condition_variable cv and each has the predicate condition turn == their_execution_order.
    Even if a thread eg second() acquires the lock first, ones it goes to predicate and that returns false, it will release the lock.
    
    Each time a thread finishes working, it updates turn with next value and notifies the other threads via CV mechanism.
*/
class Foo {
private:
    mutex mtx;
    condition_variable cv;
    // turn indicates which thread should run
    int turn = 0;
public:
    Foo() {
        // indicates that first thread should run
        turn = 1;
    }

    void first(function<void()> printFirst) {
        // acquire the lock so that there are no interruptions
        unique_lock<mutex> lock(mtx);
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        
        // Since first() is done, we can make the condition for second() true and
        // notify
        turn = 2;
        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> lock(mtx);
        // It will only be able to acquire the lock first() is done executing
        cv.wait(lock, [this] { return turn == 2; });
        
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        
        // make the condition for 3rd true so that it can execute 
        turn = 3;
        cv.notify_all();
    }

    void third(function<void()> printThird) {
        unique_lock<mutex> lock(mtx);
        // It will only be able to acquire the lock second() is done executing
        cv.wait(lock, [this] { return turn == 3; });
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};

/*
class Foo {
private:
    mutex mtx;
    condition_variable cv;
    // first_done indicates whether first() has finished executing or not
    // second done indicates whether second() has finished executing or not
    atomic<bool> first_done = false, second_done = false;
public:
    Foo() {
    }

    void first(function<void()> printFirst) {
        // acquire the lock so that there are no interruptions
        unique_lock<mutex> lock(mtx);
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        
        // Since first() is done, we can make the condition for second() true and
        // notify
        first_done = true;
        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> lock(mtx);
        // It will only be able to acquire the lock first() is done executing
        cv.wait(lock, [this] { return first_done == true; });
        
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        
        // make the condition for 3rd true so that it can execute 
        second_done = true;
        cv.notify_all();
    }

    void third(function<void()> printThird) {
        unique_lock<mutex> lock(mtx);
        // It will only be able to acquire the lock second() is done executing
        cv.wait(lock, [this] { return second_done == true; });
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};
*/
