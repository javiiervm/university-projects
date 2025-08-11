#ifndef _INFLUENCER_H_
#define _INFLUENCER_H_

#include "SNFollowers.h"

class Influencer {
    friend ostream& operator<<(ostream &os, const Influencer &inf);
    private:
        string name;
        double commission;
        vector<SNFollowers> followers;
    public:
        Influencer(string name);
        void setCommission(double commission);
        void addFollowers(string snName, int nFollowers);
        void addEvent(int nsns, string sn[], double rat[]);
        double collectCommission();
        const string getName();
        const vector<SNFollowers>& getFollowers();
        double getCommission() const;
};


#endif