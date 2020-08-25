/*
    https://leetcode.com/problems/number-of-segments-in-a-string/
*/
class Solution {
public:
    int countSegments(string s) {
        int start = 0, end = 0;
        int segments = 0;
        // We use two ptrs, first will always be at the start of the word
        // second gies till a space is found, then the covered region is 
        // taken as a segment
        while(start < s.size()) {
            while(end < s.size() && s[end] != ' ')
                ++end;
            // check if the segment contains any chars 
            if(end != start)
                ++segments;
            // goto the next char after space
            ++end;
            start = end;
        }
        return segments;
    }
};
