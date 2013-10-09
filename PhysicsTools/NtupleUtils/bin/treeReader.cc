#include "treeReader.h"


treeReader::treeReader (TTree * tree) :
m_tree (tree)
{
  std::cout << ">>>>> treeReader::Read " << m_tree -> GetEntries() << " entries" << std::endl; 

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
   std::cout << "4V | setting " << bre->GetName () << " for type : " << bre->GetClassName () << "\n" ;
   std::vector<ROOT::Math::XYZTVector> * dummy = new std::vector<ROOT::Math::XYZTVector> ;
   m_4Vvectors[bre->GetName ()] = dummy ;
   m_tree->SetBranchAddress (bre->GetName (), &m_4Vvectors[bre->GetName ()]) ;
  }
  
  if (bname.find ("vector<ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> >") != std::string::npos)
  {
   std::cout << "3V | setting " << bre->GetName () << " for type : " << bre->GetClassName () << "\n" ;
   std::vector<ROOT::Math::XYZVector> * dummy = new std::vector<ROOT::Math::XYZVector> ;
   m_3Vvectors[bre->GetName ()] = dummy ;
   m_tree->SetBranchAddress (bre->GetName (), &m_3Vvectors[bre->GetName ()]) ;
  }
  
  if (bname.find ("vector<int>") != std::string::npos)
  {
   std::cout << "IV | setting " << bre->GetName () << " for type : " << bre->GetClassName () << "\n" ;
   std::vector<int> * dummy = new std::vector<int> ;
   m_Ivectors[bre->GetName ()] = dummy ;
   m_tree->SetBranchAddress (bre->GetName (), &m_Ivectors[bre->GetName ()]) ;
  }
  
  if (bname.find ("vector<float>") != std::string::npos)
  {
   std::cout << "FV | setting " << bre->GetName () << " for type : " << bre->GetClassName () << "\n" ;
   std::vector<float> * dummy = new std::vector<float> ;
   m_Fvectors[bre->GetName ()] = dummy ;
   m_tree->SetBranchAddress (bre->GetName (), &m_Fvectors[bre->GetName ()]) ;
  }
  
  if (bname.find ("vector<double>") != std::string::npos)
  {
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
 
 for (std::map <std::string, std::vector<ROOT::Math::XYZTVector> * >::const_iterator iMap = m_4Vvectors.begin () ; iMap != m_4Vvectors.end () ;  ++iMap)
 {
  delete iMap->second ;
 } 
 
 for (std::map <std::string, std::vector<ROOT::Math::XYZVector> * >::const_iterator iMap = m_3Vvectors.begin () ; iMap != m_3Vvectors.end (); ++iMap)
 {
  delete iMap->second ;
 } 
} 


std::vector<double>* treeReader::GetDouble(const std::string &name){
 std::map<std::string,std::vector<double> * >::const_iterator                 it_D  = m_Dvectors.find(name);
 if (it_D  != m_Dvectors.end()  ) return m_Dvectors[name];
 else return NULL;
}
std::vector<float>* treeReader::GetFloat(const std::string &name){
 std::map<std::string,std::vector<float> * >::const_iterator           it_F  = m_Fvectors.find(name);
 if (it_F  != m_Fvectors.end()  ) return m_Fvectors[name];
 else return NULL;
}
std::vector<int>* treeReader::GetInt(const std::string &name){
 std::map<std::string,std::vector<int> * >::const_iterator             it_I  = m_Ivectors.find(name);
 if (it_I  != m_Ivectors.end()  ) return m_Ivectors[name];
 else return NULL;
}
std::vector<ROOT::Math::XYZVector>* treeReader::Get3V(const std::string &name){
 std::map<std::string,std::vector<ROOT::Math::XYZVector> * >::const_iterator    it_3V  = m_3Vvectors.find(name);
 if (it_3V  != m_3Vvectors.end()  ) return m_3Vvectors[name];
 else return NULL;
}
std::vector<ROOT::Math::XYZTVector>* treeReader::Get4V(const std::string &name){
 std::map<std::string,std::vector<ROOT::Math::XYZTVector> * >::const_iterator   it_4V  = m_4Vvectors.find(name);
 if (it_4V  != m_4Vvectors.end()  ) return m_4Vvectors[name];
 else return NULL;
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


TH2F * treeReader::PrepareTest ()  
{
  int dim = m_Dvectors.size () + m_Fvectors.size () +
            m_Ivectors.size () + m_3Vvectors.size () + m_4Vvectors.size () ;
            
  TH2F * testMe = new TH2F ("testMe", "vectors size", dim, 0, dim, 10, 0, 10) ;

  return testMe ;                             
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


void 
treeReader::FillTest (TH2F * testMe) 
{
    int pos = 0 ;
    for (std::map <std::string, std::vector<double> * >::const_iterator                 iMap = m_Dvectors.begin () ;
         iMap != m_Dvectors.end () ;
         ++iMap)
      {
        testMe->Fill (pos++, iMap->second->size ()) ;
      }
    for (std::map <std::string, std::vector<float> * >::const_iterator                  iMap = m_Fvectors.begin () ;
         iMap != m_Fvectors.end () ;
         ++iMap)
      {
        testMe->Fill (pos++, iMap->second->size ()) ;
      }
    for (std::map <std::string, std::vector<int> * >::const_iterator                    iMap = m_Ivectors.begin () ;
         iMap != m_Ivectors.end () ;
         ++iMap)
      {
        testMe->Fill (pos++, iMap->second->size ()) ;
      }
    for (std::map <std::string, std::vector<ROOT::Math::XYZVector> * >::const_iterator  iMap = m_3Vvectors.begin () ;
         iMap != m_3Vvectors.end () ;
         ++iMap)
      {
        testMe->Fill (pos++, iMap->second->size ()) ;
      }
    for (std::map <std::string, std::vector<ROOT::Math::XYZTVector> * >::const_iterator iMap = m_4Vvectors.begin () ;
         iMap != m_4Vvectors.end () ;
         ++iMap)
      {
        testMe->Fill (pos++, iMap->second->size ()) ;
      }  
}

