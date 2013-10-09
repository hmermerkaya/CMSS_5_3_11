#include "PhysicsTools/NtupleUtils/interface/treeReader.h"


treeReader::treeReader (TTree * tree, bool verbosity) :
m_tree (tree),
m_verbosity (verbosity)
{
 TObjArray * br_list = m_tree->GetListOfBranches () ;
 TIter br_it (br_list) ;
 TBranch * iBranch ; 
 
 //PG loop over branches
 while ((iBranch = (TBranch *) br_it.Next ())) 
 {
  TBranchElement* bre = (TBranchElement*) iBranch ;
  std::string bname = bre->GetClassName () ;      
  if (bname.find ("Event") != std::string::npos) continue ;
  
  if (bname.find ("vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >") != std::string::npos)
  {
   if (m_verbosity)
     std::cout << "4V | setting " << bre->GetName () << " for type : " << bre->GetClassName () << "\n" ;
   std::vector<ROOT::Math::XYZTVector> * dummy = new std::vector<ROOT::Math::XYZTVector> ;
   m_4Vvectors[bre->GetName ()] = dummy ;
   m_tree->SetBranchAddress (bre->GetName (), &m_4Vvectors[bre->GetName ()]) ;
  }
  
  if (bname.find ("vector<ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> >") != std::string::npos)
  {
   if (m_verbosity)
     std::cout << "3V | setting " << bre->GetName () << " for type : " << bre->GetClassName () << "\n" ;
   std::vector<ROOT::Math::XYZVector> * dummy = new std::vector<ROOT::Math::XYZVector> ;
   m_3Vvectors[bre->GetName ()] = dummy ;
   m_tree->SetBranchAddress (bre->GetName (), &m_3Vvectors[bre->GetName ()]) ;
  }
  
  if (bname.find ("vector<int>") != std::string::npos)
  {
   if (m_verbosity)
     std::cout << "IV | setting " << bre->GetName () << " for type : " << bre->GetClassName () << "\n" ;
   std::vector<int> * dummy = new std::vector<int> ;
   m_Ivectors[bre->GetName ()] = dummy ;
   m_tree->SetBranchAddress (bre->GetName (), &m_Ivectors[bre->GetName ()]) ;
  }

  if (bname.find ("vector<string>") != std::string::npos)
  {
   if (m_verbosity)
     std::cout << "SV | setting " << bre->GetName () << " for type : " << bre->GetClassName () << "\n" ;
   std::vector<std::string> * dummy = new std::vector<std::string> ;
   m_Svectors[bre->GetName ()] = dummy ;
   m_tree->SetBranchAddress (bre->GetName (), &m_Svectors[bre->GetName ()]) ;
  }
  
  if (bname.find ("vector<float>") != std::string::npos)
  {
   if (m_verbosity)
     std::cout << "FV | setting " << bre->GetName () << " for type : " << bre->GetClassName () << "\n" ;
   std::vector<float> * dummy = new std::vector<float> ;
   m_Fvectors[bre->GetName ()] = dummy ;
   m_tree->SetBranchAddress (bre->GetName (), &m_Fvectors[bre->GetName ()]) ;
  }
  
  if (bname.find ("vector<double>") != std::string::npos)
  {
   if (m_verbosity)
     std::cout << "DV | setting " << bre->GetName () << " for type : " << bre->GetClassName () << "\n" ;
   std::vector<double> * dummy = new std::vector<double> ;
   m_Dvectors[bre->GetName ()] = dummy ;
   m_tree->SetBranchAddress (bre->GetName (), &m_Dvectors[bre->GetName ()]) ;
  }
  
 } //PG loop over branches
 
 std::cout << " --> " << (m_3Vvectors.size () + m_4Vvectors.size () + m_Fvectors.size () + m_Dvectors.size () + m_Ivectors.size ()) << " branches read\n" ;
 
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


treeReader::~treeReader () 
{
 for (std::map <std::string, std::vector<double> * >::const_iterator iMap = m_Dvectors.begin () ; iMap != m_Dvectors.end () ; ++iMap)
 {
  delete iMap->second ;
 } 
 
 for (std::map <std::string, std::vector<float> * >::const_iterator iMap = m_Fvectors.begin () ; iMap != m_Fvectors.end () ; ++iMap)
 {
  delete iMap->second ;
 } 
 
 for (std::map <std::string, std::vector<int> * >::const_iterator iMap = m_Ivectors.begin () ; iMap != m_Ivectors.end () ; ++iMap)
 {
  delete iMap->second ;
 } 

 for (std::map <std::string, std::vector<std::string> * >::const_iterator iMap = m_Svectors.begin () ; iMap != m_Svectors.end () ; ++iMap)
 {
  delete iMap->second ;
 } 
 
 for (std::map <std::string, std::vector<ROOT::Math::XYZTVector> * >::const_iterator iMap = m_4Vvectors.begin () ; iMap != m_4Vvectors.end () ;  ++iMap)
 {
  delete iMap->second ;
 } 
 
 for (std::map <std::string, std::vector<ROOT::Math::XYZVector> * >::const_iterator iMap = m_3Vvectors.begin () ; iMap != m_3Vvectors.end (); ++iMap)
 {
  delete iMap->second ;
 } 
} 




std::vector<ROOT::Math::XYZVector>* treeReader::Get3V(const std::string &name){
 std::map<std::string,std::vector<ROOT::Math::XYZVector> * >::const_iterator    it_3V  = m_3Vvectors.find(name);
 if (it_3V  != m_3Vvectors.end()  ) return m_3Vvectors[name];
 else return new std::vector<ROOT::Math::XYZVector>;
}

std::vector<ROOT::Math::XYZPoint>* treeReader::Get3PV(const std::string &name){
 std::map<std::string,std::vector<ROOT::Math::XYZPoint> * >::const_iterator    it_3PV  = m_3PVvectors.find(name);
 if (it_3PV  != m_3PVvectors.end()  ) return m_3PVvectors[name];
 else return new std::vector<ROOT::Math::XYZPoint>;
}

std::vector<ROOT::Math::XYZTVector>* treeReader::Get4V(const std::string &name){
 std::map<std::string,std::vector<ROOT::Math::XYZTVector> * >::const_iterator   it_4V  = m_4Vvectors.find(name);
 if (it_4V  != m_4Vvectors.end()  ) return m_4Vvectors[name];
 else return new std::vector<ROOT::Math::XYZTVector>;
}

std::vector<double>* treeReader::GetDouble(const std::string &name){
 std::map<std::string,std::vector<double> * >::const_iterator                 it_D  = m_Dvectors.find(name);
 if (it_D  != m_Dvectors.end()  ) return m_Dvectors[name];
 else return new std::vector<double>;
}

std::vector<float>* treeReader::GetFloat(const std::string &name){
 std::map<std::string,std::vector<float> * >::const_iterator           it_F  = m_Fvectors.find(name);
 if (it_F  != m_Fvectors.end()  ) return m_Fvectors[name];
 else return new std::vector<float>;
}

std::vector<int>* treeReader::GetInt(const std::string &name){
 std::map<std::string,std::vector<int> * >::const_iterator             it_I  = m_Ivectors.find(name);
 if (it_I  != m_Ivectors.end()  ) return m_Ivectors[name];
 else return new std::vector<int>;
}

std::vector<std::string>* treeReader::GetString(const std::string &name){
 std::map<std::string,std::vector<std::string> * >::const_iterator             it_S  = m_Svectors.find(name);
 if (it_S  != m_Svectors.end()  ) return m_Svectors[name];
 else return new std::vector<std::string>;
}
