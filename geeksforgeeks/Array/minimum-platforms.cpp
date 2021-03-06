/*
    https://practice.geeksforgeeks.org/problems/minimum-platforms/0
*/
#include <bits/stdc++.h>
using namespace std;

struct Event {
    string t;
    bool arrive = true;
    
    Event(string t, bool arrive): t(t), arrive(arrive) {};
};
int solve(vector<string>& arrival, vector<string>& depart) {
    // Create time events and sort in increasing order  
    
    vector<Event> events;
    
    for(int i = 0; i < arrival.size(); i++) {
        events.emplace_back(Event(arrival[i], true));
        events.emplace_back(Event(depart[i], false));
    }
    
    sort(events.begin(), events.end(), 
        [](Event &a, Event &b)->bool{
            return (a.arrive && a.t == b.t) ||
                (a.t < b.t);
        });
        
    int platforms = 0, max_platforms = 0;
    
    for(Event& event: events) {
        if(event.arrive)
            ++platforms;
        else
            --platforms;
        max_platforms = max(max_platforms, platforms);
    }
    return max_platforms;
}

int main()
{
    int t, n;
    cin >> t;
    while(t--) {
        cin >> n;
        vector<string> arrival(n), depart(n);
        
        for(int i = 0; i < n; i++)
            cin >> arrival[i];
        for(int i = 0; i < n; i++)
            cin >> depart[i];
            
        cout << solve(arrival, depart) << endl;
    }
	return 0;
}