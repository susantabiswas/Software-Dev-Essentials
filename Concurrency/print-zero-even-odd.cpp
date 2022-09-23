/*
    https://leetcode.com/problems/print-zero-even-odd/
    
    We use condition variable to sync the threads.
    We track the current num to print with a var and a bool flag that indicates whether
    we want to print 0. 
    The zero thread only acquires the lock when flag is set. Odd and even only acquire the
    lock when the number is either even or odd.
    
    Also thing to note is a thread upon the end of an iteration will not wait to enter the loop
    again as long as the loop condition is true. So it might enter with an old value and just be 
    waiting to acquire the lock. We need to ensure that it exist when the n reaches 0 i.e
    we dont have any other number to print. So we put a break condition there.
    
    Also the threads waiting need to get a chance to acquire the lock and reach the break condition,
    because 0 thread will be the last one to print and then it reaches the break condition and exits,
    but the other threads will still be waiting and hence we put n <= 0 condition in cv predicate as 
    well so that at the end they can acquire the lock and reach the break condition and exit execution.
*/
class ZeroEvenOdd {
private:
    int n;
    mutex mtx;
    condition_variable cv;
    // Current number to print
    int num = 1;
    // whether to print 0
    bool print_zero = true;
public:
    ZeroEvenOdd(int n) {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        while(n > 0) {
            unique_lock<mutex> lock(mtx);
            
            // only acquires the lock when print_zero flag is set
            cv.wait(lock, [this] { return print_zero; });
            
            if(n <= 0)
                break;
            printNumber(0);
            
            // Now that 0 is printed, we print the actual number
            // ++num;
            print_zero = false;
            cv.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {
        while(n > 0) {
            unique_lock<mutex> lock(mtx);
            
            // here !print_Zero is there because num starts from 0, which is even and hence
            // initially without this condition the cv condition would become true and it might print itself
            // before 0
            // we have n <= 0 because the thread will enter the next iteration as soon as it reaches the end of loop
            // but then will get stuck at the cv.wait line. So once the last thread is done processing n becomes 0 and we shouldnt
            // process further. Further more, that thread will reach the break condition and will exit but the other threads
            // will keep waiting. So with this condition each thread will have an opportunity to acquire the lock
            // and continue and reach the break condition
            cv.wait(lock, [this]{ return (!print_zero && num % 2 == 0) || n <= 0; });
            if(n <= 0)
                break;
            // even number, so print it
            printNumber(num);
            --n;
            ++num;
            // now that a number is printed, we need to print 0 again, so set its flag
            print_zero = true;
            cv.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
        while(n > 0) {
            unique_lock<mutex> lock(mtx);
            
            // acquire the lock only when the current number is odd
            cv.wait(lock, [this]{ return (!print_zero && num % 2) || n <= 0; });
            if(n <= 0)
                break;
            
            // print the odd number
            printNumber(num);
            --n;
            ++num;
            // now that a number is printed, we need to print 0 again, so set its flag
            print_zero = true;
            cv.notify_all();
        }
    }
};
