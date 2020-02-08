/*
    https://leetcode.com/problems/word-ladder/
    TC: O(D * L * 26) ~ O(DL), D: distance of transformation, L: Length of longest word
*/
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // tracks unvisited words
        unordered_set<string> unvisited(wordList.begin(), wordList.end());
        queue<string> q;
        q.emplace(beginWord);
        // add to visited
        unvisited.erase(beginWord);
        // tracks the level in BFS
        int level = 0;
        // tracks no. of nodes in current level
        int level_nodes = q.size();
        while(!q.empty()) {
            string curr = q.front();
            q.pop();
        
            // if the current word is the target
            if(curr == endWord)
                return level + 1;
            // try reaching another word by replacing characters in different positions
            for(int i = 0; i < curr.size(); i++) {
                char curr_char = curr[i];
                // replace with a-z char
                for(int j = 0; j < 26; j++) {
                    // replace the char and check if that word is connected to the
                    // current word via a transformation(edge)
                    curr[i] = 'a' + j;
                    string next_word = curr;
                    // add the word to queue if it has not been visited and is part of dict
                    if(unvisited.find(next_word) != unvisited.end()) {
                        q.emplace(next_word);
                        // remove from unvisited
                        unvisited.erase(next_word);
                    }
                }    
                // restore the char
                curr[i] = curr_char;
            }
            
            --level_nodes;
            // end of nodes in current level
            if(level_nodes == 0) {
                ++level;
                level_nodes = q.size();   
            }
        }
        return 0;
    }
};
