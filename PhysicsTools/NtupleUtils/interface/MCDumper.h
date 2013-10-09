#ifndef MCDumper_h
#define MCDumper_h

#include "PhysicsTools/NtupleUtils/interface/MCUtils.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include <vector>



class MCDumper
{
 public:
  
  //!ctor
  MCDumper(edm::Handle<reco::GenParticleCollection>& genParticles,const bool& verbosity);
  MCDumper(edm::Handle<reco::GenParticleCollection>& genParticles,const bool& verbosity,const std::vector<int>& mc_pdgId);
    
  //!dtor
  ~MCDumper();
 
  std::vector<const reco::Candidate*> Get(int pdgId); 
   
 private:
  
  void Analyze(edm::Handle<reco::GenParticleCollection>& hGenParticles);

  bool verbosity_p;

  std::map<int,std::vector<const reco::Candidate*>* > mc_p;
  std::vector<int> mc_pdgId_p;
  
};

#endif
