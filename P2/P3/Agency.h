#ifndef _AGENCY_H_
#define _AGENCY_H_

#include "Influencer.h"

class Agency {
    friend ostream& operator<<(ostream &os, const Agency &ag);
    private:
        string name;
        double money;
        vector<Influencer> influencers;
    public:
        Agency(string name, double initialMoney);
        Influencer *searchInfluencer(string infName);
        void addInfluencer(string infName, double commission);
        void addFollowers(string infName, string snName, int nFollowers);
        void newEvent(vector<string> infNames, int nsns, string snNames[], double evRats[]);
        void deleteInfluencer(string infName);
        double collectCommissions();
        const string getName();
        const double getMoney();
};


#endif