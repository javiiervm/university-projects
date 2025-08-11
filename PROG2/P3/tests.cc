
#include <stdexcept>
#include <iostream>
using namespace std;

#include "SNData.h"
#include "Util.h"
#include "Agency.h"
int main()
{
   SNData::newSocialNetwork("TokTik",0.8,0.1);
   SNData::newSocialNetwork("Infagram",0.6,0.05);
   SNData::newSocialNetwork("YZ",0.5,0.2);
   SNData::newSocialNetwork("JungleBook",0.1,0.1);

   cout << "---------- SNData -----------" << endl;

   // Check name is not repeated
   try {
      SNData::newSocialNetwork("TokTik", 0.8, 0.1);
      cout << "You have not catch duplicated name" << endl;
   } catch (const invalid_argument &name) {}
   
   // Check rating
   try {
      SNData::newSocialNetwork("BeReal", 12, 0.1);
      cout << "You have not catch wrong AvgR" << endl;
   } catch (const invalid_argument &err) {}

   try {
      SNData::newSocialNetwork("BeReal", 0, 0.1);
      cout << "You have not catch wrong AvgR" << endl;
   } catch (const invalid_argument &err) {}

   try {
      SNData::newSocialNetwork("BeReal", 1, 0.1);
      cout << "You have not catch wrong AvgR" << endl;
   } catch (const invalid_argument &err) {}

   // Check monetizing
   try {
      SNData::newSocialNetwork("BeReal", 0.8, 0);
      cout << "You have not catch wrong AvgM" << endl;
   } catch (const invalid_argument &err) {}

   try {
      SNData::newSocialNetwork("BeReal", 0.8, 1);
      cout << "You have not catch wrong AvgM" << endl;
   } catch (const invalid_argument &err) {}

   // Check getAvgMonetizing
   if (SNData::getAvgMonetizing("TokTik") != 0.1)
      cout << "This should not appear: getAvgMonetizing does not work well" << endl;
   if (SNData::getAvgMonetizing("BeReal") != 0.0)
      cout << "This should not appear: getAvgMonetizing does not work well" << endl;

   // Check getAvgRating
   if (SNData::getAvgRating("TokTik") != 0.8)
      cout << "This should not appear: getAvgMonetizing does not work well" << endl;
   if (SNData::getAvgRating("BeReal") != 0.0)
      cout << "This should not appear: getAvgMonetizing does not work well" << endl;

   // Check checkSN
   if (!SNData::checkSN("TokTik"))
      cout << "This should not appear: checkSN does not work well" << endl;
   if (SNData::checkSN("BeReal"))
      cout << "This should not appear: checkSN does not work well" << endl;

   cout << "If no messages have been printed, congrats!, SNData passes the tests" << endl;

   // SNFollowers
   cout << "---------- SNFollowers -----------" << endl;

   // constructor for SNFollowers
   try {
      SNFollowers a("BeReal", 14);
      cout << "The constructor of SNFollowers does not work well: name part" << endl;
   } catch (Exception err) {}

   try {
      SNFollowers a("TokTik", -12);
      cout << "The constructor of SNFollwers does not work well: initial followers part" << endl;
   } catch (const invalid_argument &err) {}

   SNFollowers tokTik("TokTik", 10);
   // addFollowers
   tokTik.addFollowers(-12);
   if (tokTik.getNumFollowers() != 0)
      cout << "This should not appear: addFollowers of SNFollowers does not work well" << endl;
   tokTik.addFollowers(1000);
   if (tokTik.getNumFollowers() != 1000)
      cout << "This should not appear: addFollowers of SNFollowers does not work well" << endl;

   // addEvent
   try {
      tokTik.addEvent(-0.3);
      cout << "addEvent does not work well: negatives are allowed" << endl;
   } catch (const invalid_argument &err) {}

   tokTik.addEvent(0.65);
   if (tokTik.getNumFollowers() != 1812)
      cout << "This should not appear: addEvent does not work well, update number of followers, ratio > 0.8" << endl;
   if (tokTik.getMoney() != 812 * SNData::getAvgMonetizing(tokTik.getName()))
      cout << "This should not appear: addEvent does not work well, update money, ratio > 0.8" << endl;
   tokTik.addFollowers(-812);
   tokTik.addEvent(0.56);
   if (tokTik.getNumFollowers() != 801)
      cout << "This should not appear: addEvent does not work well, update number of followers, ratio <= 0.8" << endl;
   if (tokTik.getMoney() != 812 * SNData::getAvgMonetizing(tokTik.getName())) // no money is earned
      cout << "This should not appear: addEvent does not work well, update money, ratio <= 0.8" << endl;

   // collectCommission
   try {
      tokTik.collectCommission(0);
      cout << "collectCommission does not work well: parameter < 0" << endl;
   } catch (const invalid_argument &err) {}

   try {
      tokTik.collectCommission(1);
      cout << "collectCommission does not work well: parameter < 0" << endl;
   } catch (const invalid_argument &err) {}

   double moneyExpected = 0.1 * 812 * SNData::getAvgMonetizing(tokTik.getName());
   if (tokTik.collectCommission(0.1) != moneyExpected)
      cout << "This should not appear: collectCommission does not work well" << endl;
   if (tokTik.getMoney() != 0)
      cout << "This should not appear: collectCommission does not put the money to 0" << endl;

   cout << "If no messages have been printed, congrats!, SNFollowers passes the tests" << endl;   

   // Influencer
   cout << "---------- Influencer -----------" << endl;

   Influencer illojuanMaricon("Illojuan");
   // setCommission
   try {
      illojuanMaricon.setCommission(-1);
      cout << "setCommission does not work well: commission cannot be negative" << endl;      
   } catch (Exception err) {}

   try {
      illojuanMaricon.setCommission(0.9);
      cout << "setCommission does not work well: commission cannot be greater than 0.8" << endl;      
   } catch (Exception err) {}
   

   // addFollowers
   illojuanMaricon.addFollowers("BeReal", 100);
   cout << illojuanMaricon;
   cout << "If an error was raised and no Social Networks are printed, the addFollowers method works fine" << endl;
   illojuanMaricon.addFollowers(tokTik.getName(), 100);
   cout << illojuanMaricon;
   cout << "If TokTik is printed with 100 followers, the addFollowers method works fine" << endl;
   illojuanMaricon.addFollowers(tokTik.getName(), 900);
   cout << illojuanMaricon;
   cout << "If TokTik is printed with 1000 followers, the addFollowers method works fine" << endl;

   // addEvent
   string sn[] = {"TokTik", "BeReal"};
   double rat[] = {0.65, 0.4};
   illojuanMaricon.addEvent(2, sn, rat);
   cout << illojuanMaricon;
   cout << "If only appears TokTik with 1812 followers, addEvent works right" << endl;
   
   // collectCommission
   if (illojuanMaricon.collectCommission() != moneyExpected)
      cout << "This should not appear: collectCommission does not work well" << endl;

   // Agency
   cout << "---------- Agency -----------" << endl;

   Agency puteros("Puteros Masones", 1000);

   // addInfluencer
   puteros.addInfluencer("Illojuan", 0.9);
   cout << puteros;
   cout << "If an error was printed and \"Puteros Masones\" has no influencers, your program works fine" << endl;
   puteros.addInfluencer("Ibai", 0.1);
   cout << puteros;
   cout << "If the agency has an influencer, your program works fine" << endl;
   puteros.addInfluencer("Ibai", 0.1);
   cout << puteros;
   cout << "If an error was printed and \"Puteros Masones\" has 1 influencer, your program works fine" << endl;

   // searchInfluencer
   try {
      puteros.searchInfluencer("Illojuan");
      cout << "searchInfluencer does not work well: found an influencer that should not be in the Agency" << endl;
   } catch (Exception err) {
      // cout << "Great catch: an influencer was not found correctly" << endl;
   }

   try {
      puteros.searchInfluencer("Ibai");
   } catch (Exception err) {}

   // addFollowers
   puteros.addFollowers("Illojuan", "TokTik", 100);
   cout << puteros;
   cout << "If an ERR_NOT_FOUND was printed and the influencer does not have a social network, your program works fine" << endl;

   puteros.addFollowers("Ibai", "BeReal", 1000);
   cout << puteros;
   cout << "If an ERR_UNKNOWN_SN was printed and the influencer does not have a social network, your program works fine" << endl;

   puteros.addFollowers("Ibai", "TokTik", 1000);
   cout << puteros;
   cout << "If the influencer has a social network with 1000 followers, your program works fine" << endl;

   // newEvent
   vector<string> infNames = {"Illojuan", "Ibai"};
   puteros.newEvent(infNames, 2, sn, rat);
   cout << puteros;
   cout << "If only appears Ibai, who has the social network TokTik with 1812 followers, newEvent works right" << endl;

   // collectCommissions
   if (puteros.collectCommissions() != moneyExpected)
      cout << "This should not appear: collectCommissions does not work fine, the return value is not correct" << endl;
   if (puteros.getMoney() != moneyExpected + 1000)
      cout << "This should not appear: collectCommissions does not work fine, the agency's money has not increased" << endl;

   // deleteInfluencer
   puteros.searchInfluencer("Ibai")->addFollowers("TokTik", -812);
   puteros.newEvent(infNames, 2, sn, rat);
   puteros.deleteInfluencer("Ibai");
   if (puteros.getMoney() != 1016.24)
      cout << "deleteInfluencer does not work well: the money of the agency does not match the expected" << endl;
   cout << puteros;
   cout << "Check that there is no influencers" << endl;

   return 0;
}
