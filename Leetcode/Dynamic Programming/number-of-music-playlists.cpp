/*
    https://leetcode.com/problems/number-of-music-playlists/
    
    TC: O(goal * min(n, goal))
    SC: O(goal * n)
    
    Given a length of playlist 'm' and some unqiue songs 'n', we time we can do 2 things:
    
    For the given length `i` and total available `j` uniq songs
    1. Add a new song out of these unique songs (which is, the only song except for already used j-1 songs)
        to all the diff playlists of size `i-1`
    2. Replay an already played song such that we don't play the last k songs and add it to
        all the playlists of size `i-1` that
*/
class Solution {
public:
    int numMusicPlaylists(int n, int goal, int k) {
        const long MOD = pow(10, 9) + 7;
        
        // dp[i][j] = no. of playlists with length 'i' and no. of unique songs 'j'
        // used atleast once
        vector<vector<long>> dp(goal + 1, vector<long>(n + 1, 0));
        
        // only one way of creating a playlist of len 0 and unique songs 0
        // i.e to have an empty playlist
        dp[0][0] = 1;
        
        for(int len = 1; len <= goal; len++)
            // if len < unique_songs, we can't create a playlist using all the songs
            // as the playlist length is smaller, so dp[i][j] = 0.
            // Hence we don't compute beyond min(len, n) in case len < n, we will have dp[len][unique_songs] = 0
            for(int unique_songs = 1; unique_songs <= min(len, n); unique_songs++) {
                // If we use a new song as the ith song, then we can add this to all
                // the previous playlists with len-1 that had only `unique_songs-1` songs and
                // we can add any song out of (n - len|previously used uniq songs|)
                long new_song = (dp[len-1][unique_songs-1] * (n - (unique_songs-1))) % MOD;
                
                // We replay a song out of available `unique_songs` no. of songs.
                // Since between each repeated song there should be k other songs, we
                // can't use the last k songs out of `unique_songs`
                long replay_song = (dp[len-1][unique_songs] * (unique_songs - k)) % MOD;
                
                dp[len][unique_songs] = (new_song + (unique_songs > k ? replay_song : 0)) % MOD;
            }
        
        return dp[goal][n];
    }
};
