#ifndef treeReader_h
#define treeReader_h

#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TH2.h"
#include "Math/Vector4D.h"
#include "Math/Vector3D.h"
#include "TBranch.h"
#include "TBranchElement.h"

#include <map>
#include <vector>
#include <string>

class treeReader
{
  public:
  
    treeReader (TTree *) ;
    ~treeReader () ;
  
    void GetEntry (int iEvent) {m_tree->GetEntry (iEvent) ; } ;
    
//     template <class T> std::vector<T>* Get(const std::string &name);
    std::vector<double>*                 GetDouble(const std::string &name);
    std::vector<float>*                  GetFloat (const std::string &name);
    std::vector<int>*                    GetInt   (const std::string &name);
    std::vector<ROOT::Math::XYZVector>*  Get3V    (const std::string &name);
    std::vector<ROOT::Math::XYZTVector>* Get4V    (const std::string &name);

    TH2F * PrepareTest () ; //PG NB the TH2F has to be deleted
    void FillTest (TH2F * testMe) ;
        
  private:

    std::map <std::string, std::vector<double> * >                 m_Dvectors ;
    std::map <std::string, std::vector<float> * >                  m_Fvectors ;
    std::map <std::string, std::vector<int> * >                    m_Ivectors ;
    std::map <std::string, std::vector<ROOT::Math::XYZVector> * >  m_3Vvectors ;
    std::map <std::string, std::vector<ROOT::Math::XYZTVector> * > m_4Vvectors ;
    
    TTree * m_tree ;

} ;

// template <class T> std::vector<T>* treeReader::Get(const std::string &name){
//  if (typeid(T)==typeid(double)) {
//   std::map<std::string,std::vector<double> * >::const_iterator          it_D  = m_Dvectors.find(name);
//   if (it_D  != m_Dvectors.end()  ) return m_Dvectors[name];
//  }
//  if (typeid(T)==typeid(float)) {
//   std::map<std::string,std::vector<float> * >::const_iterator           it_F  = m_Fvectors.find(name);
//   if (it_F  != m_Fvectors.end()  ) return m_Fvectors[name];
//  }
//  if (typeid(T)==typeid(int)) {
//   std::map<std::string,std::vector<int> * >::const_iterator             it_I  = m_Ivectors.find(name);
//   if (it_I  != m_Ivectors.end()  ) return m_Ivectors[name];
//  }
//  if (typeid(T)==typeid(ROOT::Math::XYZVector)) {
//   std::map<std::string,std::vector<ROOT::Math::XYZVector> * >::const_iterator    it_3V  = m_3Vvectors.find(name);
//   if (it_3V  != m_3Vvectors.end()  ) return m_3Vvectors[name];
//  }
//  if (typeid(T)==typeid(ROOT::Math::XYZTVector)) {
//   std::map<std::string,std::vector<ROOT::Math::XYZTVector> * >::const_iterator   it_4V  = m_4Vvectors.find(name);
//   if (it_4V  != m_4Vvectors.end()  ) return m_4Vvectors[name];
//  }
// }










#endif

