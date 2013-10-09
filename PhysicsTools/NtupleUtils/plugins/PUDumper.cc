#include "PhysicsTools/NtupleUtils/plugins/PUDumper.h"






//! ctor
PUDumper::PUDumper(const edm::ParameterSet& iConfig)
{
  MCPileupTag_ = iConfig.getParameter<edm::InputTag>("MCPileupTag");
  mcFlag_ = iConfig.getUntrackedParameter<bool>("mcFlag",true);  
  
  // create histograms
  edm::Service<TFileService> fs;
  
  h_nPUtrue      = fs -> make<TH1F>("nPUtrue",     "nPUtrue",     50,-0.5,49.5);
  h_nPUit        = fs -> make<TH1F>("nPUit",       "nPUit",       50,-0.5,49.5);
  h_nPUoot_early = fs -> make<TH1F>("nPUoot_early","nPUoot_early",50,-0.5,49.5);
  h_nPUoot_late  = fs -> make<TH1F>("nPUoot_late"," nPUoot_late", 50,-0.5,49.5);
}

// ----------------------------------------------------------------






//! dtor
PUDumper::~PUDumper()
{}

// ----------------------------------------------------------------






//! loop over the reco particles and count leptons
void PUDumper::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // skip if running on data
  if( !mcFlag_ ) return;
  
  
  // get the PU collection
  edm::Handle<std::vector<PileupSummaryInfo> > PupInfo;
  iEvent.getByLabel(MCPileupTag_,PupInfo);
  
  
  // nPU
  int nPUtrue = 0;
  int nPUit = 0;
  int nPUoot_early = 0;
  int nPUoot_late = 0;
  
  
  // loop on BX
  std::vector<PileupSummaryInfo>::const_iterator PVI;
  for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI)
  {
    //std::cout << "PUDumper::BX: " << PVI->getBunchCrossing() << "   nPU: " << PVI->getPU_NumInteractions() << std::endl;
    
    // in-time pileup
    if( PVI->getBunchCrossing() == 0 )
    {
      nPUtrue += PVI->getTrueNumInteractions();
      nPUit   += PVI->getPU_NumInteractions();
    }
    
    // out-of-time pileup
    else if( PVI->getBunchCrossing() < 0 )
    {
      nPUoot_early += PVI->getPU_NumInteractions();
    }
    
    // out-of-time pileup
    else
    {
      nPUoot_late += PVI->getPU_NumInteractions();
    }
  } // loop on BX
  
  
  // fill histograms
  h_nPUtrue      -> Fill(nPUtrue);
  h_nPUit        -> Fill(nPUit);
  h_nPUoot_early -> Fill(nPUoot_early);
  h_nPUoot_late  -> Fill(nPUoot_late);
}

DEFINE_FWK_MODULE(PUDumper);
