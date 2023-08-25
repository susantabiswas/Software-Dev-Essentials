/*
    https://leetcode.com/problems/fizz-buzz-multithreaded/
    
    Condition variable is used to make each thread wait till their print condition is true.
    Also it is important that a thread is allowed to pass the CV if i > n, as we no longer
    have anything to print.
*/
class FizzBuzz {
private:
    int n;
    int i = 1;
    mutex mtx;
    condition_variable cv;
public:
    FizzBuzz(int n) {
        this->n = n;
    }
    
    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        unique_lock<mutex> lock(mtx);
        
        while(true) {
            cv.wait(lock, [this]{ return i > n || (i % 3 == 0 && i % 5 != 0); });
            
            if(i > n)
                break;
            
            printFizz();
            ++i;
            cv.notify_all();
        }
        cv.notify_all();
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        unique_lock<mutex> lock(mtx);
        
        while(true) {
            cv.wait(lock, [this]{ return i > n || (i % 3 != 0 && i % 5 == 0); });
            
            if(i > n)
                break;
            
            printBuzz();
            ++i;
            cv.notify_all();
        }
        cv.notify_all();
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        unique_lock<mutex> lock(mtx);
        
        while(true) {
            cv.wait(lock, [this]{ return i > n || (i % 3 == 0 && i % 5 == 0); });
            
            if(i > n)
                break;
            
            printFizzBuzz();
            ++i;
            cv.notify_all();
        }
        cv.notify_all();
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        unique_lock<mutex> lock(mtx);
        
        while(true) {
            cv.wait(lock, [this]{ return i > n || (i % 3 != 0 && i % 5 != 0); });
            
            if(i > n)
                break;
            
            printNumber(i);
            ++i;
            cv.notify_all();
        }
        cv.notify_all();
    }
};
