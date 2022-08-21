/*
    https://leetcode.com/problems/largest-palindromic-number/
    
    TC: O(N)
    SC: O(N)
    
    Idea is to put the chars with largest digits first and then put the next largest next.
    Now for a given largest, two cases:
    1. Even: Put count/2 chars at front and back
    2. Odd: We take out the even instances and put them. Put (count - 1) / 2 chars at front and back
    
    Now to increase the length of the string, we can add a single odd instance at the center as well, 
    so track the biggest such instance.
    
    Handle 0 cases, might get a string with all 0s etc.
    
    Eg "444947137"
    9: 1, 7: 2, 4: 4, 3: 1, 1: 1
    Put the largest ones first
    digit = 9 has length of 1, so cant put, max_odd = 9
    digit = 7 => 7...7, max_odd = 9
    digit = 4 => 744.447, max_odd = 9
    digit = 3 => Cant put since freq 1, max_odd = 9
    digit = 1 => cant put since freq 1, max_odd = 9
    7449447, put the max_odd at the center
    
*/
class Solution {
public:
    string largestPalindromic(string num) {
        // Find the char freq for the string
        map<char, int, greater<int>> freq;
        // Tracks the max odd freq char, init to '#' to indicate empty
        char max_odd = '#';
        // To make insertions efficient, we keep two strings
        // front tracks the [0, N/2] and back tracks [N-1, N/2]
        // Insertions are made at the back. 'back' needs to be reversed later to get [N/2, N-1]
        string front, back;
        
        // Find the freq map
        for(auto digit: num)
            ++freq[digit];
        
        // edge case: If all 0s present, eg 00000
        if(freq.size() == 1 && freq.begin()->first == '0')
            return "0";
        
        for(auto [digit, c]: freq) {
            // If 0 is the only char and no other string
            if(digit == '0' && front.empty())
                continue;
            
            // If the length is odd, take out the even chars if possible
            if(c % 2) {
                // if no max odd char seen so far
                if(max_odd == '#')
                    max_odd = digit;
                // check if current char can be the max odd char
                else if(digit > max_odd)
                    max_odd = digit;
                // Put the even no. of char instances to the front and back of string
                if(c > 1) {
                    int even_len = c - 1;
                    for(int i = 0; i < even_len/2; i++)
                        front += digit, back += digit;
                }
            }
            // If even length, put c/2 to both front and back
            if(c % 2 == 0) 
                for(int i = 0; i < c/2; i++)
                    front += digit, back += digit;
        }
        // reverse to get [N/2, N-1]
        reverse(back.begin(), back.end());
        // If we have an odd length max char, put it
        if(max_odd != '#')
            front += max_odd;
        
        return front + back;
    }
};
