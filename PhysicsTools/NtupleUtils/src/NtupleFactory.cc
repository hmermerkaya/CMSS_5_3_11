#include "PhysicsTools/NtupleUtils/interface/NtupleFactory.h"


///--- Constructor ---
NtupleFactory::NtupleFactory(TString fileName){
//---- create output tree ----
internalTree_ = true;
fileName_ = fileName;
outFile_ = new TFile(fileName_,"RECREATE");
outTree_ = new TTree("SimpleTree","SimpleTree");
}

NtupleFactory::NtupleFactory(TTree* outTree_input){
//---- create output tree ----
 internalTree_ = false;
 outTree_ = outTree_input;
}

///--- Destructor ---
NtupleFactory::~NtupleFactory(){
 //---- destroy everything ----
 if (internalTree_){
  delete outTree_;
  delete outFile_;
  }
  
  for (std::map<TString,std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >* >::iterator it=ArrayContent_StdXYZT_.begin() ; it != ArrayContent_StdXYZT_.end(); it++ ){
   delete ((*it).second);
  }
  for (std::map<TString,TClonesArray*>::iterator it=ArrayContent_4TV_.begin() ; it != ArrayContent_4TV_.end(); it++ ){
   delete ((*it).second); 
  }
  for (std::map<TString,std::vector<ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> >* >::iterator it=ArrayContent_StdXYZ_.begin() ; it != ArrayContent_StdXYZ_.end(); it++ ){
   delete ((*it).second);
  }
  for (std::map<TString,std::vector<ROOT::Math::PositionVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> >* >::iterator it=ArrayContent_StdXYZ2_.begin() ; it != ArrayContent_StdXYZ2_.end(); it++ ){
   delete ((*it).second);
  }
  for (std::map<TString,TClonesArray*>::iterator it=ArrayContent_3TV_.begin() ; it != ArrayContent_3TV_.end(); it++ ){
   delete ((*it).second); 
  }
  for (std::map<TString,TClonesArray*>::iterator it=ArrayContent_TMatrix_.begin() ; it != ArrayContent_TMatrix_.end(); it++ ){
   delete ((*it).second); 
  }

  for (std::map<TString,std::vector<float>* >::iterator it=ArrayContentFloat_.begin() ; it != ArrayContentFloat_.end(); it++ ){
   delete ((*it).second);
  }
  for (std::map<TString,std::vector<double>* >::iterator it=ArrayContentDouble_.begin() ; it != ArrayContentDouble_.end(); it++ ){
   delete ((*it).second);
  }
  for (std::map<TString,std::vector<int>* >::iterator it=ArrayContentInt_.begin() ; it != ArrayContentInt_.end(); it++ ){
   delete ((*it).second);
  }
}


///--------------------------
///----- Add collection -----


void NtupleFactory::Add4V(const TString &name){
 if (ArrayContent_StdXYZT_.find (name) != ArrayContent_StdXYZT_.end ())
 {
  std::cerr << "ERROR : Array series " << name << " already existing, NOT replaced" << std::endl ;
  return ;                
 }
 std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >* dummy = new std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > > ;
 ArrayContent_StdXYZT_[name] = dummy ;
 outTree_->Branch(name,"std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >",&(ArrayContent_StdXYZT_[name]));
}

void NtupleFactory::Add4TV(const TString &name){
 if (ArrayContent_4TV_.find (name) != ArrayContent_4TV_.end ())
 {
  std::cerr << "ERROR : Array series " << name << " already existing, NOT replaced" << std::endl ;
  return ;                
 }
 TClonesArray* dummy = new TClonesArray ("TLorentzVector");
 ArrayContent_4TV_[name] = dummy ;
 outTree_->Branch (name, "TClonesArray", &(ArrayContent_4TV_[name]), 256000,0);
 ArrayContent_4TV_num_[name] = 0;
 return ;
}

void NtupleFactory::Add3V(const TString &name){
 if (ArrayContent_StdXYZ_.find (name) != ArrayContent_StdXYZ_.end ())
 {
  std::cerr << "ERROR : Array series " << name << " already existing, NOT replaced" << std::endl ;
  return ;                
 }
 std::vector<ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> >* dummy = new std::vector<ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> > ;
 ArrayContent_StdXYZ_[name] = dummy ;
 outTree_->Branch(name,"std::vector<ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> >",&(ArrayContent_StdXYZ_[name]));
}

void NtupleFactory::Add3PV(const TString &name){
 if (ArrayContent_StdXYZ2_.find (name) != ArrayContent_StdXYZ2_.end ())
 {
  std::cerr << "ERROR : Array series " << name << " already existing, NOT replaced" << std::endl ;
  return ;                
 }
 std::vector<ROOT::Math::PositionVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> >* dummy = new std::vector<ROOT::Math::PositionVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> > ;
 ArrayContent_StdXYZ2_[name] = dummy ;
 outTree_->Branch(name,"std::vector<ROOT::Math::PositionVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> >",&(ArrayContent_StdXYZ2_[name]));
}

void NtupleFactory::Add3TV(const TString &name){
 if (ArrayContent_4TV_.find (name) != ArrayContent_4TV_.end ())
 {
  std::cerr << "ERROR : Array series " << name << " already existing, NOT replaced" << std::endl ;
  return ;                
 }
 TClonesArray* dummy = new TClonesArray ("TVector3");
 ArrayContent_3TV_[name] = dummy ;
 outTree_->Branch (name, "TClonesArray", &(ArrayContent_3TV_[name]), 256000,0);
 ArrayContent_3TV_num_[name] = 0;
 return ;
}

void NtupleFactory::AddFloat(const TString &name){
 if (ArrayContentFloat_.find (name) != ArrayContentFloat_.end ())
 {
  std::cerr << "ERROR : Array series " << name << " already existing, NOT replaced" << std::endl ;
  return ;                
 }
 std::vector<float>* dummy = new std::vector<float> ;
 ArrayContentFloat_[name] = dummy ;
 outTree_->Branch(name,"std::vector<float>",&(ArrayContentFloat_[name]));
}

void NtupleFactory::AddDouble(const TString &name){
 if (ArrayContentDouble_.find (name) != ArrayContentDouble_.end ())
 {
  std::cerr << "ERROR : Array series " << name << " already existing, NOT replaced" << std::endl ;
  return ;                
 }
 std::vector<double>* dummy = new std::vector<double> ;
 ArrayContentDouble_[name] = dummy ;
 outTree_->Branch(name,"std::vector<double>",&(ArrayContentDouble_[name]));
}

void NtupleFactory::AddInt(const TString &name){
 if (ArrayContentInt_.find (name) != ArrayContentInt_.end ())
 {
  std::cerr << "ERROR : Array series " << name << " already existing, NOT replaced" << std::endl ;
  return ;                
 }
 std::vector<int>* dummy = new std::vector<int> ;
 ArrayContentInt_[name] = dummy ;
 outTree_->Branch(name,"std::vector<int>",&(ArrayContentInt_[name]));
}

void NtupleFactory::AddLongLongInt(const TString &name){
 if (ArrayContentLongLongInt_.find (name) != ArrayContentLongLongInt_.end ())
 {
  std::cerr << "ERROR : Array series " << name << " already existing, NOT replaced" << std::endl ;
  return ;                
 }
 std::vector<Long64_t>* dummy = new std::vector<Long64_t> ;
 ArrayContentLongLongInt_[name] = dummy ;
 outTree_->Branch(name,"std::vector<Long64_t>",&(ArrayContentLongLongInt_[name]));
}

void NtupleFactory::AddString(const TString &name){
 if (ArrayContentString_.find (name) != ArrayContentString_.end ())
 {
  std::cerr << "ERROR : Array series " << name << " already existing, NOT replaced" << std::endl ;
  return ;                
 }
 std::vector<std::string>* dummy = new std::vector<std::string> ;
 ArrayContentString_[name] = dummy ;
 outTree_->Branch(name,"std::vector<std::string>",&(ArrayContentString_[name]));
}



void NtupleFactory::AddTMatrix(const TString &name){
 if (ArrayContent_TMatrix_.find (name) != ArrayContent_TMatrix_.end ())
 {
  std::cerr << "ERROR : Array series " << name << " already existing, NOT replaced" << std::endl ;
  return ;                
 }
 TClonesArray* dummy = new TClonesArray ("TMatrix");
 ArrayContent_TMatrix_[name] = dummy ;
 outTree_->Branch (name, "TClonesArray", &(ArrayContent_TMatrix_[name]), 256000,0);
 ArrayContent_TMatrix_num_[name] = 0;
 return ;
}

////--------------------------
///----- Fill collection -----


void NtupleFactory::Fill4V(const TString &name,const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > &vect){
 if (ArrayContent_StdXYZT_.find (name) != ArrayContent_StdXYZT_.end ()){
  ArrayContent_StdXYZT_[name]->push_back(vect);
 }
 else {
  std::cerr << "ERROR : Array series " << name << " not existing. Nothing done." << std::endl ;
  return ;        
 }
}

void NtupleFactory::Fill4TV(const TString &name,const TLorentzVector &vect){
 if (ArrayContent_4TV_.find (name) != ArrayContent_4TV_.end ()){
  int counter = ArrayContent_4TV_num_[name];
  new ((*(ArrayContent_4TV_[name]))[counter]) TLorentzVector (vect);
  ArrayContent_4TV_num_[name] += 1;
 }
 else {
  std::cerr << "ERROR : Array series " << name << " not existing. Nothing done." << std::endl ;
  return ;        
 }
}

void NtupleFactory::Fill3V(const TString &name,const ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> &vect){
 if (ArrayContent_StdXYZ_.find (name) != ArrayContent_StdXYZ_.end ()){
  ArrayContent_StdXYZ_[name]->push_back(vect);
 }
 else {
  std::cerr << "ERROR : Array series " << name << " not existing. Nothing done." << std::endl ;
  return ;        
 }
}

void NtupleFactory::Fill3PV(const TString &name,const ROOT::Math::PositionVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> &vect){
 if (ArrayContent_StdXYZ2_.find (name) != ArrayContent_StdXYZ2_.end ()){
  ArrayContent_StdXYZ2_[name]->push_back(vect);
 }
 else {
  std::cerr << "ERROR : Array series " << name << " not existing. Nothing done." << std::endl ;
  return ;        
 }
}

void NtupleFactory::Fill3TV(const TString &name,const TVector3 &vect){
 if (ArrayContent_3TV_.find (name) != ArrayContent_3TV_.end ()){
  int counter = ArrayContent_3TV_num_[name];
  new ((*(ArrayContent_3TV_[name]))[counter]) TVector3 (vect);
  ArrayContent_3TV_num_[name] += 1;
 }
 else {
  std::cerr << "ERROR : Array series " << name << " not existing. Nothing done." << std::endl ;
  return ;        
 }
}

void NtupleFactory::FillFloat(const TString &name,const float &vect){
 if (ArrayContentFloat_.find (name) != ArrayContentFloat_.end ()){
  ArrayContentFloat_[name]->push_back(vect);
 }
 else {
  std::cerr << "ERROR : Array series " << name << " not existing. Nothing done." << std::endl ;
  return ;        
 }
}
 
void NtupleFactory::FillDouble(const TString &name,const double &vect){
 if (ArrayContentDouble_.find (name) != ArrayContentDouble_.end ()){
  ArrayContentDouble_[name]->push_back(vect);
 }
 else {
  std::cerr << "ERROR : Array series " << name << " not existing. Nothing done." << std::endl ;
  return ;        
 }
}
 
void NtupleFactory::FillInt(const TString &name,const int &vect){
 if (ArrayContentInt_.find (name) != ArrayContentInt_.end ()){
  ArrayContentInt_[name]->push_back(vect);
 }
 else {
  std::cerr << "ERROR : Array series " << name << " not existing. Nothing done." << std::endl ;
  return ;        
 }
}

void NtupleFactory::FillLongLongInt(const TString &name,const int &vect){
 if (ArrayContentLongLongInt_.find (name) != ArrayContentLongLongInt_.end ()){
  ArrayContentLongLongInt_[name]->push_back(vect);
 }
 else {
  std::cerr << "ERROR : Array series " << name << " not existing. Nothing done." << std::endl ;
  return ;        
 }
}

void NtupleFactory::FillString(const TString &name,const std::string& vect){
 if (ArrayContentString_.find (name) != ArrayContentString_.end ()){
  ArrayContentString_[name]->push_back(vect);
 }
 else {
  std::cerr << "ERROR : Array series " << name << " not existing. Nothing done." << std::endl ;
  return ;        
 }
}

void NtupleFactory::FillTMatrix(const TString &name,const TMatrix &vect){
 if (ArrayContent_TMatrix_.find (name) != ArrayContent_TMatrix_.end ()){
  int counter = ArrayContent_TMatrix_num_[name];
  new ((*(ArrayContent_TMatrix_[name]))[counter]) TMatrix (vect);
  ArrayContent_TMatrix_num_[name] += 1;
 }
 else {
  std::cerr << "ERROR : Array series " << name << " not existing. Nothing done." << std::endl ;
  return ;        
 }
}


///---- Clear Ntuple ------------
void NtupleFactory::ClearNtuple(){
  for (std::map<TString,std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >* >::iterator it=ArrayContent_StdXYZT_.begin() ; it != ArrayContent_StdXYZT_.end(); it++ ){
    ((*it).second)->clear();  
  }
  for (std::map<TString,TClonesArray*>::iterator it=ArrayContent_4TV_.begin() ; it != ArrayContent_4TV_.end(); it++ ){
    ((*it).second)->Clear(); 
    ArrayContent_4TV_num_[(*it).first] = 0;
  }
  for (std::map<TString,std::vector<ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> >* >::iterator it=ArrayContent_StdXYZ_.begin() ; it != ArrayContent_StdXYZ_.end(); it++ ){
    ((*it).second)->clear();  
  }
  for (std::map<TString,std::vector<ROOT::Math::PositionVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> >* >::iterator it=ArrayContent_StdXYZ2_.begin() ; it != ArrayContent_StdXYZ2_.end(); it++ ){
    ((*it).second)->clear();  
  }
  for (std::map<TString,TClonesArray*>::iterator it=ArrayContent_3TV_.begin() ; it != ArrayContent_3TV_.end(); it++ ){
    ((*it).second)->Clear(); 
    ArrayContent_3TV_num_[(*it).first] = 0;
  }
 for (std::map<TString,TClonesArray*>::iterator it=ArrayContent_TMatrix_.begin() ; it != ArrayContent_TMatrix_.end(); it++ ){
    ((*it).second)->Clear(); 
    ArrayContent_TMatrix_num_[(*it).first] = 0;
  }
  
  for (std::map<TString,std::vector<float>* >::iterator it=ArrayContentFloat_.begin() ; it != ArrayContentFloat_.end(); it++ ){
    ((*it).second)->clear();  
  }
  for (std::map<TString,std::vector<double>* >::iterator it=ArrayContentDouble_.begin() ; it != ArrayContentDouble_.end(); it++ ){
    ((*it).second)->clear();  
  }
  for (std::map<TString,std::vector<int>* >::iterator it=ArrayContentInt_.begin() ; it != ArrayContentInt_.end(); it++ ){
    ((*it).second)->clear();  
  }
  for (std::map<TString,std::vector<Long64_t>* >::iterator it=ArrayContentLongLongInt_.begin() ; it != ArrayContentLongLongInt_.end(); it++ ){
    ((*it).second)->clear();  
  }
  for (std::map<TString,std::vector<std::string>* >::iterator it=ArrayContentString_.begin() ; it != ArrayContentString_.end(); it++ ){
    ((*it).second)->clear();  
  }
}

///---- Write entry to TTree ----
void NtupleFactory::FillNtuple(){
 outTree_->Fill();
 ClearNtuple();
}



///---- Write collection to file ----
void NtupleFactory::WriteNtuple(){
 //---- if using TFileService, not use this
 if (internalTree_) outFile_->Write();
 else std::cerr << "Service not available: using TFileService" << std::endl ;
}




///---- Write to a text file branches declaration ----
void NtupleFactory::DumpBranches(){
 //----- symply use MakeClass
 outTree_->MakeClass("out.txt");
}

