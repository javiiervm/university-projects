#include <iostream>
#include <cctype>   // Función isalnum
#include <vector>

using namespace std;

#ifndef TWEET_H
#define TWEET_H

enum Exception {exception_mention, exception_name, exception_email, exception_pos};

class Tweet {
    friend ostream& operator<<(ostream &os, const Tweet &tw);
    private:
        string text;
        unsigned int nextId = 1;
        unsigned int id;
    public:
        Tweet(string text, const vector<string> &users);
        string getText() const;
        unsigned int getId() const;
        vector<string> getMentions() const;
};

#endif