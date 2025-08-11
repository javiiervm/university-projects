#include "User.h"

User::User(string name, string email) {
    bool arroba = false, punto = false;
    for(unsigned int i = 0; i < name.size(); i++) {
        if(!isalnum(name[i])) {
            throw exception_name;
        }
    }
    for(unsigned int i = 0; i < email.size(); i++) {
        if(!(i > 0 && i < email.size() - 1)) {
            if(email[i] == '@' || email[i] == '.') {
                throw exception_email;
            }
        }
    }
    if(!arroba || !punto)
        throw exception_email;
    
    this->name = name;
    this->email = email;
}

unsigned int User::writeTweet(string text, const vector<string> &users) {
    try {
        tweets.push_back(Tweet(text, users));
    } catch(Exception e) {
        if(e == exception_mention) {
            cout << "ERROR MENCION" << endl;
            return 0;
        } /*else {
            Tweet::debug
        }*/
    }
    return tweets[tweets.size()-1].getId();
}

void User::addTweet(Tweet newTweet) {
    tweets.push_back(newTweet);
}

string User::getName() const {
    return name;
}

Tweet User::getTweet(int pos) const {
    if(pos >= tweets.size())
        throw exception_pos;
    return tweets[pos];
}

unsigned int User::getNumberOfTweets() const {
    return tweets.size();
}

ostream& operator<<(ostream &os, const User &us) {
    os << us.name << " (" << us.email << ")" << endl;
    for(unsigned int i = 0; i < us.getNumberOfTweets(); i++)  {
        os << us.tweets[i];
    }
    return os;
}
