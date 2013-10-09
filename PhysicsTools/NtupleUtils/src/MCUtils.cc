#include "PhysicsTools/NtupleUtils/interface/MCUtils.h"






// -----------------------------------------------------------------
// Print the whole decay tree
// -----------------------------------------------------------------

void PrintDecayTree(const reco::Candidate* pCurrent,
                    const int& level)
{
  for(int j = 0; j < level; ++j) std::cout << "------";
  std::cout << "> ";
  PrintParticleInfo(pCurrent);  
  
  
  for(unsigned int i = 0; i < pCurrent -> numberOfDaughters(); ++i)
  {
    if(pCurrent -> daughter(i) -> status() == 1)
    {
      for(int j = 0; j < level+1; ++j) std::cout << "------";
      std::cout << "> ";
      PrintParticleInfo(pCurrent -> daughter(i));
    }
    
    else PrintDecayTree(pCurrent -> daughter(i), level+1);
  }
  
}






// -----------------------------------------------------------------
// Find the mc daughter particles
// -----------------------------------------------------------------

void FindDaughterParticles(const reco::Candidate** pCurrent,
                           const bool& verbosity,
                           const int& level,
                           std::vector<const reco::Candidate*>* pFinal)
{
  if( (verbosity) && (level == 1) )
    std::cout << std::endl;

  if(verbosity)
  {
    for(int j = 0; j < level; ++j) std::cout << "------";
    std::cout << "> ";
    PrintParticleInfo(*pCurrent);  
  }
  
  
  
  // Variable for decayed current particle
  const reco::Candidate* pCurrentNew = 0;
  
  
  
  for(unsigned int i = 0; i < (*pCurrent) -> numberOfDaughters(); ++i)
  {
    if(verbosity)
    {
      for(int j = 0; j < level+1; ++j) std::cout << "------";
      std::cout << "> ";
      PrintParticleInfo((*pCurrent) -> daughter(i));
    }
    
    
    if( (pFinal != 0) && ((*pCurrent) -> daughter(i) -> pdgId() != (*pCurrent) -> pdgId()) )
      pFinal -> push_back((*pCurrent) -> daughter(i));
    
    if((*pCurrent) -> daughter(i) -> pdgId() == (*pCurrent) -> pdgId())
      pCurrentNew = (*pCurrent) -> daughter(i);
  }
  
  
  // Change the current particle into the decayed one
  if(pCurrentNew)
    (*pCurrent) = pCurrentNew;
}






// -----------------------------------------------------------------
// Get the vector of mc decay particles
// -----------------------------------------------------------------

void FindDecayParticles(std::vector<const reco::Candidate*>& pFinal,
                        const reco::Candidate* pCurrent,
                        const bool& verbosity,
                        const int& level)
{
  if(verbosity)
  {
    for(int j = 0; j < level; ++j) std::cout << "------";
    std::cout << "> ";
    PrintParticleInfo(pCurrent);  
  }
  
  
  for(unsigned int i = 0; i < pCurrent -> numberOfDaughters(); ++i)
  {
    if(pCurrent -> daughter(i) -> status() == 1)
    {
      pFinal.push_back(pCurrent -> daughter(i));
      
      if(verbosity)
      {
        for(int j = 0; j < level+1; ++j) std::cout << "------";
        std::cout << "> ";
        PrintParticleInfo(pCurrent -> daughter(i));
      }
    }
     
    else FindDecayParticles(pFinal, pCurrent -> daughter(i), verbosity, level+1);
  }
  
}






// -----------------------------------------------------------------
// Get the neutrinos and visible tau-jet from tau decay
// -----------------------------------------------------------------

void FindTauDecayParticles(std::vector<const reco::Candidate*>& tauJ,
                           std::vector<const reco::Candidate*>& nu,
                           const reco::Candidate* pCurrent,
                           const bool& verbosity)
{
  if( abs(pCurrent -> pdgId()) != 15 )
  {
    std::cerr << ">>>>>> MCUtils::FindTauDecayParticles::Warning: Particle given is not a tau" << std::endl;
    return;
  }
  
  
  // clear vectors for final state particles from tau decay
  tauJ.clear();
  nu.clear();
  
  
  // decay parameters
  int nProng = 0;
  bool isLeptonic = false;

  std::vector<const reco::Candidate*> pFinal;
  FindDecayParticles(pFinal, pCurrent, verbosity);
  
  
  // get neutrinos and visible tauJ 
  for(unsigned int i = 0; i < pFinal.size(); ++i)
  {
    int pdgId =  pFinal.at(i) -> pdgId();
    int charge = pFinal.at(i) -> charge();
    
    if( (abs(pdgId) == 12) || (abs(pdgId) == 14) || (abs(pdgId) == 16) )
      nu.push_back(pFinal.at(i));
    
    if( (abs(pdgId) == 12) || (abs(pdgId) == 14) )
      isLeptonic = true;
    
    if( (abs(pdgId) != 12) && (abs(pdgId) != 14) && (abs(pdgId) != 16) )
      tauJ.push_back(pFinal.at(i));
  
    if(charge != 0)
      ++nProng;
  }
  
}
