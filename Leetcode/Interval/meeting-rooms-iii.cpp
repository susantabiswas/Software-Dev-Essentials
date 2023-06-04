/*
    https://leetcode.com/problems/meeting-rooms-iii/
    
    TC: O(nlogn (sorting) + nlogn (heap push/pop))
    SC: O(n)
    
    This is a simulation problem, where if there is a free room avail for use, then
    use it while trying to get the room with the lowest index. Otherwise, take the room
    where the ongoing meeting will end the earliest and if multiple rooms will be avail at the same
    time, pick the one with the lowest room index.
    While checking if a room is avail is free or not is trivial, it might not be trivial to simulate
    waiting for a room to get a avail room. For this we just pick the meeting room where the meeting will end the
    earliest as we would have waited for that long. Then since the current meeting would take place there and has already gotten
    delayed, update its end time accordingly.
    
    1. Sort the meetings by start time.
    2. We use min heap to keep track of busy {end_time, room_idx} and free rooms {room_idx}.
    3. Intially all the rooms are available for use.
    4. for each meeting:
        - Mark any meeting room free whose end time has passed the start of current meeting
        - If a room is avail, take it.
        - If a room is not avail, get the room with the earliest meeting end time, we will
            use this room.
            
    5. Find the most used room
*/
class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        // sort the meetings by the start time
        sort(meetings.begin(), meetings.end());
        
        // custom comparator: when the end time is same, pick the room with a 
        // lower index
        auto comp = [&](const array<long long, 2>& a, const array<long long, 2>& b) {
            if(a[0] == b[0])
                return a[1] > b[1];
            return a[0] > b[0];
        };
        // Min heap of <meeting_end_time, room_id>
        priority_queue<array<long long, 2>, vector<array<long long, 2>>, decltype(comp)> busy_rooms(comp);
        
        // Min heap of <room_id>
        priority_queue<int, vector<int>, greater<int>> free_rooms;
        
        // <room_id, no_of_times_used>
        unordered_map<int, int> room_used;
        // tracks the most used room
        long long most_used = 0, most_used_room = 0;
        
        // Initially all the rooms are empty
        for(int room = 0; room < n; room++)
            free_rooms.push(room);
        
        for(auto meeting: meetings) {
            int start = meeting[0], end = meeting[1];
            
            // Check the update for all the busy rooms where the meeting have
            // finished and mark them available for use
            while(!busy_rooms.empty() && busy_rooms.top()[0] <= start) {
                int room = busy_rooms.top()[1];
                busy_rooms.pop();
                // mark the room as free again
                free_rooms.push(room);
            }
            
            // check if there is any vacant room for the meeting
            if(!free_rooms.empty()) {
                int room = free_rooms.top();
                free_rooms.pop();
                
                // mark the room as busy
                busy_rooms.push({end, room});
                ++room_used[room];
            } 
            // all the rooms are busy. Pick the room where the meeting will end the earliest
            else {
                auto [meeting_end, room] = busy_rooms.top();
                busy_rooms.pop();
                
                // When the current ongoing meeting will end in the room, 
                // this new meeting will start there after waiting for it to end
                // and hence its end time will also get delayed
                ++room_used[room];
                int duration = end - start;
                busy_rooms.push({meeting_end + duration, room});
            }
        }
        
        // find the most used room with lowest room index
        // if two rooms have the same freq count, pick the lower index one
        for(auto [room, used]: room_used) {
            if(used > most_used ||
              (used == most_used && room < most_used_room)) {
                most_used = room_used[room];
                most_used_room = room;
            }
        }
        return most_used_room;
    }
};
