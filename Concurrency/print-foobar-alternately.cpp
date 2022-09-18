/*
    https://leetcode.com/problems/print-foobar-alternately/
    
    We use a condition variable so that both the threads can wait on that.
    Now we use a boolean flag that indicates whether it's foo or bar's turn to print.
    This flag is used in the predicate function of condition variable.
    
    Initially flag is set so that foo is printed, then it is made false so that bar is printed. Bar thread upon execution makes it true again so that foo can be executed.
*/
class FooBar {
private:
    int n;
    mutex mtx;
    condition_variable cv;
    // Indicates whether it is foo or bar's turn.
    // true means it is foo's turn
    bool print_foo = true;
public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            // declare the lock and wait on condition variable
            // This thread will be executed only if it is foo's turn
            unique_lock<mutex> lock(mtx);
        	cv.wait(lock, [this] { return print_foo; });
            
            // printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            
            // reset foo's printing turn and make it false so that bar is printed
            print_foo = false;
            // notify the waiting bar thread
            cv.notify_one();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            // execute only if it is bar's turn
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this] { return !print_foo; });
        	
            // printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            
            // now it will be foo's turn to execute
            print_foo = true;
            cv.notify_one();
        }
    }
};
