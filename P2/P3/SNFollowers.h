#ifndef _SNFOLLOWERS_H_
#define _SNFOLLOWERS_H_

#include "SNData.h"

class SNFollowers {
    friend ostream& operator<<(ostream &os, const SNFollowers &snf);
    private:
        string name;
        int numFollowers;
        double money;
    public:
        SNFollowers(string name, int initialFollowers);
        void addFollowers(int nFollowers);
        void addEvent(double rating);
        double collectCommission(double commission);
        const string getName();
        const int getNumFollowers();
        const double getMoney();
};

#endif