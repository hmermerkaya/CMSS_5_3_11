#ifndef ntpleUtils_h
#define ntpleUtils_h

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include <iomanip>

#include "TFile.h"
#include "TH1F.h"
#include "TChain.h"
#include "TVector3.h"
#include "Math/Vector4D.h"
#include "ConfigParser.h"






bool maggiore(double i, double j);






/** get the number of events from a list of files */
std::map<int, int> GetTotalEvents(const std::string& histoName, const std::string& inputFileList);
std::map<int, int> GetTotalEvents(const std::string& histoName, const std::vector<std::string> & inputFileList);

/** fill a chain from a list of files */
bool FillChain(TChain& chain, const std::string& inputFileList);
bool FillChain(TChain& chain, const std::vector<std::string> & inputFileList);

/** get the parameters from a congiguration file */
int parseConfigFile (const TString& config) ;






/** compute delta phi */
double deltaPhi (const double& phi1, const double& phi2);

/** compute delta eta */
double deltaEta (const double& eta1, const double& eta2);

/** compute delta R */
double deltaR (const double& eta1, const double& phi1,
               const double& eta2, const double& phi2);





/** define the map of all possible matching */
template <class T1, class T2>
std::map<float, std::pair<int, int> > MatchingDRMap(const std::vector<T1>& collection1,
                                                    const std::vector<T2>& collection2)
{
  // define map of all possible DRs
  typedef std::map<float, std::pair<int, int> > DRMap;
  DRMap myDRMap;
  myDRMap.clear();  
  // compute all DRs 
  for(unsigned int it1 = 0; it1 <  collection1.size(); ++it1)
  {
    for(unsigned int it2 = 0; it2 < collection2.size(); ++it2)
    {
      float DR = deltaR((collection1.at(it1)).Eta(), (collection1.at(it1)).Phi(),
                        (collection2.at(it2)).Eta(), (collection2.at(it2)).Phi());
      std::pair<int, int> dummy(it1, it2);
      myDRMap[DR] = dummy;
    }
  }
  return myDRMap;
}

/** define the map of all possible matching */
template <class T1, class T2>
int GetMatching(const std::vector<T1>& collection1, //---- RECO
                const std::vector<T2>& collection2, //---- MC
                const float& DRMax,
                float ptRatioMin,
                float ptRatioMax,
                std::vector<int>* matchIt1 = 0) //---- index from RECO that matches with MC

{
  // get the DR map between two collection of particles
  typedef std::map<float, std::pair<int, int> > DRMap;
  DRMap myDRMap = MatchingDRMap(collection1, collection2);
  
    // define boolean flags to avoid double usage of the same particle
  std::vector<bool> isUsed1;
  for(unsigned int i = 0; i < collection1.size(); ++ i)
    isUsed1.push_back(false);
  
  std::vector<bool> isUsed2;
  for(unsigned int i = 0; i < collection2.size(); ++ i)
    isUsed2.push_back(false);
  
  
  // intialize the vector which will store the result of the matching
  if(matchIt1 != 0)
  {
    (*matchIt1).clear();
    for(unsigned int i = 0; i < collection2.size(); ++i)
      (*matchIt1).push_back(-1);
  }
  
  // loop over the DRmap to get the smallest DR matchings
  unsigned int nMatching = 0;
  
  for(DRMap::const_iterator mapIt = myDRMap.begin();
      mapIt != myDRMap.end(); ++mapIt)
  {
    int it1 = (mapIt -> second).first;
    int it2 = (mapIt -> second).second;
    
    float DR = mapIt -> first;
    
    TVector3 momentum1(collection1.at(it1).Px(),
                       collection1.at(it1).Py(),
                       collection1.at(it1).Pz());
    TVector3 momentum2(collection2.at(it2).Px(),
                       collection2.at(it2).Py(),
                       collection2.at(it2).Pz());
    
    if( 1. * collection1.at(it1).Pt() / (collection2.at(it2)).Pt() < ptRatioMin) 
      continue;
    if( 1. * collection1.at(it1).Pt() / (collection2.at(it2)).Pt() > ptRatioMax) 
      continue;
    
    if( (DR <= DRMax) && (isUsed1.at(it1) == false) && (isUsed2.at(it2) == false) )
    {
      isUsed1.at(it1) = true; 
      isUsed2.at(it2) = true; 
      ++nMatching;
      
      if(matchIt1 != 0)
        (*matchIt1).at(it2) = it1;
    }
    
    if( (nMatching == collection2.size()) || (DR > DRMax) )
      break;    
  }
  
  return nMatching;
}






/** select jet pairs */
double SelectJets(std::vector<int>& it, std::vector<ROOT::Math::XYZTVector>& jets,
                  const std::string& method,
                  const double& etMin,
                  const std::vector<int>* blacklist = 0);

/** select jet pairs with Deta cut*/
double SelectJets(std::vector<int>& it, std::vector<ROOT::Math::XYZTVector>& jets,
                  const std::string& method,
                  const double& etMin,
                  const double& DetaMin,
                  const double& DetaMax,
                  const std::vector<int>* blacklist = 0);

/** select leptons */
int SelectLepton(std::vector<ROOT::Math::XYZTVector>& leptons,
                 const std::string& method,
                 const double& ptMin,
                 const std::vector<int>* blacklist = 0);

/** select tag jets */
double SelectTagJets(std::vector<int>& it, std::vector<ROOT::Math::XYZTVector>& jets,
                     const double& etMin,
                     const double& DetaMIN,
                     const double& mjjMIN,                     
                     const std::vector<int>* blacklist = 0);

/** select W jets */
double SelectWJets(std::vector<int>& it, std::vector<ROOT::Math::XYZTVector>& jets,
                   const double& etMin,
                   const double& DetaMAX,
                   const double& mjjMAX,                     
                   const std::vector<int>* blacklist = 0);


/** build combinations of n jets */
int Build4JetCombinations(std::vector<std::vector<int> >& comb, const int& nJets);

/** print combinations of n jets */
void Print4JetCombination(const std::vector<int>& combination);



/** print 4-vector */
void Print4V(const ROOT::Math::XYZTVector& p);

#endif
