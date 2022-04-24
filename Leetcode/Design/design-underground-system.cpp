/*
    https://leetcode.com/problems/design-underground-system/
    
    TC:
    checkIn: O(1)
    checkOut: O(1)
    getAverageTime: O(1)
    
    Idea is to have 2 hash tables, one for storing the travel records, mapped by customerId.
    Another which has <startStation, endStation> as key and value is <sample_count, sum_total_elapsed_time>.
    
    The second hash table records completed trip data, instead of computing avg each time a new record is inserted,
    we store the sample_count (n) and total_sum of travel time for that station pair.
    
    Whenever we get a record in checkOut, we look for the customerId in the checkin_records, then we compute the
    travel time by retrieving the checkin time and current station's checkout time. Save this info in the avg_time 
    hash table for later computation.
*/
class UndergroundSystem {
private:
    // custom comparator for C++ unordered_map of pair as key
    struct Comparator {
        template<class T1, class T2>
        size_t operator()(const pair<T1, T2>& p) const {
            auto hash1 = hash<T1>{}(p.first);
            auto hash2 = hash<T2>{}(p.second);
            // unequal hash will have non-zero value
            if(hash1 != hash2)
                return hash1 ^ hash2;
            return hash1;
        }
    };
    
    // <CustomerId, <CheckInStation, time> >
    unordered_map<int, pair<string, int>> checkin_records;
    // <StartStationName, <total_records, sum_total_travel_time> >
    unordered_map<pair<string , string>, pair<int, long long>, Comparator> avg_time;
    
public:
    UndergroundSystem() {
    }
    
    void checkIn(int id, string stationName, int t) {
        checkin_records[id] = make_pair(stationName, t);
    }
    
    void checkOut(int id, string stationName, int t) {
        // retrieve the checkin details of customer
        auto [start_station, checkin_time] = checkin_records[id];
        // if we are getting the startStation record for the 1st time for avg time 
        pair<string, string> itinerary = make_pair(start_station, stationName);
        // init for the given pair if it is the 1st time
        if(avg_time.count(itinerary) == 0) {
            avg_time[itinerary] = make_pair(0, 0);
        }
        // update the sample count and add the elapsed time to total
        avg_time[itinerary].first += 1;
        avg_time[itinerary].second += (t - checkin_time);
    }
    
    double getAverageTime(string startStation, string endStation) {
        auto itinerary = make_pair(startStation, endStation);
        // compute the avg on the fly
        return (double) avg_time[itinerary].second / avg_time[itinerary].first;
    }
};

/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */
