#include "PhysicsTools/NtupleUtils/interface/MCDumper.h"


// -----------------------------------------------------------------
// ctor
// -----------------------------------------------------------------

MCDumper::MCDumper(edm::Handle<reco::GenParticleCollection>& genParticles,const bool& verbosity):
 verbosity_p(verbosity)
{ 
 if(verbosity_p)
  std::cerr << "*** MCDumper::ctor ***" << std::endl;  
 Analyze(genParticles);
}


MCDumper::MCDumper(edm::Handle<reco::GenParticleCollection>& genParticles,const bool& verbosity,const std::vector<int>& mc_pdgId):
  verbosity_p(verbosity)
{ 
 
 int nentries = mc_pdgId.size();
 for (int i=0; i<nentries; i++){
  mc_pdgId_p.push_back(mc_pdgId.at(i));
  std::vector<const reco::Candidate*>* dummy = new std::vector<const reco::Candidate*>;
  mc_p[mc_pdgId.at(i)] = dummy;
 }
  
 if(verbosity_p)
  std::cerr << "*** MCDumper::ctor ***" << std::endl;  
 Analyze(genParticles);
}






// -----------------------------------------------------------------
// dtor
// -----------------------------------------------------------------

MCDumper::~MCDumper()
{  
 if(verbosity_p)
  std::cerr << "*** MCDumper::dtor ***" << std::endl;
   
   for (std::map<int,std::vector<const reco::Candidate*>* >::iterator it=mc_p.begin() ; it != mc_p.end(); it++ ){
  delete ((*it).second);
   }
   
}






// -----------------------------------------------------------------
// Analyze
// -----------------------------------------------------------------

void MCDumper::Analyze(edm::Handle<reco::GenParticleCollection>& genParticles)
{
 if(verbosity_p)
  std::cerr << "*** MCDumper::Analyze ***" << std::endl;
  
 for(reco::GenParticleCollection::const_iterator p = genParticles -> begin();
     p != genParticles -> end(); ++p)
 {
  const reco::Candidate* pCurrent = &(*p);  
  int pdgId  = p -> pdgId();
  //int status = p -> status();
  //int charge = p -> charge();
  if (mc_p[pdgId] != 0) {
   mc_p[pdgId]->push_back(pCurrent); 
  }
 }
}


// -----------------------------------------------------------------
// Get
// -----------------------------------------------------------------

std::vector<const reco::Candidate*> MCDumper::Get(int pdgId)
{
 if(verbosity_p)
  std::cerr << "*** MCDumper::Get Id = " << pdgId << " ***" << std::endl;
 return *(mc_p[pdgId]);
}





