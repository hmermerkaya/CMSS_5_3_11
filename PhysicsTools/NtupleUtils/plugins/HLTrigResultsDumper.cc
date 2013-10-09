/** \class HLTrigResultsDumper
 *
 *  \author Leonardo Di Matteo
 *
 */

#include "PhysicsTools/NtupleUtils/plugins/HLTrigResultsDumper.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include <iomanip>

using namespace std;
using namespace edm;

//
// constructors and destructor
//
HLTrigResultsDumper::HLTrigResultsDumper(const edm::ParameterSet& iConfig) :
  hlTriggerResults_ (iConfig.getParameter<edm::InputTag> ("HLTriggerResults")),
  HLTPaths_ (iConfig.getParameter<std::vector<std::string> >("HLTPaths")),
  hltConfig_()
{
  
  Service<TFileService> fs ;
  HLTree = fs->make<TTree> ("HLTree","HLTree");
  NtupleFactory_ = new NtupleFactory (HLTree) ;

  NameHLT = fs->make<TTree> ("NameHLT","NameHLT");
  NameHLT->Branch("HLTTag_names",&HLTPaths_);
  NameHLT->Fill();
}

HLTrigResultsDumper::~HLTrigResultsDumper()
{ }

//
// member functions
//

void
HLTrigResultsDumper::beginRun(edm::Run const & iRun, edm::EventSetup const& iSetup)
{
  using namespace std;
  using namespace edm;
  
  NtupleFactory_->AddInt("HLTwasrun"); 
  NtupleFactory_->AddInt("HLTaccept"); 
  NtupleFactory_->AddInt("HLTerror"); 
  
  bool changed (true);
  if (hltConfig_.init(iRun,iSetup,hlTriggerResults_.process(),changed)) {
    if (changed) {
      // const edm::TriggerNames & triggerNames = iEvent.triggerNames(*HLTR);
      hlNames_=hltConfig_.triggerNames();
    }
  } else {
    // dump previous
    hlNames_.clear();
  }


  return;
}
      
    
// ------------ method called to produce the data  ------------
void
HLTrigResultsDumper::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // accumulation of statistics event by event

  using namespace std;
  using namespace edm;

  // get hold of TriggerResults
  Handle<TriggerResults> HLTR;
  iEvent.getByLabel(hlTriggerResults_,HLTR);

  const unsigned int n(hlNames_.size());
  
  // decision for each HLTPaths
  for ( int iPath = 0; iPath < (int) HLTPaths_.size(); iPath++ ) {
  //Find the index of the HLTPath under inspection
  int thePathIndex = -1;

    for (unsigned int i=0; i!=n; ++i) {
//cout<<hlNames_[i]<<" "<<HLTR->wasrun(i)<<" "<<HLTR->accept(i)<<endl ;

      if ( HLTPaths_[iPath] == hlNames_[i] ) thePathIndex = i;
    }
  // cout<<"END"<<endl;
  
    //fill HLT info only for the HLT path which are in the HLT menu
    if ( thePathIndex > -1 && HLTR->wasrun((unsigned int)thePathIndex) ) NtupleFactory_->FillInt("HLTwasrun",1);
    else NtupleFactory_->FillInt("HLTwasrun",0);
    if ( thePathIndex > -1 && HLTR->accept((unsigned int)thePathIndex) ) NtupleFactory_->FillInt("HLTaccept",1);
    else NtupleFactory_->FillInt("HLTaccept",0);
    if ( thePathIndex > -1 && HLTR->error((unsigned int)thePathIndex) ) NtupleFactory_->FillInt("HLTerror",1);
    else NtupleFactory_->FillInt("HLTerror",0);
  }
  //Fill HLT tree
  NtupleFactory_->FillNtuple();

  return;

}

void
HLTrigResultsDumper::endJob()
{ }

// ----------------------------------------------------------------

//define this as a plug-in
DEFINE_FWK_MODULE(HLTrigResultsDumper);

// ----------------------------------------------------------------

