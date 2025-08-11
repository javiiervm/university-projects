#ifndef _SNDATA_H_
#define _SNDATA_H_

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "Util.h"

struct SocialNetworkData {
    string name;
    double averageRating;
    double averageMonetizing;
};

class SNData {
    private:
        static vector<SocialNetworkData> sns;
    public:
        static void newSocialNetwork(string name, double avgR, double avgM);
        static bool checkSN(string name);
        static double getAvgRating(string name);
        static double getAvgMonetizing(string name);
};

#endif