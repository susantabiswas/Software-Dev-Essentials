/*
    Pull style Feed: Here the feed is created each time a request is made.
                    This makes getFeed() costlier and other operations cheaper.
    
    - We use a global timestamp / order counter tweet_time, this is the timestamp 
    associated with each tweet.
    - We use a hash table to maintain the graph of people.
    - We use a hash table of <userId, set(<tweet_time, tweet_id>) >. The set is
    used to maintain the sorted order of tweets.
    
    TC:
    Twitter(): O(1)
    
    postTweet(): O(logm), m: max no. of tweets
        Add the tweet to user's set of tweets 
    
    getNewsFeed(): O(mlog10) + O(Nmlog10) + O(10)
        - We use a height balanced tree (set), to store the feed. The size
            is kept at 10, so each opeartion is O(log10) ~ O(1)
        - Add the tweets of current user to feed: O(m * log10)
        - Add the tweets of all the people current user follows to the feed: O(N * m * log10)
            N = Total no. of users, m = Max no. of tweets
        - Return the set of tweets: O(10) ~ (1)
    
    follow(): O(1)
    
    unfollow(): O(1)
*/
class Twitter {
    // <follower: Set(followees) >
    unordered_map<int, unordered_set<int>> graph;
    // <userId, set(<tweet_time, tweet_id>)>
    unordered_map<int, set<pair<int, int>, greater<pair<int, int> > > > tweets;
    int FEED_SIZE = 10;
    // global counter for tweets, used as an associated time stamp
    int tweet_time = 0;
public:
    Twitter() {
    }
    
    // Adds the tweet to the feed
    void addToFeed(int tweetId, int tweet_time, 
                   set<pair<int, int>, greater<pair<int, int> > >& feed) {
        // add the tweet to user's feed
        // check if feed size has hit threshold, then delete most stale tweet
        feed.emplace(make_pair(tweet_time, tweetId));
        if(feed.size() > FEED_SIZE)
            feed.erase(--feed.end());    
    }
    
    void postTweet(int userId, int tweetId) {
        ++tweet_time;
        tweets[userId].emplace(make_pair(tweet_time, tweetId));
    }
    
    vector<int> getNewsFeed(int userId) {
        // <tweet_time, tweet_id>
        set<pair<int, int>, greater<pair<int, int> > > feed;
        
        // add the tweets of current user to the feed
        // Get FEED_SIZE no. of most recent tweets of current user
        auto tweet_iter = tweets[userId].begin();
        for(int n_tweets = 1; 
            tweet_iter != tweets[userId].end() && n_tweets <= 10; tweet_iter++, n_tweets++) 
            // add to user's feed
            addToFeed(tweet_iter->second, tweet_iter->first, feed);
        
        // Fetch recent tweets from all the people
        // the current user follows and add their tweets to feed
        for(auto followeeId: graph[userId]) {
            // current user follows this person
            if(graph[userId].count(followeeId)) {
                auto tweet_iter = tweets[followeeId].begin();

                // Get FEED_SIZE no. of most recent tweets from the followee
                for(int n_tweets = 1; tweet_iter != tweets[followeeId].end() && n_tweets <= 10; tweet_iter++, n_tweets++) 
                    // add to user's feed
                    addToFeed(tweet_iter->second, tweet_iter->first, feed);
                
            }
        }
        vector<int> user_feed;
        for(auto [tweet_time, tweetId]: feed)
            user_feed.emplace_back(tweetId);
        return user_feed;
    }
    
    void follow(int followerId, int followeeId) {
        graph[followerId].emplace(followeeId);    
    }
    
    void unfollow(int followerId, int followeeId) {
        graph[followerId].erase(followeeId);
    }
};

/*
    Push style Feed: Here the feed is created before a request is made.
                    Whenever a new tweet relevant to feed is created, the feed
                    is updated. This makes getFeed() cheaper and other operations costlier.
    
    - We use a global timestamp / order counter tweet_time, this is the timestamp 
    associated with each tweet.
    - We use a hash table to maintain the graph of people.
    - We use a hash table of <userId, set(<tweet_time, tweet_id>) >. The set is
    used to maintain the sorted order of tweets.
    - We use a hash table of <userId, set(<tweet_time, tweet_id>) >. The set is
    used to maintain the feed of user.
    
    TC:
    Twitter(): O(1)
    
    postTweet(): O(logm) + O(nlog10), m: max no. of tweets, n: no. of followers
        - Add the tweet to user's set of tweets: O(logm) 
        - Add to user's feed: O(log10)
        - Add to all the follower's feed: O(nlog10)
        
    getNewsFeed(): O(10)
        - Return the set of tweets: O(10) ~ (1)
    
    follow(followerId, followeeId): O(1) + O(mlog10)
        - Add the graph edge: O(1)
        - Add the tweets of followee to follower's feed: O(mlog10)
        
    unfollow(followerId, followeeId): O(1) + O(mlog10)
        - Remove the graph edge
        - Remove followee's tweets from follower's feed: O(mlog10)
*/
class Twitter {
    // <follower: Set(followees) >
    unordered_map<int, unordered_set<int>> graph;
    // <userId, set(<tweet_time, tweet_id>)>
    unordered_map<int, set<pair<int, int>, greater<pair<int, int> > > > tweets;
    // <userId, set(<tweet_time, tweet_id>)>
    unordered_map<int, set<pair<int, int>, greater<pair<int, int> > > > feed;
    
    int FEED_SIZE = 10;
    // global counter for tweets, used as an associated time stamp
    int tweet_time = 0;
public:
    Twitter() {
    }
    
    // Adds the tweet to the feed
    void addToFeed(int tweetId, int tweet_time, 
                   set<pair<int, int>, greater<pair<int, int> > >& feed) {
        feed.emplace(make_pair(tweet_time, tweetId));
        if(feed.size() > FEED_SIZE)
            feed.erase(--feed.end());   
    }
    
    void postTweet(int userId, int tweetId) {
        ++tweet_time;
        tweets[userId].emplace(make_pair(tweet_time, tweetId));
        
        // add the tweet to feed
        addToFeed(tweetId, tweet_time, feed[userId]);
        
        // add to all follower's feed
        for(auto follower: graph) {
            int followerId = follower.first;
            // current user follows this person
            if(graph[followerId].count(userId)) {
                // add to user's feed
                addToFeed(tweetId, tweet_time, feed[followerId]);
            }
        }
    }
    
    vector<int> getNewsFeed(int userId) {
        vector<int> user_feed;
        auto feed_iter = feed[userId].begin();
        
        for(int n_tweets = 1; feed_iter != feed[userId].end() && n_tweets <= FEED_SIZE; feed_iter++, n_tweets++) 
            user_feed.emplace_back(feed_iter->second);
        return user_feed;
    }
    
    void follow(int followerId, int followeeId) {
        graph[followerId].emplace(followeeId);  
        
        // add the tweets of the followee to follower
        auto tweet_iter = tweets[followeeId].begin();
        // Get FEED_SIZE no. of most recent tweets from the followee
        for(int n_tweets = 1; tweet_iter != tweets[followeeId].end() && n_tweets <= FEED_SIZE; tweet_iter++, n_tweets++) 
            // add to user's feed
            addToFeed(tweet_iter->second, tweet_iter->first, feed[followerId]);
    }
    
    void unfollow(int followerId, int followeeId) {
        graph[followerId].erase(followeeId);
        // remove the tweets of followee from follower's feed
        auto tweet_iter = tweets[followeeId].begin();
        for(; tweet_iter != tweets[followeeId].end(); tweet_iter++) 
            feed[followerId].erase(*tweet_iter);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */
