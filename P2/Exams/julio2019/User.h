#include "Tweet.cc"

#ifndef USER_H
#define USER_H

class User {
    friend ostream& operator<<(ostream &os, const User &us);
    private:
        string name;
        string email;
        vector<Tweet> tweets;
    public:
        User(string name, string email);
        unsigned int writeTweet(string text, const vector<string> &users);
        void addTweet(Tweet newTweet);
        string getName() const;
        Tweet getTweet(int pos) const;
        unsigned int getNumberOfTweets() const;
};

#endif