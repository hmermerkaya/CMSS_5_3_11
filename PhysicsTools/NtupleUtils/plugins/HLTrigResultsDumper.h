#ifndef HLTrigResultsDumper_h
#define HLTrigResultsDumper_h

/** \class HLTrigResultsDumper
 *
 *  
 *  This class is an EDAnalyzer saves essential HLT info into a TTree
 *
 *  \author Leonardo Di Matteo
 *
 */
 
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "PhysicsTools/NtupleUtils/interface/NtupleFactory.h"

#include<vector>
#include<string>

#include <TTree.h>

//
// class declaration
//

class HLTrigResultsDumper : public edm::EDAnalyzer {

   public:
      explicit HLTrigResultsDumper(const edm::ParameterSet&);
      ~HLTrigResultsDumper();

      virtual void beginRun(edm::Run const &, edm::EventSetup const&);

      virtual void endJob();

      virtual void analyze(const edm::Event&, const edm::EventSetup&);

   private:

      edm::InputTag hlTriggerResults_;  // Input tag for TriggerResults
      
       /// input paths that will be expanded into trigger names
      std::vector<std::string>  HLTPaths_;

      HLTConfigProvider hltConfig_;        // to get configuration for L1s/Pre
      
      std::vector<std::string>  hlNames_;  // name of each HLT algorithm
      
      //Tree containing essential HLT info
      TTree * HLTree ;  
      TTree * NameHLT ;  
      NtupleFactory* NtupleFactory_;
      NtupleFactory* NtupleFactory_HLTnames;

};

#endif //HLTrigResultsDumper_h
