/*
    https://leetcode.com/problems/maximize-number-of-subsequences-in-a-string/
    
    TC: O(N)
    SC: O(1)
    
    Idea:
    1st question to answer is where is the optimal pos for either of pattern chars.
    The ans is either at front or back, this is because, when a subseq is matched it goes from
    left to right of chars in pattern. Lets say we are talking for pattern[0], if it is put at
    pos 'i' in text, then if there are any instances of pattern[1] before 'i', those will be missed.
    So pattern[0] needs to be placed at front so that all the instances of pattern[1] are after it.
    Same logic for placement of pattern[1] at back.
    
    Once that is done, it's easy. Either we can actually make two such strings and then use the DP subsequence
    logic to find which new string has more sub seqs. 
        But since this pattern has only 2 chars, we can do better. We track the no. of instances of pattern[0]
    and whenever an instance of pattern[1] is found, we can combine that with the number of pattern[0] instances 
    found so far in the str. This way we can find the number of subseqs.
    Also we track counts of patter[0] and pattern[1] resp. Since we can add 1 instance of either of those, so 
    we check which instance has the highest count currently and then combine the other char of subseq so that we get more no.
    of subsequences.
*/
class Solution {
public:
    long long maximumSubsequenceCount(string text, string pattern) {
        // Keeps track of count of patt[0] and patt[1] resp.
        long n_patt0 = 0, n_patt1 = 0;
        long sub_sequences = 0;
        // Find all the subsequences that exist without the addition of 
        // any chars of pattern
        for(int i = 0; i < text.size(); i++) {
            // if the second char is found, all the instances of 1st char
            // can create a subseq with this char
            if(text[i] == pattern[1]) {
                sub_sequences += n_patt0;
                ++n_patt1;
            }
            if(text[i] == pattern[0])
                ++n_patt0;
        }
        // Since we can add either patt[0] or patt[1], so whichever
        // has the highest existing count in the str can be combined with the
        // other needed char of subseq from pattern
        return sub_sequences + max(n_patt0, n_patt1);
        
    }
};
