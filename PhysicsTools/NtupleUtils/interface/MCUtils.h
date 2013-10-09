#ifndef MCUtils_h
#define MCUtils_h

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/Particle.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include <vector>
#include <string>
#include <sstream>






// -----------------------------------------------------------------
// Print mc particle infos
// -----------------------------------------------------------------

template <class T>
void PrintParticleInfo(T* pCurrent)
{
  // Print the particle info
  std::cout << std::setprecision(3) << std::fixed
            << "pdgId:"     << std::setw(5) << pCurrent -> pdgId()
            << "   Charge:" << std::setw(4) << pCurrent -> charge()
            << "   St:"     << std::setw(1) << pCurrent -> status()
            << "   P=("     << std::setw(8) << pCurrent -> energy()
            << ","          << std::setw(8) << pCurrent -> px()
            << ","          << std::setw(8) << pCurrent -> py()
            << ","          << std::setw(8) << pCurrent -> pz()
            << ")   pT = "  << std::setw(7) << pCurrent -> pt()
            << "   eta = "  << std::setw(7) << (pCurrent -> p4()).eta()
            << "   phi = "  << std::setw(7) << (pCurrent -> p4()).phi()
            << "   m = "    << std::setw(7) << pCurrent -> mass()
            << std::endl;
}






// -----------------------------------------------------------------
// Print the whole decay tree
// -----------------------------------------------------------------

void PrintDecayTree(const reco::Candidate* pCurrent,
                    const int& level = 1);






// -----------------------------------------------------------------
// Find the daughter particles
// -----------------------------------------------------------------

void FindDaughterParticles(const reco::Candidate** pCurrent,
                           const bool& verbosity,
                           const int& level,
                           std::vector<const reco::Candidate*>* pFinal = 0);






// -----------------------------------------------------------------
// Get the vector of mc decay particles
// -----------------------------------------------------------------

void FindDecayParticles(std::vector<const reco::Candidate*>& pFinal,
                        const reco::Candidate* pCurrent,
                        const bool& verbosity = false,
                        const int& level = 1);






// -----------------------------------------------------------------
// Get the neutrinos and visible tau-jet from tau decay
// -----------------------------------------------------------------
void FindTauDecayParticles(std::vector<const reco::Candidate*>& tauJ,
                           std::vector<const reco::Candidate*>& nu,
                           const reco::Candidate* pCurrent,
                           const bool& verbosity = false);

#endif
