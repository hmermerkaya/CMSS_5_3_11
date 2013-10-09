#ifndef NtupleFactory_h
#define NtupleFactory_h

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "TString.h"
#include "TClonesArray.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TFile.h"
#include "TMatrix.h"
//#include "TParameter.h"
#include "Math/PtEtaPhiE4D.h"
#include "Math/PtEtaPhiM4D.h"
#include "Math/LorentzVector.h"
#include "Math/Vector3D.h"
#include "Math/PositionVector3D.h"
#include "Math/Vector3Dfwd.h"

class NtupleFactory{
  
 protected:
  
 public:
  NtupleFactory(TString namefile);
  NtupleFactory(TTree* outTree_input);
  ~NtupleFactory();
      
  void Add4V(const TString &name);
  void Fill4V(const TString &name,const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > &vect);
  
  void Add4TV(const TString &name);
  void Fill4TV(const TString &name,const TLorentzVector &vect);
 
  void Add3V(const TString &name);
  void Fill3V(const TString &name,const ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> &vect);

  void Add3PV(const TString &name);
  void Fill3PV(const TString &name,const ROOT::Math::PositionVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> &vect);
      
  void Add3TV(const TString &name);
  void Fill3TV(const TString &name,const TVector3 &vect);
      
  void AddFloat(const TString &name);
  void FillFloat(const TString &name,const float &vect);

  void AddDouble(const TString &name);
  void FillDouble(const TString &name,const double &vect);

  void AddInt(const TString &name);
  void FillInt(const TString &name,const int &vect);
  
  void AddLongLongInt(const TString &name);
  void FillLongLongInt(const TString &name,const int &vect);
  
  void AddString(const TString &name);
  void FillString(const TString &name,const std::string& vect);

  void AddTMatrix(const TString &name);
  void FillTMatrix(const TString &name, const TMatrix &vect);
  
  
  void FillNtuple();

  void ClearNtuple();
    
  void WriteNtuple(); 
  
  void DumpBranches();
  
 private:
  TLorentzVector myvector ;
  TMatrix mymatrix;
  std::map <TString,std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >* > ArrayContent_StdXYZT_ ;
  std::map <TString,TClonesArray*> ArrayContent_4TV_ ;
  std::map <TString,int> ArrayContent_4TV_num_ ;
  std::map <TString,std::vector<ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> >* > ArrayContent_StdXYZ_ ;
  std::map <TString,std::vector<ROOT::Math::PositionVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> >* > ArrayContent_StdXYZ2_ ;
  std::map <TString,TClonesArray*> ArrayContent_3TV_ ;
  std::map <TString,int> ArrayContent_3TV_num_ ;
  std::map <TString,std::vector<float>* > ArrayContentFloat_ ;
  std::map <TString,std::vector<double>* > ArrayContentDouble_ ;
  std::map <TString,std::vector<int>* > ArrayContentInt_ ;
  std::map <TString,std::vector<Long64_t>* > ArrayContentLongLongInt_ ;
  std::map <TString,std::vector<std::string>* > ArrayContentString_ ;
  std::map <TString,TClonesArray*> ArrayContent_TMatrix_ ;
  std::map <TString,int> ArrayContent_TMatrix_num_;

  TTree* outTree_;
  bool internalTree_;
  
  TFile* outFile_;
  TString fileName_ ;
  
};



#endif
