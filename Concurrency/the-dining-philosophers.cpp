/*
    https://leetcode.com/problems/the-dining-philosophers/
*/
///////////////////////////// SOLUTION 3: Semaphore of n-1 size to prevent all n trying together
class Semaphore {
private:
	int count;
    mutex mtx;
    condition_variable cv;
	
public:
    Semaphore(int n = 0) : count(n) { }
    void Set(int n) { count = n; }
    void Signal() {
        unique_lock<mutex> lck(mtx);
        ++count;
        cv.notify_one();
    }
    void Wait() {
        unique_lock<mutex> lck(mtx);
        cv.wait(lck, [&](){ return count > 0; }); 
        --count;
    }
};

class DiningPhilosophers {
private:
    int n = 5;
    mutex forks[5];
    Semaphore semaphore;
public:
    
    DiningPhilosophers() {
        semaphore.Set(4);
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
		
        int left = philosopher;
        int right = (philosopher + 1) % n;
        
        semaphore.Wait();
        
         // attempt to acquire the locks for forks
        unique_lock<mutex> left_fork(forks[left]);
        unique_lock<mutex> right_fork(forks[right]);

        pickLeftFork();
        pickRightFork();
        eat();
        putLeftFork();
        putRightFork();    
        
        left_fork.unlock();
        right_fork.unlock();
        
        semaphore.Signal();
    }
};

///////////// SOLUTION 1: Less Performant
/*
class DiningPhilosophers {
private:
    int n = 5;
    mutex table;
    mutex forks[5];
    
public:
    DiningPhilosophers() {
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
		
        // acquire the table lock so that only this
        // thread can acquire the forks. Even if this can acquire
        // only one of the forks, this will prevent any other thread to acquire the
        // locks untill the thread that holds one of the forks this thread needs is returned
        unique_lock<mutex> table_lock(table);
        
        int left = philosopher;
        int right = (philosopher + 1) % n;
        // attempt to acquire the locks for forks
        unique_lock<mutex> left_fork(forks[left]);
        unique_lock<mutex> right_fork(forks[right]);
        
        pickLeftFork();
        pickRightFork();
        eat();
        putLeftFork();
        putRightFork();
    }
};
*/

//////////////////////////// SOLUTION 2: Prevent Deadlock
/*
class DiningPhilosophers {
private:
    int n = 5;
    mutex forks[5];
    
public:
    DiningPhilosophers() {
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
		
        
        int left = philosopher;
        int right = (philosopher + 1) % n;
        
        // The adjacent people try to acquire the forks in different order
        // this prevents a cycle dependency and in the worst case when all n-1 people
        // have acquired forks and blocked each other, the last one won't be able to
        // acquire any fork because of this ordering
        
        // for odd indexed person, they take the left and then the right
        if(philosopher % n) {
            // attempt to acquire the locks for forks
            unique_lock<mutex> left_fork(forks[left]);
            unique_lock<mutex> right_fork(forks[right]);

            pickLeftFork();
            pickRightFork();
            eat();
            putLeftFork();
            putRightFork();    
        }
        // for even indexed person, they take the right and then the left
        else {
            // attempt to acquire the locks for forks
            unique_lock<mutex> right_fork(forks[right]);
            unique_lock<mutex> left_fork(forks[left]);
        
            pickRightFork();
            pickLeftFork();
            eat();
            putRightFork();    
            putLeftFork();
        }
    }
};
*/
