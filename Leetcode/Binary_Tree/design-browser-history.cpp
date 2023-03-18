/*
    https://leetcode.com/problems/design-browser-history/
    
    There can be various designs for this like using a doubly linked list etc.
    Here we will use a height balanced tree to make the back and forward operations fast.
    
    Idea is to keep a height balanced tree with key as history index and its value will
    be the homepage. The indexing for history starts from 0 and goes on 1, 2...
    
    Lets say this is the current state of history: 1, 2, 3(curr), 4, 5, 6, 7
    Now if a page is visited (curr = 4) then the history is invalid beyond index 4.
    Instead of deleting the keys, we can later use them. We can use a var end_idx to track the 
    valid last index in history.
    
    visit()
        TC: O(logn)
    
    back()
        TC: O(logn)
        
    forward()
        TC: O(logn)
    
    SC: O(n)
    
    where n is the total no. of entries in history
*/
class BrowserHistory {
private:
    int curr = -1; // Currently tracked index
    int end_idx = -1; // Last valid url index
    // <index, url>
    map<int, string> pages;
public:
    BrowserHistory(string homepage) {
        pages[++this->curr] = homepage;
        this->end_idx = this->curr;
    }
    
    void visit(string url) {
        // Add the current url, end index of history
        // now points to this url index since all
        // the history will now be invalid after this index
        pages[++this->curr] = url;
        this->end_idx = this->curr;
    }
    
    string back(int steps) {
        // get the first index
        int first = pages.begin()->first;
        int history_idx = this->curr - steps;
        
        // Get the valid index from history
        string page = history_idx >= first ? pages[history_idx] : pages[first];
        this->curr = history_idx >= first ? history_idx : first;
        
        return page;
    }
    
    string forward(int steps) {
        int history_idx = this->curr + steps;
        
        string page = history_idx <= this->end_idx ? pages[history_idx] : pages[this->end_idx];
        this->curr = history_idx <= this->end_idx ? history_idx : this->end_idx;
        
        return page;
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */
