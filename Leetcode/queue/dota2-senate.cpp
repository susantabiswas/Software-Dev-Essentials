// TC: O(kN), the simulation will run few times. Each time atleast half the members will get disabanded.
// SC: O(N)
class Solution {
public:
    string predictPartyVictory(string senate) {
        queue<int> dire, radiant;
        
        for(int i = 0; i < senate.size(); i++) {
            if(senate[i] == 'D')
                dire.push(i);
            else
                radiant.push(i);
        }
        
        bool stop = false, dire_wins = false, radiant_wins = false;
        
        // the 1st senate to vote will be from dire
        while(!stop) {
            for(int i = 0; i < senate.size() && !stop; i++) {
                // take 1 vote from each party
                if(!dire.empty() && i == dire.front()) {
                    // if the other party has no voting members, dire party wins
                    if(radiant.empty()) {
                        dire_wins = true;
                        stop = true;
                        break;
                    }
                    else {
                        // revoke the voting rights of the next eligible member
                        // from the other group
                        radiant.pop();
                    }

                    // queue this member to the voting order for its next turn
                    // so this member will again get the turn once all others have exercised 
                    // their vote once
                    dire.push(dire.front());
                    dire.pop();
                }

                if(!radiant.empty() && i == radiant.front()) {
                    // if the other party has no voting members, dire party wins
                    if(dire.empty()) {
                        radiant_wins = true;
                        stop = true;
                        break;
                    }
                    else {//cout<<"dire popped:"<<radiant.front()<<" by:"<<i<<endl;
                        // revoke the voting rights of the next eligible member
                        // from the other group
                        dire.pop();
                    }

                    // queue this member to the voting order for its next turn
                    // so this member will again get the turn once all others have exercised 
                    // their vote once
                    radiant.push(radiant.front());
                    radiant.pop();
                }
            }
        }    
        
        return dire_wins ? "Dire" : "Radiant";
    }
};
